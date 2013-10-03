
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
#include "SDL_rotozoom.h"

#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>

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


int shouldFillBuffers = 0;	//Will be set to 1 when screen buffers should be filled
int shouldRedraw = 0;		//Will be set when entire screen should be blitted to the screen
int drawingComplete = 0;	//Will be set to 1 when a new line can be drawn
int buffersFull = 0;		//Will be set to 1 when buffers are full and ready for drawing
int spriteTableChanged = 1;	//Will be set to one when the list needs to be sorted

int BGDrawBuffer[160][144];
int windowDrawBuffer[160][144];
int spriteBackBuffer[160][144];	//Behind background
int spriteFrontBuffer[160][144];

SDL_Surface *display;

typedef int drawBuffer[160][144];

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

void dummyFunct2(){
	return;
}

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
	
char getColorForTile(tileData* tile,int row, int column){
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
			while(drawingComplete == 0);
			drawingComplete = 0;
			(*LY) = 0;
			*LCDStatus=((*LCDStatus)&0xFC)|LCD_MODE2;			
			shouldFillBuffers=1;
			
			//If Mode 2 interrupt enabled
			if(((*LCDStatus)&0x20)!=0){
				(*interruptFlags) = (*interruptFlags)|0x2;	//Set LCD STAT Interrupt
			}
			if(*LY==*LYC){
				*LCDStatus = ((*LCDStatus)&0xFB)|0x4;	//Set Coincidence Flag
				(*interruptFlags) = (*interruptFlags)|0x2;	//Set LCD STAT Interrupt Request
			} else {
				*LCDStatus = (*LCDStatus)&0xFB;	//Otherwise clear it
			}	
		} else {
			temp = screenRefreshCount%456;
			if(temp==0){	//Switch To Mode 2
				*LCDStatus=((*LCDStatus)&0xFC)|LCD_MODE2;
				*LY =(*LY)+1;				
				
				//If Mode 2 interrupt enabled
				if(((*LCDStatus)&0x20)!=0){
					(*interruptFlags) = (*interruptFlags)|0x2;	//Set LCD STAT Interrupt
				}
				
				if(*LY==*LYC){	//If LY and LYC are equal
					*LCDStatus = ((*LCDStatus)&0xFB)|0x4;	//Set Coincidence Flag
					(*interruptFlags) = (*interruptFlags)|0x2;	//Set LCD STAT Interrupt Request
				} else {
					*LCDStatus = (*LCDStatus)&0xFB;	//Otherwise clear it
				}	
			} else if(temp==77){
				*LCDStatus=((*LCDStatus)&0xFC)|LCD_MODE3;
			} else if(temp==249){
				*LCDStatus=((*LCDStatus)&0xFC)|LCD_MODE0;
				if(((*LCDStatus)&0x4)!=0){	//If Mode 0 flag set
					(*interruptFlags) = (*interruptFlags)|0x2;	//Set LCD STAT Interrupt
				}	
			}
		}	
	} else if(screenRefreshCount==65664){	//V-Blank Start
	
	
		buffersFull = 0;
		shouldRedraw = 1;
		*LCDStatus=((*LCDStatus)&0xFC)|LCD_MODE1;
		*LY = (*LY) + 1;
		
		if(((*LCDStatus)&0x8)!=0){
			(*interruptFlags) = (*interruptFlags)|0x2;	//Set LCD STAT Interrupt
		}	
		
		(*interruptFlags) = (*interruptFlags)|0x1;	//Set V-Blank Interrupt
		
		if(*LY==*LYC){	//If LY and LYC are equal
			*LCDStatus = ((*LCDStatus)&0xFB)|0x4;	//Set Coincidence Flag
			(*interruptFlags) = (*interruptFlags)|0x2;	//Set LCD STAT Interrupt Request
		} else {
			*LCDStatus = (*LCDStatus)&0xFB;	//Otherwise clear it
		}
	} else if((screenRefreshCount%456)==0){
		*LY = (*LY)+1;
		if(*LY==*LYC){	//If LY and LYC are equal
			*LCDStatus = ((*LCDStatus)&0xFB)|0x4;	//Set Coincidence Flag
			(*interruptFlags) = (*interruptFlags)|0x2;	//Set LCD STAT Interrupt Request
		} else {
			*LCDStatus = (*LCDStatus)&0xFB;	//Otherwise clear it
		}
	}	
}

void putPixelSDL(int x,int y,int value,SDL_Surface *dest){
	int* displayPixels = (int*)dest->pixels;

	displayPixels[y*(SCREEN_WIDTH)+x] = value;
}

char getAlpha(int pixel){
	/*char r;
	char g;
	char b;
	char a;
	
	SDL_GetRGBA(pixel,display->format,&r,&g,&b,&a);
	
	return a;*/
	return pixel>>24;
}

int checkForWhite(int pixel){
	/*char r,g,b,a;
	
	SDL_GetRGBA(pixel,display->format,&r,&g,&b,&a);
	
	if((r==0xFF)&&(g==0xFF)&&(b==0xFF)){
		return 1;
	} else {
		return 0;
	}*/
	
	if((pixel&0xFFFFFF) == 0xFFFFFF){
		return 1;
	} else {
		return 0;
	}
	
}

void drawBGTileToBuffer(unsigned int tileNum,drawBuffer outputBuffer,int x,int y,int palette[4]){
	
	tileData* currTile = (tileData*)&vramBanks[tileNum*sizeof(tileData)];
	
	int tileRow,tileColumn;
	
	/*if((tileNum&0xFF)==0xB1){
		//printf("Drawing Tile 0xB1 to X: %d\t Y: %d\n",x,y);
	}*/	
	
	if((x<=-8)||(x>160)){
		return;
	}
	if((y<=-8)||(y>144)){
		return;
	}
	
	dummyFunct2();
	
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
	
	tileData *BGTileData = (tileData*)vramBanks;
	char *BGTileMap = NULL;
	
	int (*backgroundBuffer)[144] = args[2];
	//drawBuffer backgroundBuffer;
	//backgroundBuffer = args[2];
	
	int colorWhite = SDL_MapRGB(display->format,0xFF,0xFF,0xFF);
	int colorLightGray = SDL_MapRGB(display->format,0xAA,0xAA,0xAA);
	int colorDarkGray = SDL_MapRGB(display->format,0x55,0x55,0x55);
	int colorBlack = SDL_MapRGB(display->format,0,0,0);
	
	printf("white: %d\n",checkForWhite(colorWhite));
	
	int basePalette[4];
	basePalette[3] = colorBlack;
	basePalette[2] = colorDarkGray;
	basePalette[1] = colorLightGray;
	basePalette[0] = colorWhite;
	
	int bgPalette[4];
	
	//char tilesBuffered[160][144];
	
	while(1){
		while((*beginFillingBackgroundBuffer)==0){
			//Nothing
		}
		*beginFillingBackgroundBuffer = 0;
		*backgroundBufferComplete = 0;
		
		//memset(tilesBuffered,0,160*144);
		memset(backgroundBuffer,0,160*144);
		
		if((*LCDControl)&LCD_CONTROL_BG_ENABLE){
		
			if(((*LCDControl)&LCD_CONTROL_BG_TILE_MAP)==0){
				BGTileMap = vramBanks+0x1800;
			} else {
				BGTileMap = vramBanks+0x1C00;
			}
		
			bgPalette[0] = basePalette[(*BGPaletteData)&0x3];
			bgPalette[1] = basePalette[((*BGPaletteData)&0xC)>>2];
			bgPalette[2] = basePalette[((*BGPaletteData)&0x30)>>4];
			bgPalette[3] = basePalette[((*BGPaletteData)&0xC0)>>6];
			
			for(i=-1;i<TILES_PER_COLUMN;i++){
				for(j=-1;j<TILES_PER_ROW;j++){
				
					tileOffsetX = (*scrollX)/8 + j;
					if(tileOffsetX >= 32){
						tileOffsetX-=32;
					}
					tileOffsetY = (*scrollY)/8 + i;
					if(tileOffsetY >= 32){
						tileOffsetY-=32;
					}
										
					currTile = (unsigned int)BGTileMap[tileOffsetY*32+tileOffsetX]&0xFF;				
					
					if((*LCDControl)&LCD_CONTROL_BG_TILE_DATA){
						drawBGTileToBuffer(currTile&0x1FF,backgroundBuffer,j*8+(*scrollX%8),i*8+(*scrollY%8),bgPalette);
					} else {
						if(currTile<0x80){
							drawBGTileToBuffer((currTile+0x100)&0x1FF,backgroundBuffer,j*8+(*scrollX%8),i*8+(*scrollY%8),bgPalette);
						} else {
							drawBGTileToBuffer((currTile)&0x1FF,backgroundBuffer,j*8+(*scrollX%8),i*8+(*scrollY%8),bgPalette);
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
					backgroundBuffer[j][i] = colorWhite;
				}
			}
		}
		
		*backgroundBufferComplete = 1;
	}	
	
	return;
}

int windowBufferFill(void *arguments){
	void** args = (void*)arguments;

	char* windowBufferComplete = (char*)args[0];
	char* beginFillingWindowBuffer = (char*)args[1];
	int (*windowBuffer)[144] = args[2];
	
	int colorTransparent = SDL_MapRGBA(display->format,255,255,255,0);	
	int colorWhite = SDL_MapRGB(display->format,0xFF,0xFF,0xFF);
	int colorLightGray = SDL_MapRGB(display->format,0xAA,0xAA,0xAA);
	int colorDarkGray = SDL_MapRGB(display->format,0x55,0x55,0x55);
	int colorBlack = SDL_MapRGB(display->format,0,0,0);
	
	int basePalette[4];
	basePalette[3] = colorBlack;
	basePalette[2] = colorDarkGray;
	basePalette[1] = colorLightGray;
	basePalette[0] = colorWhite;
	
	int windowPalette[4];
	
	
	tileData *BGTileData = (tileData*)vramBanks;
	char *BGTileMap = NULL;
	
	int i,j;
	unsigned int currTile;
	
	while(1){
		while(*beginFillingWindowBuffer==0){
		}
		*beginFillingWindowBuffer = 0;
		*windowBufferComplete = 0;
		
		for(i=0;i<144;i++){
			for(j=0;j<160;j++){
				windowBuffer[j][i] = colorTransparent;
			}
		}
		
		if(((*LCDControl)&LCD_CONTROL_WINDOW_ENABLE)!=0){
			
			
			if(((*WX)<167)&&((*WY)<144)){	//Window on screen
				
				if(((*LCDControl)&LCD_CONTROL_WINDOW_TILE_MAP)==0){
					BGTileMap = (char*)(vramBanks+0x1800);
				} else {
					BGTileMap = (char*)(vramBanks+0x1C00);
				}
				
				windowPalette[0] = basePalette[(*BGPaletteData)&0x3];
				windowPalette[1] = basePalette[((*BGPaletteData)&0xC)>>2];
				windowPalette[2] = basePalette[((*BGPaletteData)&0x30)>>4];
				windowPalette[3] = basePalette[((*BGPaletteData)&0xC0)>>6];
				
				for(i=0;i*8+((*WX)-7)<160;i++){
					for(j=0;j*8+(*WY)<144;j++){
						currTile = BGTileMap[i*32+j];
						currTile += 128;	//Make the number unsigned
						
						drawBGTileToBuffer(0x81,windowBuffer,i*8+((*WX)-7),j*8+(*WY),windowPalette);
					}
				}
			}
			
		}
		
		*windowBufferComplete = 1;
	}
	
	return;
}
	
int spriteBufferFill(void *arguments){
	void** args = (void*)arguments;

	char* backSpriteBufferComplete = (char*)args[0];
	char* frontSpriteBufferComplete = (char*)args[1];
	char* beginFillingSpriteBuffer = (char*)args[2];
	int (*backSpriteBuffer)[144] = args[3];
	int (*frontSpriteBuffer)[144] = args[4];
	
	int colorTransparent = 0xAA000000;	//Top 8 bits unused. Will use to mask out invisible pixels
	int colorWhite = SDL_MapRGB(display->format,0xFF,0xFF,0xFF);
	int colorLightGray = SDL_MapRGB(display->format,0xAA,0xAA,0xAA);
	int colorDarkGray = SDL_MapRGB(display->format,0x55,0x55,0x55);
	int colorBlack = SDL_MapRGB(display->format,0,0,0);
	
	printf("Alpha Value of transparent: %X\n",colorTransparent);
	
	int basePalette[4];
	basePalette[3] = colorBlack;
	basePalette[2] = colorDarkGray;
	basePalette[1] = colorLightGray;
	basePalette[0] = colorWhite;
	
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
	
	/*for(currSprite = firstSprite;currSprite!=NULL;currSprite = currSprite->next){
		printf("currSprite: %d\n",currSprite->spriteNum);
	}*/
	
	while(1){
		while(*beginFillingSpriteBuffer == 0);
		*backSpriteBufferComplete = 0;
		*frontSpriteBufferComplete = 0;
		*beginFillingSpriteBuffer = 0;
		
		if(*(LCDControl)&LCD_CONTROL_SPRITE_ENABLE){
			if(spriteTableChanged == 1){	//The table must be rearranged
				//spriteListSort(&firstSprite,NULL);
				spriteTableChanged = 0;
			}
			
			for(i=0;i<144;i++){
				numSpritesPerLine[i] = 0;	//Reset the sprite count
			}
			
			//Fill the Palettes
			sprite0Palette[0] = colorTransparent;
			for(i=1;i<4;i++){
				switch(((*obj0Palette)>>(i*2))&0x3){
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
			
			sprite1Palette[0] = colorTransparent;
			for(i=1;i<4;i++){
				switch(((*obj1Palette)>>(i*2))&0x3){
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
					backSpriteBuffer[j][i] = colorTransparent;
					frontSpriteBuffer[j][i] = colorTransparent;
				}
			}
			
			/*for(currSprite = firstSprite;currSprite!=NULL;currSprite = currSprite->next){
				printf("spriteNum: %d\n",currSprite->spriteNum);
			}*/
			
			for(currSprite = firstSprite;currSprite!=NULL;currSprite = currSprite->next){
				spriteY = OAMTableEntry[currSprite->spriteNum].Y;
				spriteX = OAMTableEntry[currSprite->spriteNum].X;
				spriteTileNum = OAMTableEntry[currSprite->spriteNum].tile;
				spriteFlags = OAMTableEntry[currSprite->spriteNum].flags;
				
				if((spriteY>=0)&&(spriteY<160)){	//Outside of range, don't draw
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
						if(((*LCDControl)&LCD_CONTROL_SPRITE_8X16) == 0){
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
	}
	return;
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
	
	void* backgroundArgs[3];
	void* windowArgs[3];
	void* spriteArgs[5];
	
	int i,j,a,b;
	
	int* enlargePixelData;
	
	SDL_Surface* screenBitmap = NULL;
	SDL_Surface* enlargedBitmap = NULL;
	
	SDL_Rect topLeftRect;
	
	
	drawBuffer backgroundBuffer;
	drawBuffer windowBuffer;
	drawBuffer backSpriteBuffer;
	drawBuffer frontSpriteBuffer;
	
	double fps;
	unsigned int currTime;
	unsigned int prevTime;
	int framesElapsed = 0;
	
	printf("Video Thread Started!\n");


	backgroundArgs[0] = &backgroundBufferComplete;
	backgroundArgs[1] = &beginFillingBackgroundBuffer;
	backgroundArgs[2] = backgroundBuffer;
	
	windowArgs[0] = &windowBufferComplete;
	windowArgs[1] = &beginFillingWindowBuffer;
	windowArgs[2] = windowBuffer;
	
	spriteArgs[0] = &backSpriteBufferComplete;
	spriteArgs[1] = &frontSpriteBufferComplete;
	spriteArgs[2] = &beginFillingSpriteBuffer;
	spriteArgs[3] = backSpriteBuffer;
	spriteArgs[4] = frontSpriteBuffer;
	

	
	screenBitmap = SDL_CreateRGBSurface(SDL_SWSURFACE,160*WINDOW_SCALE,144*WINDOW_SCALE,32,0,0,0,0);
	if(screenBitmap == NULL){
		printf("Unable to create screenBuffer Exiting!!!\n");
		exit(1);
	}
	
	printf("Starting to create threads\n");	
	
	backgroundBufferFillThread = SDL_CreateThread(backgroundBufferFill,backgroundArgs);
	if(backgroundBufferFillThread == NULL){
		printf("Unable to create backgroundBufferFillThread Exiting!!!\n");
		exit(1);
	}
	
	windowBufferFillThread = SDL_CreateThread(windowBufferFill,windowArgs);
	if(windowBufferFillThread == NULL){
		printf("Unable to create windowBufferFillThread Exiting!!!\n");
		exit(1);
	}
	
	spriteBufferFillThread = SDL_CreateThread(spriteBufferFill,spriteArgs);
	if(spriteBufferFillThread == NULL){
		printf("Unable to create spriteBufferFillThread Exiting!!!\n");
		exit(1);
	}
	
	printf("Finished creating Threads\n");
	
	drawingComplete=1;

	while(1){
		if(shouldFillBuffers == 1){
			backSpriteBufferComplete = 1;
			frontSpriteBufferComplete = 1;
			backgroundBufferComplete = 0;
			windowBufferComplete = 1;
			
			beginFillingBackgroundBuffer = 1;
			beginFillingWindowBuffer = 1;
			beginFillingSpriteBuffer = 1;
			
			while(backSpriteBufferComplete==0);
			while(frontSpriteBufferComplete==0);
			while(backgroundBufferComplete==0);
			while(windowBufferComplete==0);
			
			buffersFull = 1;
			shouldFillBuffers = 0;
		
		} else if(shouldRedraw == 1){
			
			if(SDL_LockSurface(display) == -1){
				printf("Couldn't Lock display!!!\n");
			}
			
			for(i=0;i<160;i++){
				for(j=0;j<144;j++){
					putPixelSDL(i,j,backgroundBuffer[i][j],display);
					if(checkForWhite(backgroundBuffer[i][j]) == 1){	//If background color is 0
						//printf("Drawing backsprite\n");
						if((getAlpha(backSpriteBuffer[i][j])&0xFF) != 0xAA){
							//printf("Actually Drawing: %X\n",getAlpha(backSpriteBuffer[i][j])&0xFF);
							putPixelSDL(i,j,backSpriteBuffer[i][j],display);
						}
					}
					/*if(getAlpha(windowBuffer[i][j]) == 0){
						putPixelSDL(i,j,windowBuffer[i][j]);
					}*/
					if((getAlpha(frontSpriteBuffer[i][j])&0xFF) != 0xAA){
						//printf("Drawing sprite alpha: %hhX\n",getAlpha(frontSpriteBuffer[i][j]));
						
						putPixelSDL(i,j,frontSpriteBuffer[i][j],display);
					}
				}
			}
			
			SDL_UnlockSurface(display);
		
			enlargePixelData = (int*)screenBitmap->pixels;
			
			SDL_Flip(display);
			
			
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
			
		}
	}
}
	
void initVideo(){
	
	SDL_Thread *drawThread;

	display = SDL_SetVideoMode(160*WINDOW_SCALE,144*WINDOW_SCALE,32,SDL_SWSURFACE);
	if(display == NULL){
		printf("Display could not be created!!!\n");
		exit(0);
	}	
	
	drawThread = SDL_CreateThread(drawVideo,NULL);
	if(drawThread == NULL){
		printf("Couldn't create drawThread!!!\n");
		exit(0);
	}
	
}	



//Only used for testing the SpriteList structure and associated functions
/*
void testLinkedList(){
	
	int i;
	
	SpriteList *firstSprite;
	SpriteList *currSprite = NULL;	
	
	SpriteList *search;
	
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
	
	spriteListInsert(&firstSprite,getSpriteElement(&firstSprite,0),33);
	spriteListInsert(&firstSprite,getSpriteElement(&firstSprite,9),456);
	spriteListInsert(&firstSprite,getSpriteElement(&firstSprite,23),3433);
	spriteListInsert(&firstSprite,getSpriteElement(&firstSprite,25),454);
	spriteListInsert(&firstSprite,getSpriteElement(&firstSprite,19),87);
	spriteListInsert(&firstSprite,getSpriteElement(&firstSprite,35),14);
	spriteListInsert(&firstSprite,getSpriteElement(&firstSprite,2),10000);
	spriteListInsert(&firstSprite,getSpriteElement(&firstSprite,13),563);

	spriteListInsert(&firstSprite,getSpriteElement(&firstSprite,7),42);
	
	//spriteListDelete(&firstSprite,getSpriteElement(&firstSprite,0));
	//spriteListDelete(&firstSprite,getSpriteElement(&firstSprite,89332));
	
	//spriteListInsert(&firstSprite,getSpriteElement(&firstSprite,34),5534532);	
	
	for(currSprite = firstSprite;currSprite != NULL;currSprite = currSprite->next){
		printf("%d\n",currSprite->spriteNum);
	}
	
	unsigned int currSmallestNum;
	SpriteList *currSmallestSprite;
	SpriteList *sortSprite = firstSprite;
	currSprite = firstSprite;
	
	spriteListSort(&firstSprite,NULL);
	
	printf("\n\n");
	
	for(currSprite = firstSprite;currSprite != NULL;currSprite = currSprite->next){
		printf("%d\n",currSprite->spriteNum);
	}
	
}*/
