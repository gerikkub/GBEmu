#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <omp.h>


#include "main.h"
#include "instructions.h"
#include "core.h"
#include "mem.h"
#include "video.h"
#include "io.h"
#include "dma.h"
#include "joypad.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

#define BIT(x)	(1<<x)

#define LCD_CONTROL_DISPLAY_ENABLE		BIT(7)
#define LCD_CONTROL_WINDOW_TILE_MAP		BIT(6)
#define LCD_CONTROL_WINDOW_ENABLE		BIT(5)
#define LCD_CONTROL_BG_TILE_DATA		BIT(4)
#define LCD_CONTROL_WINDOW_TILE_DATA	BIT(4)
#define LCD_CONTROL_BG_TILE_MAP			BIT(3)
#define LCD_CONTROL_SPRITE_8X16			BIT(2)
#define LCD_CONTROL_SPRITE_ENABLE		BIT(1)
#define LCD_CONTROL_BG_ENABLE			BIT(0)

#define LCD_MODE0	0
#define LCD_MODE1	1
#define	LCD_MODE2	2
#define LCD_MODE3	3

#define LCD_STATUS_LYC_LY_INT			BIT(6)
#define LCD_STATUS_OAM_INT				BIT(5)
#define LCD_STATUS_V_BLANK_INT			BIT(4)
#define LCD_STATUS_H_BLANK_INT			BIT(3)
#define LCD_STATUS_LYC_LC_FLAG			BIT(2)
#define LCD_STATUS_MODE3				LCD_MODE3
#define	LCD_STATUS_MODE2				LCD_MODE2
#define LCD_STATUS_MODE1				LCD_MODE1 
#define LCD_STATUS_MODE0				LCD_MODE0

#define LCD_MODE0	0
#define LCD_MODE1	1
#define	LCD_MODE2	2
#define LCD_MODE3	3

//From white to black
#define LCD_COLOR0	0
#define LCD_COLOR1	1
#define LCD_COLOR2	2
#define LCD_COLOR3	3

#define OAM_FLAG_PRIORITY	BIT(7)
#define OAM_FLAG_YFLIP		BIT(6)
#define OAM_FLAG_XFLIP		BIT(5)
#define OAM_FLAG_PALETTE	BIT(4)

#define SCREEN_WIDTH	160
#define SCREEN_HEIGHT	144
#define WINDOW_SCALE	1

#define MAX_SPRITES_PER_LINE	10

#define TILES_PER_ROW		20
#define TILES_PER_COLUMN	18

#define MODE_0_THRESHOLD	249
#define MODE_2_THRESHOLD	0
#define MODE_3_THRESHOLD	77

#define PIXEL_FORMAT SDL_PIXELFORMAT_ARGB8888

typedef int drawBuffer[160][144];

int shouldFillBuffers = 0;	//Will be set to 1 when screen buffers should be filled
int shouldRedraw = 0;		//Will be set when entire screen should be blitted to the screen
int drawingComplete = 0;	//Will be set to 1 when a new line can be drawn
int buffersFull = 0;		//Will be set to 1 when buffers are full and ready for drawing
int spriteTableChanged = 1;	//Will be set to one when the list needs to be sorted

static SDL_Window* window;
static SDL_Renderer* renderer;

SDL_sem *drawVideoStartSem;
SDL_sem *drawVideoCompleteSem;
SDL_sem *fillBuffersSem;
SDL_sem *spriteStartSem;
SDL_sem *windowStartSem;
SDL_sem *backgroundStartSem;
SDL_sem *spriteEndSem;
SDL_sem *windowEndSem;
SDL_sem *backgroundEndSem;

static SDL_sem *drawOnMainThreadSem;
static int renderScreen[144][160];
static SDL_Texture* screenTexture;	


typedef struct tileLine_T {
	char lowBits;
	char highBits;
}__attribute__((packed)) tileLine;
	
typedef struct tileData_t {
	tileLine lines[8];
}__attribute__((packed)) tileData;

typedef struct SpriteList_t {
	int spriteNum;
	struct SpriteList_t* next;
} SpriteList;

typedef struct OAMEntry_t {
	unsigned char Y;
	unsigned char X;
	unsigned char tile;
	unsigned char flags;
}__attribute__((packed)) OAMEntry;

SpriteList* firstSprite;

void spriteListInsert(SpriteList** first,SpriteList* insertPoint,int spriteNum){
	
	if(insertPoint == NULL){
		return;
	}
	
	SpriteList *newElement = (SpriteList*)malloc(sizeof(newElement));
	if(newElement == NULL){
		printf("Couldn't Allocate room for new Sprite!!!\n");
		exit(1);
	}
	SpriteList *searchElement = *first;
	
	newElement->spriteNum = spriteNum;
	if(insertPoint==*first){
		newElement->next = *first;
		*first = newElement;
	} else {	
		while(searchElement->next != insertPoint){
			searchElement = searchElement->next;
			if(searchElement == NULL){
				return;
			}
		}
		newElement->next = insertPoint;
		searchElement->next = newElement;
	}
}

void spriteListDelete(SpriteList** first,SpriteList* deletePoint){
	if(*first == deletePoint){
		SpriteList* tempSprite;
		tempSprite = *first;
		*first = tempSprite->next;
		free(tempSprite);
		return;
	}
	
	SpriteList* searchElement = *first;
	
	while(searchElement->next != deletePoint){
		searchElement = searchElement->next;
		if(searchElement==NULL){
			return;
		}
	}
	searchElement->next = deletePoint->next;
	free(deletePoint);
}
	
SpriteList* getSpriteElement(SpriteList** first,int data){
	SpriteList *search = *first;
	while((search!=NULL)&&(search->spriteNum!=data)){
		search = search->next;
	}
	return search;
}

void spriteListSort(SpriteList** first,SpriteList* last){
	if(*first == NULL){
		return;
	}

	if(((*first)->next == last)||((*first) == last)){
		return;
	}	
	
	OAMEntry* OAMTableEntries = (OAMEntry*)OAMTable;
	
	SpriteList *pivot = *first;
	SpriteList *currSprite = pivot->next;
	SpriteList *tempSprite;
	int pivotNum = OAMTableEntries[pivot->spriteNum].X;
	
	while(currSprite!=last){
		if(OAMTableEntries[currSprite->spriteNum].X<pivotNum){
			spriteListInsert(first,pivot,OAMTableEntries[currSprite->spriteNum].X);
			tempSprite = currSprite;
			currSprite = currSprite->next;
			spriteListDelete(first,tempSprite);
		} else {
			currSprite = currSprite->next;
		}
	}

	spriteListSort(first,pivot);
	spriteListSort(&pivot->next,last);
}	
	
unsigned char getColorForTile(tileData* tile,int row, int column){
	tileLine readLine = tile->lines[row];
	char upperBit = readLine.highBits >> (7-column);
	upperBit = upperBit&1;
	char lowerBit = readLine.lowBits >> (7-column);
	lowerBit = lowerBit&1;
	
	return ((upperBit<<1)|lowerBit)&0x3;
}
	
void updateVideo(int screenRefreshCount){
	
	int temp;
	
	
	if(screenRefreshCount<65664){	//Not in V-Blank
	
		if(screenRefreshCount == 0){
			SDL_SemWait(drawVideoCompleteSem);
			drawingComplete = 0;
			setLY(0);
			setLCDStatus((getLCDStatus()&0xFC)|LCD_MODE2);			
			shouldFillBuffers=1;
			SDL_SemPost(fillBuffersSem);
			
			//If Mode 2 interrupt enabled
			if((getLCDStatus()&LCD_STATUS_OAM_INT)!=0){
				setInterrupt(INT_LCD);			//Set LCD STAT Interrupt
			}
			if(getLY()==getLYC()){
				setLCDStatus(getLCDStatus()|LCD_STATUS_LYC_LC_FLAG);	//Set Coincidence Flag
				if(getLCDStatus()&LCD_STATUS_LYC_LY_INT){
					setInterrupt(INT_LCD);				//Set LCD STAT Interrupt Request
				}
			} else {
				setLCDStatus(getLCDStatus(~LCD_STATUS_LYC_LC_FLAG));	//Otherwise clear it
			}	
		} else {
			temp = screenRefreshCount%456;
			if(temp==MODE_2_THRESHOLD){	//Switch To Mode 2
				setLCDStatus((getLCDStatus()&0xFC)|LCD_MODE2);
				setLY(getLY()+1);				
				
				//If Mode 2 interrupt enabled
				if((getLCDStatus()&LCD_STATUS_OAM_INT)!=0){
					setInterrupt(INT_LCD);		//Set LCD STAT Interrupt
				}
				
				if(getLY()==getLYC()){	//If LY and LYC are equal
					setLCDStatus(getLCDStatus()|LCD_STATUS_LYC_LC_FLAG);	//Set Coincidence Flag
					if(getLCDStatus()&LCD_STATUS_LYC_LY_INT){
						setInterrupt(INT_LCD);				//Set LCD STAT Interrupt Request
					}
				} else {
					setLCDStatus(getLCDStatus()& ~LCD_STATUS_LYC_LC_FLAG);	//Otherwise clear it
				}	
			} else if(temp==MODE_3_THRESHOLD){
				setLCDStatus((getLCDStatus()&0xFC)|LCD_MODE3);
			} else if(temp==MODE_0_THRESHOLD){
				setLCDStatus((getLCDStatus()&0xFC)|LCD_MODE0);
				if((getLCDStatus()&LCD_STATUS_H_BLANK_INT)){	//If Mode 0 flag set
					setInterrupt(INT_LCD);	//Set LCD STAT Interrupt
				}	
			}
		}	
	} else if(screenRefreshCount==65664){	//V-Blank Start
	
	
		buffersFull = 0;
		shouldRedraw = 1;
		SDL_SemPost(drawVideoStartSem);
		setLCDStatus((getLCDStatus()&0xFC)|LCD_STATUS_MODE1);
		setLY(getLY() + 1);
		
		if(getLCDStatus()&LCD_STATUS_V_BLANK_INT){
			setInterrupt(INT_VBLANK);	
		}	
		
		if(getLY()==getLYC()){	//If LY and LYC are equal
			setLCDStatus(getLCDStatus()|LCD_STATUS_LYC_LC_FLAG);	//Set Coincidence Flag
			if(getLCDStatus()&LCD_STATUS_LYC_LC_FLAG){
				setInterrupt(INT_LCD);
			}
		} else {
			setLCDStatus(getLCDStatus()& ~LCD_STATUS_LYC_LC_FLAG);
		}
	} else if((screenRefreshCount%456)==0){
		setLY(getLY()+1);
		if(getLY()==getLYC()){
			setLCDStatus(getLCDStatus()|LCD_STATUS_LYC_LC_FLAG);
			if(getLCDStatus()&LCD_STATUS_LYC_LC_FLAG){
				setInterrupt(INT_LCD);
			}
		} else {
			setLCDStatus(getLCDStatus()& ~LCD_STATUS_LYC_LC_FLAG);
		}
	}	
}

char hasAlpha(int pixel) {
   return ((pixel >> 24)&0xFF) == 0x80;
}

int checkForWhite(int pixel){
	return (pixel&0xFFFFFF) == 0xFFFFFF;
}

void drawBGTileToBuffer(unsigned int tileNum,drawBuffer outputBuffer,int x,int y,int palette[4]){
	
	tileData* currTile = (tileData*)&vramBanks[tileNum*sizeof(tileData)];
	
	int tileRow,tileColumn;
	
	if((x<=-8)||(x>160)){
		return;
	}
	if((y<=-8)||(y>144)){
		return;
	}
	
	for(tileRow=0;tileRow<8;tileRow++){
		for(tileColumn=0;tileColumn<8;tileColumn++){
			if((x+tileColumn>=0)&&(x+tileColumn<160)){
				if((y+tileRow>=0)&&(y+tileRow<144)){
					outputBuffer[x+tileColumn][y+tileRow] = palette[getColorForTile(currTile,tileRow,tileColumn)];
				}
			}
		}
	}
}	

void reverseTile(drawBuffer outputBuffer,int x,int y){
	
	int tempColor;
	int i;
	
	if(x<0){
		return;
	} else if(y<0){
		return;
	}
	
	for(i=0;i<8;i++){
		tempColor = outputBuffer[x+7][y+i];
		outputBuffer[x+7][y+i] = outputBuffer[x][y+i];
		outputBuffer[x][y+i] = tempColor;
		
		tempColor = outputBuffer[x+6][y+i];
		outputBuffer[x+6][y+i] = outputBuffer[x+1][y+1];
		outputBuffer[x+1][y+i] = tempColor;
		
		tempColor = outputBuffer[x+5][y+i];
		outputBuffer[x+5][y+i] = outputBuffer[x+2][y+i];
		outputBuffer[x+2][y+i] = tempColor;
		
		tempColor = outputBuffer[x+4][y+i];
		outputBuffer[x+4][y+i] = outputBuffer[x+3][y+i];
		outputBuffer[x+3][y+i] = tempColor;
	}
	
}
	
	

int backgroundBufferFill(void *arguments){
	void** args = (void*)arguments;

	char* backgroundBufferComplete = (char*)args[0];
	char* beginFillingBackgroundBuffer = (char*)args[1];
	
	int i,j;
	unsigned int currTile;
	int tileOffsetX;
	int tileOffsetY;
	
	unsigned char *BGTileMap = NULL;
	
	int (*backgroundBuffer)[144] = args[2];
	//drawBuffer backgroundBuffer;
	//backgroundBuffer = args[2];

	int* basePalette = (int*)args[3];
	
	int bgPalette[4];
	
	//char tilesBuffered[160][144];
	
	while(1){
		//while(*beginFillingBackgroundBuffer == 0);
		SDL_SemWait(backgroundStartSem);
		//SDL_SemWait(backgroundSem);
		*beginFillingBackgroundBuffer = 0;
		*backgroundBufferComplete = 0;
		
		//memset(tilesBuffered,0,160*144);
		memset(backgroundBuffer,0,160*144);
		
		if(getLCDControl()&LCD_CONTROL_BG_ENABLE){
		
			if((getLCDControl()&LCD_CONTROL_BG_TILE_MAP)==0){
				BGTileMap = vramBanks+0x1800;
			} else {
				BGTileMap = vramBanks+0x1C00;
			}
		
			bgPalette[0] = basePalette[getBGPaletteData()&0x3];
			bgPalette[1] = basePalette[(getBGPaletteData()&0xC)>>2];
			bgPalette[2] = basePalette[(getBGPaletteData()&0x30)>>4];
			bgPalette[3] = basePalette[(getBGPaletteData()&0xC0)>>6];
			
			for(i=-1;i<TILES_PER_COLUMN;i++){
				for(j=-1;j<TILES_PER_ROW;j++){
				
					tileOffsetX = getscrollX()/8 + j;
					if(tileOffsetX >= 32){
						tileOffsetX-=32;
					}
					tileOffsetY = getscrollY()/8 + i;
					if(tileOffsetY >= 32){
						tileOffsetY-=32;
					}
										
					currTile = (unsigned int)BGTileMap[tileOffsetY*32+tileOffsetX]&0xFF;				
					
					if(getLCDControl()&LCD_CONTROL_BG_TILE_DATA){
						drawBGTileToBuffer(currTile&0x1FF,backgroundBuffer,j*8+(getscrollX()%8),i*8+(getscrollY()%8),bgPalette);
					} else {
						if(currTile<0x80){
							drawBGTileToBuffer((currTile+0x100)&0x1FF,backgroundBuffer,j*8+(getscrollX()%8),i*8+(getscrollY()%8),bgPalette);
						} else {
							drawBGTileToBuffer((currTile)&0x1FF,backgroundBuffer,j*8+(getscrollX()%8),i*8+(getscrollY()%8),bgPalette);
						}
					}
						
					/*if((((*LCDControl)&LCD_CONTROL_BG_TILE_DATA)==0)&&(currTile<0x80)){
						currTile+=128;
					}
					drawBGTileToBuffer(currTile&0x1FF,backgroundBuffer,j*8+(*scrollX%8),i*8+(*scrollY%8),bgPalette);
					*/
				}
			}
		
		} else {
			for(i=0;i<144;i++){
				for(j=0;j<160;j++){
					backgroundBuffer[j][i] = basePalette[0];
				}
			}
		}
		
		*backgroundBufferComplete = 1;
		SDL_SemPost(backgroundEndSem);
	}	
	
	return 0;
}

int windowBufferFill(void *arguments){
	void** args = (void*)arguments;

	char* windowBufferComplete = (char*)args[0];
	char* beginFillingWindowBuffer = (char*)args[1];
	int (*windowBuffer)[144] = args[2];
	
	
	int* basePalette = (int*)args[3];
	
	int windowPalette[4];
	
	
	char *BGTileMap = NULL;
	
	int i,j;
	unsigned int currTile;
	
	while(1){
		SDL_SemWait(windowStartSem);
		*beginFillingWindowBuffer = 0;
		*windowBufferComplete = 0;

		for(i=0;i<144;i++){
			for(j=0;j<160;j++){
				windowBuffer[j][i] = basePalette[4];
			}
		}
	
	
		if(getLCDControl()&LCD_CONTROL_WINDOW_ENABLE){ 
			
			if((getWX()<167)&&(getWY()<144)){	//Window on screen
				
				if((getLCDControl()&LCD_CONTROL_WINDOW_TILE_MAP)==0){
					BGTileMap = (char*)(vramBanks+0x1800);
				} else {
					BGTileMap = (char*)(vramBanks+0x1C00);
				}
				
				windowPalette[0] = basePalette[getBGPaletteData()&0x3];
				windowPalette[1] = basePalette[(getBGPaletteData()&0xC)>>2];
				windowPalette[2] = basePalette[(getBGPaletteData()&0x30)>>4];
				windowPalette[3] = basePalette[(getBGPaletteData()&0xC0)>>6];
				
				for(i=0;i*8+(getWX()-7)<160;i++){
					for(j=0;j*8+getWY()<144;j++){
						currTile = BGTileMap[i*32+j];
						currTile += 128;	//Make the number unsigned
						
						drawBGTileToBuffer(0x81,windowBuffer,i*8+getWX()-7,j*8+getWY(),windowPalette);
					}
				}
			}
			
		}
		
		*windowBufferComplete = 1;
		SDL_SemPost(windowEndSem);
	}
	
	return 0;
}
	
int spriteBufferFill(void *arguments){
	void** args = (void*)arguments;

	char* backSpriteBufferComplete = (char*)args[0];
	char* frontSpriteBufferComplete = (char*)args[1];
	char* beginFillingSpriteBuffer = (char*)args[2];
	int (*backSpriteBuffer)[144] = args[3];
	int (*frontSpriteBuffer)[144] = args[4];
	
	int* basePalette = (int*)args[5];
	
	int sprite0Palette[4];
	int sprite1Palette[4];

	OAMEntry *OAMTableEntry = (OAMEntry*)OAMTable;
	
	int numSpritesPerLine[144];	//Holds the number of sprites per line. Max of 10
	int i,j;
	int tooManySprites;			//Should be a boolean type
	unsigned char spriteY,spriteX;
	char spriteTileNum,spriteFlags;
	
	SpriteList* firstSprite = NULL;
	SpriteList* currSprite = NULL;	
	
	//Create an initial setup for the Sprite Linked List
	firstSprite = (SpriteList*)malloc(sizeof(SpriteList));
	currSprite = firstSprite;
	for(i=0;i<39;i++){
		currSprite->spriteNum = i;
		currSprite->next = (SpriteList*)malloc(sizeof(SpriteList));
		currSprite = currSprite->next;
	}
	currSprite->spriteNum = 39;
	currSprite->next = NULL;

   memset(backSpriteBuffer, 0x80, 144 * 160 * 4);
   memset(frontSpriteBuffer, 0x80, 144 * 160 * 4);
	
	while(1){
		//while(*beginFillingSpriteBuffer == 0);
		SDL_SemWait(spriteStartSem);
		//SDL_SemWait(spriteSem);
		*backSpriteBufferComplete = 0;
		*frontSpriteBufferComplete = 0;
		*beginFillingSpriteBuffer = 0;
		
		if(getLCDControl()&LCD_CONTROL_SPRITE_ENABLE){
			if(spriteTableChanged == 1){	//The table must be rearranged
				spriteTableChanged = 0;
			}
			
			for(i=0;i<144;i++){
				numSpritesPerLine[i] = 0;	//Reset the sprite count
			}
			
			//Fill the Palettes
			sprite0Palette[0] = basePalette[4];
			for(i=1;i<4;i++){
				switch((getobj0Palette()>>(i*2))&0x3){
					case 0:
						sprite0Palette[i] = basePalette[0];
						break;
					case 1:
						sprite0Palette[i] = basePalette[1];
						break;
					case 2:
						sprite0Palette[i] = basePalette[2];
						break;
					case 3:
						sprite0Palette[i] = basePalette[3];
						break;
				}
			}
			
			sprite1Palette[0] = basePalette[4];
			for(i=1;i<4;i++){
				switch((getobj1Palette()>>(i*2))&0x3){
					case 0:
						sprite1Palette[i] = basePalette[0];
						break;
					case 1:
						sprite1Palette[i] = basePalette[1];
						break;
					case 2:
						sprite1Palette[i] = basePalette[2];
						break;
					case 3:
						sprite1Palette[i] = basePalette[3];
						break;
				}
			}
			
			for(i=0;i<144;i++){
				for(j=0;j<160;j++){
					backSpriteBuffer[j][i] = basePalette[4];
					frontSpriteBuffer[j][i] = basePalette[4];
				}
			}
			
			for(currSprite = firstSprite;currSprite!=NULL;currSprite = currSprite->next){
				spriteY = OAMTableEntry[currSprite->spriteNum].Y;
				spriteX = OAMTableEntry[currSprite->spriteNum].X;
				spriteTileNum = OAMTableEntry[currSprite->spriteNum].tile;
				spriteFlags = OAMTableEntry[currSprite->spriteNum].flags;
				
				if(spriteY<160 && spriteX<144){	//Outside of range, don't draw
					tooManySprites = 0;
					
					for(i=0;i<8;i++){	//Checks for too many sprites
						if((i+spriteY)>=144){
							break;
						}
						if(numSpritesPerLine[i+spriteY]>=10){
							tooManySprites = 1;
							break;
						}
					}
					
					
					
					if(tooManySprites == 0){	//If there weren't too many sprites
						//printf("Adding sprite: %d to line: %d total: %d\n",currSprite->spriteNum,spriteY,numSpritesPerLine[spriteY]);
					
						for(i=0;i<8;i++){		//First increment the sprites per line
							if((i+spriteY)>=144){
								break;
							}
							numSpritesPerLine[i+spriteY]++;
						}
						
						//printf("Drawing spriteNum: %d\n",currSprite->spriteNum);
						
						//Draw the actual sprites
						if((getLCDControl()&LCD_CONTROL_SPRITE_8X16) == 0){
							//8x8 Sprites
							if((spriteFlags&OAM_FLAG_PRIORITY)==0){
								//Above Background
								if((spriteFlags&OAM_FLAG_PALETTE)==0){
									drawBGTileToBuffer(spriteTileNum&0xFF,frontSpriteBuffer,spriteX-8,spriteY-16,sprite0Palette);
								} else {
									drawBGTileToBuffer(spriteTileNum&0xFF,frontSpriteBuffer,spriteX-8,spriteY-16,sprite1Palette);
								}
								
								if(spriteFlags&OAM_FLAG_XFLIP){
								///	printf("Sprite being flipped\n");
									reverseTile(frontSpriteBuffer,spriteX-8,spriteY-16);
								}
							} else {
								//Below Background
								if((spriteFlags&OAM_FLAG_PALETTE)==0){
									drawBGTileToBuffer(spriteTileNum&0xFF,backSpriteBuffer,spriteX-8,spriteY-16,sprite0Palette);
								} else {
									drawBGTileToBuffer(spriteTileNum&0xFF,backSpriteBuffer,spriteX-8,spriteY-16,sprite1Palette);
								}
								
								if(spriteFlags&OAM_FLAG_XFLIP){
									//printf("Sprite being flipped\n");
									reverseTile(backSpriteBuffer,spriteX-8,spriteY-16);
								}
							}
						} else {
							//8x16 Sprites
							if((spriteFlags&OAM_FLAG_PRIORITY)==0){
								//Above Background
								if((spriteFlags&OAM_FLAG_PALETTE)==0){
									drawBGTileToBuffer(spriteTileNum&0xFE,frontSpriteBuffer,spriteX-8,spriteY-16,sprite0Palette);
									drawBGTileToBuffer((spriteTileNum&0xFE)+1,frontSpriteBuffer,spriteX-8,spriteY-8,sprite0Palette);
								} else {
									drawBGTileToBuffer(spriteTileNum&0xFE,frontSpriteBuffer,spriteX-8,spriteY-16,sprite1Palette);
									drawBGTileToBuffer((spriteTileNum&0xFE)+1,frontSpriteBuffer,spriteX-8,spriteY-8,sprite1Palette);
								}
								
								if(spriteFlags&OAM_FLAG_XFLIP){
									//printf("Sprite being flipped\n");
									reverseTile(frontSpriteBuffer,spriteX-8,spriteY-16);
									reverseTile(frontSpriteBuffer,spriteX-8,spriteY-8);
								}
							} else {
								//Below Background
								if((spriteFlags&OAM_FLAG_PALETTE)==0){
									drawBGTileToBuffer(spriteTileNum&0xFE,backSpriteBuffer,spriteX-8,spriteY-16,sprite0Palette);
									drawBGTileToBuffer((spriteTileNum&0xFE)+1,backSpriteBuffer,spriteX-8,spriteY-8,sprite0Palette);
								} else {
									drawBGTileToBuffer(spriteTileNum&0xFE,backSpriteBuffer,spriteX-8,spriteY-16,sprite1Palette);
									drawBGTileToBuffer((spriteTileNum&0xFE)+1,backSpriteBuffer,spriteX-8,spriteY-8,sprite1Palette);
								}
								
								if(spriteFlags&OAM_FLAG_XFLIP){
									//printf("Sprite being flipped\n");
									reverseTile(backSpriteBuffer,spriteX-8,spriteY-16);
									reverseTile(backSpriteBuffer,spriteX-8,spriteY-8);
								}
							}
						}
					}
				}
			}
		}
		//Done drawing for this cycle		
		*backSpriteBufferComplete = 1;
		*frontSpriteBufferComplete = 1;
		*beginFillingSpriteBuffer = 0;

		SDL_SemPost(spriteEndSem);
	}
	return 0;
}			
	
int drawVideo(void* args){
	
	char backSpriteBufferComplete = 0;
	char frontSpriteBufferComplete = 0;
	char backgroundBufferComplete = 0;
	char windowBufferComplete = 0;
	
	char beginFillingBackgroundBuffer = 0;
	char beginFillingWindowBuffer = 0;
	char beginFillingSpriteBuffer = 0;
	
	SDL_Thread *backgroundBufferFillThread = NULL;
	SDL_Thread *windowBufferFillThread = NULL;
	SDL_Thread *spriteBufferFillThread = NULL;
	
	void* backgroundArgs[4];
	void* windowArgs[4];
	void* spriteArgs[6];
	
	int i,j;

	
	drawBuffer backgroundBuffer;
	drawBuffer windowBuffer;
	drawBuffer backSpriteBuffer;
	drawBuffer frontSpriteBuffer;
	
	unsigned int currTime;
	unsigned int prevTime = 0;
	int framesElapsed = 0;
	
	printf("Video Thread Started!\n");
   
   SDL_PixelFormat* pixelFormat = SDL_AllocFormat(PIXEL_FORMAT);

	int colorWhite = SDL_MapRGB(pixelFormat, 0xFF, 0xFF, 0xFF);
	int colorLightGray = SDL_MapRGB(pixelFormat, 0xAA, 0xAA, 0xAA);
	int colorDarkGray = SDL_MapRGB(pixelFormat, 0x55, 0x55, 0x55);
	int colorBlack = SDL_MapRGB(pixelFormat, 0, 0, 0);
   int colorTransparent = SDL_MapRGBA(pixelFormat, 0x80, 0x80, 0x80, 0x80);
	
	int basePalette[5];
   basePalette[4] = colorTransparent;
	basePalette[3] = colorBlack;
	basePalette[2] = colorDarkGray;
	basePalette[1] = colorLightGray;
	basePalette[0] = colorWhite;


	backgroundArgs[0] = &backgroundBufferComplete;
	backgroundArgs[1] = &beginFillingBackgroundBuffer;
	backgroundArgs[2] = backgroundBuffer;
   backgroundArgs[3] = basePalette;
	
	windowArgs[0] = &windowBufferComplete;
	windowArgs[1] = &beginFillingWindowBuffer;
	windowArgs[2] = windowBuffer;
   windowArgs[3] = basePalette;
	
	spriteArgs[0] = &backSpriteBufferComplete;
	spriteArgs[1] = &frontSpriteBufferComplete;
	spriteArgs[2] = &beginFillingSpriteBuffer;
	spriteArgs[3] = backSpriteBuffer;
	spriteArgs[4] = frontSpriteBuffer;
   spriteArgs[5] = basePalette;
	
	spriteStartSem = SDL_CreateSemaphore(0);
	windowStartSem = SDL_CreateSemaphore(0);
	backgroundStartSem = SDL_CreateSemaphore(0);

	spriteEndSem = SDL_CreateSemaphore(0);
	windowEndSem = SDL_CreateSemaphore(0);
	backgroundEndSem = SDL_CreateSemaphore(0);
	
	backgroundBufferFillThread = SDL_CreateThread(backgroundBufferFill, "Background Draw", backgroundArgs);
	if(backgroundBufferFillThread == NULL){
		printf("Unable to create backgroundBufferFillThread Exiting!!!\n");
		exit(1);
	}
	
	windowBufferFillThread = SDL_CreateThread(windowBufferFill, "Window Draw", windowArgs);
	if(windowBufferFillThread == NULL){
		printf("Unable to create windowBufferFillThread Exiting!!!\n");
		exit(1);
	}
	
	spriteBufferFillThread = SDL_CreateThread(spriteBufferFill, "Sprite Draw", spriteArgs);
	if(spriteBufferFillThread == NULL){
		printf("Unable to create spriteBufferFillThread Exiting!!!\n");
		exit(1);
	}
	
	drawingComplete=1;

	while(1){
		SDL_SemWait(fillBuffersSem);
	   SDL_SemPost(spriteStartSem);
		SDL_SemPost(windowStartSem);
		SDL_SemPost(backgroundStartSem);

		SDL_SemWait(spriteEndSem);
		SDL_SemWait(windowEndSem);
		SDL_SemWait(backgroundEndSem);
			
		buffersFull = 1;
		shouldFillBuffers = 0;
		
		SDL_SemWait(drawVideoStartSem);

   	for(i=0;i<160;i++){
   		for(j=0;j<144;j++){
            renderScreen[j][i] = backgroundBuffer[i][j];

				if(checkForWhite(backgroundBuffer[i][j])){	//If background color is 0
					if(!hasAlpha(backSpriteBuffer[i][j])){
                    renderScreen[j][i] = backSpriteBuffer[i][j]; 
               }
				} 

				if(!hasAlpha(windowBuffer[i][j])){
                 renderScreen[j][i] = windowBuffer[i][j];
		      }

				if(!hasAlpha(frontSpriteBuffer[i][j])){
                 renderScreen[j][i] = frontSpriteBuffer[i][j];
				}
			}
		}

      SDL_SemPost(drawOnMainThreadSem);
         			
		if(framesElapsed == 60){
			framesElapsed = 0;
			currTime = SDL_GetTicks();
			
			if((currTime-prevTime)<1000){	//Updating more than 60 times per second
				printf("Delaying fps\n");
				SDL_Delay(1000-(currTime-prevTime));
			} else {
				printf("fps: %f\n",60./((float)(currTime-prevTime)/1000.));
			}
			
			prevTime = currTime;
			
			
		} else {
			framesElapsed++;
		}
		
		
		shouldRedraw = 0;
		drawingComplete = 1;

	   SDL_SemPost(drawVideoCompleteSem);
	}
}
	
void initVideo(){
	
	SDL_Thread *drawThread;

	fillBuffersSem = SDL_CreateSemaphore(0);
	drawVideoStartSem = SDL_CreateSemaphore(0);
	drawVideoCompleteSem = SDL_CreateSemaphore(1);
   drawOnMainThreadSem = SDL_CreateSemaphore(0);

	if(SDL_CreateWindowAndRenderer(160, 144, SDL_WINDOW_SHOWN, &window, &renderer) == -1) {
		printf("Display could not be created!!!\n");
		exit(0);
	}	

   if(window == NULL) {
      printf("Window NULL\n");
      exit(0);
   }

   if(renderer == NULL) {
      printf("Renderer NULL\n");
      exit(0);
   }

   SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
   //SDL_RenderSetLogicalSize(renderer, 160, 144);
   SDL_RenderSetLogicalSize(renderer, 160, 144);


   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
   SDL_RenderClear(renderer);
   SDL_RenderPresent(renderer);

   screenTexture = SDL_CreateTexture(renderer, PIXEL_FORMAT, SDL_TEXTUREACCESS_STREAMING, 160, 144);
	if(screenTexture == NULL){
		printf("Unable to create screenBuffer Exiting!!!\n");
		exit(1);
	}	
	drawThread = SDL_CreateThread(drawVideo, "Video", NULL);
	if(drawThread == NULL){
		printf("Couldn't create drawThread!!!\n");
		exit(0);
   }

}	

void drawVideoFromMain() {

   if(SDL_SemValue(drawOnMainThreadSem) > 0) {
      SDL_SemWait(drawOnMainThreadSem);

      SDL_RenderClear(renderer);

      if(SDL_UpdateTexture(screenTexture, NULL, renderScreen, 640) == -1) {
         printf("Unable to update Texture\n");
      }

      SDL_RenderCopy(renderer, screenTexture, NULL, NULL);
      SDL_RenderPresent(renderer);

   }

   
}



