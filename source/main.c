#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>

#include "main.h"
#include "instructions.h"
#include "core.h"
#include "mem.h"
#include "video.h"
#include "io.h"
#include "video.h"
#include "dma.h"
#include "joypad.h"
#include "timer.h"
#include "instruction_count.h"

#define NO_STDIO_REDIRECT	1

#include <SDL2/SDL.h>

#define REGINST(num) registerInstruction(0x ## num,instruction ## num)

#define REGCB(num) registerCB(0x ## num,instructionCB ## num)

#define MAX_MEM	0xFFFF

#define MAX_MHZ	4
#define MAX_HZ (1024*1024*(MAX_MHZ))

#define MAX_PC_RECALL_LENGTH	500

#define BIT(x) (1<<(x))

#define RUN_COND_VBLANK		1
#define RUN_COND_NEXT		2
#define RUN_COND_UPTO		BIT(16)



int shouldDumpState;	//Set to 1 when memory and registers should be dumped

void registerInstruction(int num,opcodeInstruction instruction);
void registerCB(int num,opcodeInstruction instruction);

void dumpMemToFile(char* filename);
void dumpRegToFile(char* filename);
void printPermissionTable(char* filename);

void signal_INT_callback(int signum);

unsigned int screenRefreshCount=0;	

void PCRecallTest();

int runGameboy(void *args);

int main(int argc,char** argv){

	
	void* registers = (void*)malloc(12*2);
	char* cartHead = malloc(0x50);
	
	shouldDumpState = 0;
	
	//signal(SIGINT,signal_INT_callback);
	
	opcodes = (void*)malloc(SIZE_OF_INSTRUCTION*0x200);
	memset(opcodes,0,SIZE_OF_INSTRUCTION*0x200);
	
	memset(registers,0,24);
	registerList = registers;

	SDL_Init(SDL_INIT_EVERYTHING);
   
	//freopen( "CON", "w", stdout );
	//freopen( "CON", "w", stderr );
   printf("Opening ROM\n");
	
	FILE* romFile = fopen(argv[1],"rb");

   printf("Opened File\n");
	
	if(romFile == NULL){
		printf("Invalid File Submited: %s\n",argv[1]);
		exit(0);
	} else {
		printf("Reading file: %s\n",argv[1]);
	}
	fseek(romFile,0,SEEK_END); 
	unsigned int fileSize = ftell(romFile);
	rewind(romFile);
	
	//printf("Filesize: 0x%X\n",fileSize);	
	
	fseek(romFile,0x100,SEEK_SET);
	fread(cartHead,1,0x50,romFile);
	rewind(romFile);
	
	initMem(cartHead[0x48],cartHead[0x49],cartHead[0x47]);
	initIO();
	
	//printf("romMem: 0x%p  opcodes: 0x%p\n",romBanks,opcodes);

	#if LINUX == 1
		printf("Copied 0x%X Bytes\n",(unsigned int)fread(romBanks,1,fileSize,romFile));
	
	
	#else
	
		while(i<(fileSize/0x1000)){
		//printf("i: %d\n",i);
			if(fread(romBanks+i*0x1000,1,0x1000,romFile)!=0x1000){
				if(ferror(romFile)){
					printf("Error copying file to Memory!!!\n");
					printf("i: %d Copied %d bytes successfully\n",i,(i-1)*0x1000);
					perror(0);
					return 0;
				}
			}
		
			//fseek(romFile,i*1000,SEEK_SET);
			i++;
		}
		printf("Copied 0x%X Bytes\n",i*0x1000);	
	#endif		

	printf("Successfully loaded ROM\n");	
	
	
	{ //Register Instructions Here
	REGINST(00);
	REGINST(01);
	REGINST(02);
	REGINST(03);
	REGINST(04);
	REGINST(05);
	REGINST(06);
	REGINST(07);
	REGINST(08);
	REGINST(09);
	REGINST(0A);
	REGINST(0B);
	REGINST(0C);
	REGINST(0D);
	REGINST(0E);
	REGINST(0F);
	REGINST(10);
	REGINST(11);
	REGINST(12);
	REGINST(13);
	REGINST(14);
	REGINST(15);
	REGINST(16);
	REGINST(17);
	REGINST(18);
	REGINST(19);
	REGINST(1A);
	REGINST(1B);
	REGINST(1C);
	REGINST(1D);
	REGINST(1E);
	REGINST(1F);
	REGINST(20);
	REGINST(21);
	REGINST(22);
	REGINST(23);
	REGINST(24);
	REGINST(25);
	REGINST(26);
	REGINST(27);
	REGINST(28);
	REGINST(29);
	REGINST(2A);
	REGINST(2B);
	REGINST(2C);
	REGINST(2D);
	REGINST(2E);
	REGINST(2F);
	REGINST(30);
	REGINST(31);
	REGINST(32);
	REGINST(33);
	REGINST(34);
	REGINST(35);
	REGINST(36);
	REGINST(37);
	REGINST(38);
	REGINST(39);
	REGINST(3A);
	REGINST(3B);
	REGINST(3C);
	REGINST(3D);
	REGINST(3E);
	REGINST(3F);
	REGINST(40);
	REGINST(41);
	REGINST(42);
	REGINST(43);
	REGINST(44);
	REGINST(45);
	REGINST(46);
	REGINST(47);
	REGINST(48);
	REGINST(49);
	REGINST(4A);
	REGINST(4B);
	REGINST(4C);
	REGINST(4D);
	REGINST(4E);
	REGINST(4F);
	REGINST(50);
	REGINST(51);
	REGINST(52);
	REGINST(53);
	REGINST(54);
	REGINST(55);
	REGINST(56);
	REGINST(57);
	REGINST(58);
	REGINST(59);
	REGINST(5A);
	REGINST(5B);
	REGINST(5C);
	REGINST(5D);
	REGINST(5E);
	REGINST(5F);
	REGINST(60);
	REGINST(61);
	REGINST(62);
	REGINST(63);
	REGINST(64);
	REGINST(65);
	REGINST(66);
	REGINST(67);
	REGINST(68);
	REGINST(69);
	REGINST(6A);
	REGINST(6B);
	REGINST(6C);
	REGINST(6D);
	REGINST(6E);
	REGINST(6F);
	REGINST(70);
	REGINST(71);
	REGINST(72);
	REGINST(73);
	REGINST(74);
	REGINST(75);
	REGINST(76);
	REGINST(77);
	REGINST(78);
	REGINST(79);
	REGINST(7A);
	REGINST(7B);
	REGINST(7C);
	REGINST(7D);
	REGINST(7E);
	REGINST(7F);
	REGINST(80);
	REGINST(81);
	REGINST(82);
	REGINST(83);
	REGINST(84);
	REGINST(85);
	REGINST(86);
	REGINST(87);
	REGINST(88);
	REGINST(89);
	REGINST(8A);
	REGINST(8B);
	REGINST(8C);
	REGINST(8D);
	REGINST(8E);
	REGINST(8F);
	REGINST(90);
	REGINST(91);
	REGINST(92);
	REGINST(93);
	REGINST(94);
	REGINST(95);
	REGINST(96);
	REGINST(97);
	REGINST(98);
	REGINST(99);
	REGINST(9A);
	REGINST(9B);
	REGINST(9C);
	REGINST(9D);
	REGINST(9E);
	REGINST(9F);
	REGINST(A0);
	REGINST(A1);
	REGINST(A2);
	REGINST(A3);
	REGINST(A4);
	REGINST(A5);
	REGINST(A6);
	REGINST(A7);
	REGINST(A8);
	REGINST(A9);
	REGINST(AA);
	REGINST(AB);
	REGINST(AC);
	REGINST(AD);
	REGINST(AE);
	REGINST(AF);
	REGINST(B0);
	REGINST(B1);
	REGINST(B2);
	REGINST(B3);
	REGINST(B4);
	REGINST(B5);
	REGINST(B6);
	REGINST(B7);
	REGINST(B8);
	REGINST(B9);
	REGINST(BA);
	REGINST(BB);
	REGINST(BC);
	REGINST(BD);
	REGINST(BE);
	REGINST(BF);
	REGINST(C0);
	REGINST(C1);
	REGINST(C2);
	REGINST(C3);
	REGINST(C4);
	REGINST(C5);
	REGINST(C6);
	REGINST(C7);
	REGINST(C8);
	REGINST(C9);
	REGINST(CA);
	REGINST(CC);
	REGINST(CD);
	REGINST(CE);	
	REGINST(CF);	
	REGINST(D0);
	REGINST(D1);
	REGINST(D2);
	REGINST(D4);
	REGINST(D5);
	REGINST(D6);
	REGINST(D7);
	REGINST(D8);
	REGINST(D9);
	REGINST(DA);
	REGINST(DC);
	REGINST(DE);	
	REGINST(DF);	
	REGINST(E0);
	REGINST(E1);
	REGINST(E2);
	REGINST(E5);
	REGINST(E6);
	REGINST(E7);
	REGINST(E8);
	REGINST(E9);
	REGINST(EA);
	REGINST(EE);	
	REGINST(EF);	
	REGINST(F0);
	REGINST(F1);
	REGINST(F2);
	REGINST(F3);
	REGINST(F5);
	REGINST(F6);
	REGINST(F7);
	REGINST(F8);
	REGINST(F9);
	REGINST(FA);
	REGINST(FB);
	REGINST(FE);
	REGINST(FF);
	}
	

	
	{ //CB Instructions
	REGCB(00);
	REGCB(01);
	REGCB(02);
	REGCB(03);
	REGCB(04);
	REGCB(05);
	REGCB(06);
	REGCB(07);
	REGCB(08);
	REGCB(09);
	REGCB(0A);
	REGCB(0B);
	REGCB(0C);
	REGCB(0D);
	REGCB(0E);
	REGCB(0F);
	REGCB(10);
	REGCB(11);
	REGCB(12);
	REGCB(13);
	REGCB(14);
	REGCB(15);
	REGCB(16);
	REGCB(17);
	REGCB(18);
	REGCB(19);
	REGCB(1A);
	REGCB(1B);
	REGCB(1C);
	REGCB(1D);
	REGCB(1E);
	REGCB(1F);
	REGCB(20);
	REGCB(21);
	REGCB(22);
	REGCB(23);
	REGCB(24);
	REGCB(25);
	REGCB(26);
	REGCB(27);
	REGCB(28);
	REGCB(29);
	REGCB(2A);
	REGCB(2B);
	REGCB(2C);
	REGCB(2D);
	REGCB(2E);
	REGCB(2F);
	REGCB(30);
	REGCB(31);
	REGCB(32);
	REGCB(33);
	REGCB(34);
	REGCB(35);
	REGCB(36);
	REGCB(37);
	REGCB(38);
	REGCB(39);
	REGCB(3A);
	REGCB(3B);
	REGCB(3C);
	REGCB(3D);
	REGCB(3E);
	REGCB(3F);
	REGCB(40);		
	REGCB(41);
	REGCB(42);
	REGCB(43);
	REGCB(44);
	REGCB(45);
	REGCB(46);
	REGCB(47);
	REGCB(48);
	REGCB(49);
	REGCB(4A);
	REGCB(4B);
	REGCB(4C);
	REGCB(4D);
	REGCB(4E);
	REGCB(4F);
	REGCB(50);
	REGCB(51);
	REGCB(52);
	REGCB(53);
	REGCB(54);
	REGCB(55);
	REGCB(56);
	REGCB(57);
	REGCB(58);
	REGCB(59);
	REGCB(5A);
	REGCB(5B);
	REGCB(5C);
	REGCB(5D);
	REGCB(5E);
	REGCB(5F);	
	REGCB(60);
	REGCB(61);
	REGCB(62);
	REGCB(63);
	REGCB(64);
	REGCB(65);
	REGCB(66);
	REGCB(67);
	REGCB(68);
	REGCB(69);
	REGCB(6A);
	REGCB(6B);
	REGCB(6C);
	REGCB(6D);
	REGCB(6E);
	REGCB(6F);
	REGCB(70);
	REGCB(71);
	REGCB(72);
	REGCB(73);
	REGCB(74);
	REGCB(75);
	REGCB(76);
	REGCB(77);
	REGCB(78);
	REGCB(79);
	REGCB(7A);
	REGCB(7B);
	REGCB(7C);
	REGCB(7D);
	REGCB(7E);
	REGCB(7F);
	REGCB(80);	
	REGCB(81);
	REGCB(82);
	REGCB(83);
	REGCB(84);
	REGCB(85);
	REGCB(86);
	REGCB(87);
	REGCB(88);
	REGCB(89);
	REGCB(8A);
	REGCB(8B);
	REGCB(8C);
	REGCB(8D);
	REGCB(8E);
	REGCB(8F);
	REGCB(90);
	REGCB(91);
	REGCB(92);
	REGCB(93);
	REGCB(94);
	REGCB(95);
	REGCB(96);
	REGCB(97);
	REGCB(98);
	REGCB(99);
	REGCB(9A);
	REGCB(9B);
	REGCB(9C);
	REGCB(9D);
	REGCB(9E);
	REGCB(9F);
	REGCB(A0);
	REGCB(A1);
	REGCB(A2);
	REGCB(A3);
	REGCB(A4);
	REGCB(A5);
	REGCB(A6);
	REGCB(A7);
	REGCB(A8);
	REGCB(A9);
	REGCB(AA);
	REGCB(AB);
	REGCB(AC);
	REGCB(AD);
	REGCB(AE);
	REGCB(AF);
	REGCB(B0);
	REGCB(B1);
	REGCB(B2);
	REGCB(B3);
	REGCB(B4);
	REGCB(B5);
	REGCB(B6);
	REGCB(B7);
	REGCB(B8);
	REGCB(B9);
	REGCB(BA);
	REGCB(BB);
	REGCB(BC);
	REGCB(BD);
	REGCB(BE);
	REGCB(BF);
	REGCB(C0);
	REGCB(C1);
	REGCB(C2);
	REGCB(C3);
	REGCB(C4);
	REGCB(C5);
	REGCB(C6);
	REGCB(C7);
	REGCB(C8);
	REGCB(C9);
	REGCB(CA);
	REGCB(CB);
	REGCB(CC);
	REGCB(CD);
	REGCB(CE);
	REGCB(CF);
	REGCB(D0);
	REGCB(D1);
	REGCB(D2);
	REGCB(D3);
	REGCB(D4);
	REGCB(D5);
	REGCB(D6);
	REGCB(D7);
	REGCB(D8);
	REGCB(D9);
	REGCB(DA);
	REGCB(DB);
	REGCB(DC);
	REGCB(DD);
	REGCB(DE);
	REGCB(DF);
	REGCB(E0);
	REGCB(E1);
	REGCB(E2);
	REGCB(E3);
	REGCB(E4);
	REGCB(E5);
	REGCB(E6);
	REGCB(E7);
	REGCB(E8);
	REGCB(E9);
	REGCB(EA);
	REGCB(EB);
	REGCB(EC);
	REGCB(ED);
	REGCB(EE);
	REGCB(EF);
	REGCB(F0);
	REGCB(F1);
	REGCB(F2);
	REGCB(F3);
	REGCB(F4);
	REGCB(F5);
	REGCB(F6);
	REGCB(F7);
	REGCB(F8);
	REGCB(F9);
	REGCB(FA);
	REGCB(FB);
	REGCB(FC);
	REGCB(FD);
	REGCB(FE);
	REGCB(FF);
	
	
	}

	
	//PCRecallHead = malloc(sizeof(PCRecall*));
	PCRecallHead = malloc(8);
	*PCRecallHead = initPCRecall();


	
	initVideo();
	initJoypad();
	//initTimer();

	initInstructionCounter();
	
	
	writePC(0x100);
	
	clearFlagZ();
	clearFlagN();
	clearFlagH();
	clearFlagC();
	
	/*Redraw Screen every 70224 clicks
	Mode 0 for 207 clicks then Mode 2 for 77 clicks the Mode 3 for 172 clicks
	After 160 lines switch to Mode 1 for 4560 clicks
	*/
	
	//PCRecallTest();
	
	//printf("scrollX init: 0x%p\n",scrollX);
	//while(timerReady == 0);
	
	SDL_Thread *runGameboyThread = SDL_CreateThread(runGameboy, "gameboy", argv);
	if(runGameboyThread == NULL){
		printf("Unable to create Gameboy Thread. Exiting!!!\n");
	}

   //drawVideoFromMain();
   //SDL_Delay(5000);
   //return 0;
	
	while(1){
	
		joypadUpdate();
      drawVideoFromMain();
	
	}
	
	if(argc > 2){
		dumpMemToFile(argv[2]);
		if(argc > 3){
			dumpRegToFile(argv[3]);
		}		
	}
	
   printf("Exiting\n");
   fflush(stdout);
	
	return 0;
}



void dumpMemToFile(char* filename){
	FILE* memDump = fopen(filename, "wb");
	rewind(memDump);
	
	char* tempPtr = malloc(0x10000);
	if(tempPtr == NULL){
		printf("Couldn't allocate enough mem for dumpMemToFile\n");
		return;
	}
	
	//printf("tempPtr: 0x%p\n",tempPtr);
	
	memset(tempPtr,0,0x10000);
	memcpy(&tempPtr[0],romBanks,0x4000);	//0x0-0x3FFF ROM BANK 00
	memcpy(&tempPtr[0x4000],romBanks+0x4000*currentRomBank,0x4000);	//0x4000-0x7FFF ROM BANK 01..NN
	memcpy(&tempPtr[0x8000],vramBanks+0x2000*currentVramBank,0x2000); //0x8000-0x9FFF Banks 01..02 in CGB 
	//This next block is Extern RAM, may not actually exist
	if(ramBanks!=NULL){
		memcpy(&tempPtr[0xA000],ramBanks+0x2000*currentRamBank,0x2000);	//0xA000-0xBFFF Banks 00..03 possible
	}
	memcpy(&tempPtr[0xC000],workBanks,0x1000);	//0xC000-0xCFFF Work RAM Bank 00
	memcpy(&tempPtr[0xD000],workBanks+currentWorkBank*0x1000,0x1000); //0xD000-0xDFFF Banks 01..07
	memcpy(&tempPtr[0xE000],&tempPtr[0xC000],0x1E00); //0xE000-0xFDFF Carbon Copy of 0xE000-0xDDFF
	memcpy(&tempPtr[0xFE00],OAMTable,0xA0);	//0xFE00-0xFE9F Sprite Attribute Table (OAM)
	//Memory 0xFEA0-0xFEFF Not usable
	memcpy(&tempPtr[0xFF00],IOPorts,0x80);	//0xFF00-0xFF7F I/O Ports
	memcpy(&tempPtr[0xFF80],hram,0x7F);	//0xFF80-0xFFFF High RAM
	memcpy(&tempPtr[0xFFFF],&interruptER,0x1);	//0xFFFF Interrupt Enable Register
	
	fwrite(tempPtr,1,0x10000,memDump);
	
	free(tempPtr);
	fclose(memDump);
	
	return;	
}

int runGameboyCycle(int screenRefreshCount){
	//Everything neccesary for one cycle of gameboy
	int returnValue;
	returnValue = runCPUCycle();
	
	updateVideo(screenRefreshCount);

	if(isOAMDMAActive()==1){
		runOAMDMA();
	}
	
	runTimer();
	
	return returnValue;
}

int runGameboy(void *args){
	int screenRefreshCount = 0;

	printf("Starting Gameboy Thread\n");

	unsigned int currTime;
	unsigned int prevTime = 0;
	char** argv = args;

	writeA(0);

	while(runGameboyCycle(screenRefreshCount)!=0x10){
		screenRefreshCount++;
		if(screenRefreshCount==70224){
			screenRefreshCount=0;
			
			//Delay if needed
			currTime = SDL_GetTicks();
			if((currTime-prevTime) < (unsigned int)((1./(float)MAX_HZ)*70224.*1000000.)){
				//printf("Delaying for %d\n",(unsigned int)((1./(float)MAX_HZ)*70224.*1000000.) - (currTime-prevTime));
				SDL_Delay(((unsigned int)((1./(float)MAX_HZ)*70224.*1000000.) - (currTime-prevTime))/1000);
			}
			prevTime = currTime;

			/** DEBUG **/
			//printf("Debug Workbank: %X\n",workBanks[0x1E5C]);
			
		}
      //printf("Mem at 0xFFA6: %hhX\n", readCharFromMem(0xFFA6));
	}
	printf("Gameboy Stopped at PC: %hX\n",getPC());
	
	printPCRecall(PCRecallHead,MAX_PC_RECALL_LENGTH);
	
	dumpMemToFile(argv[2]);
	dumpRegToFile(argv[3]);

	SDL_Delay(3000);
	exit(1);
}

int runGameboyWithCondition(int screenRefreshCount,int condition){
	
	short thisPC;
	
	if(condition==RUN_COND_VBLANK){
		while(runGameboyCycle(screenRefreshCount)!=0x10){
			screenRefreshCount++;
			if(screenRefreshCount == 65664){	//V-Blank Start
				return 0;
			} else if(screenRefreshCount==70224){
				screenRefreshCount=0;
			}
		}
		return 0x10;
	} else if(condition==RUN_COND_NEXT){
		thisPC = getPC()&0xFFFF;
		while(!(((getPC()&0xFFFF)>thisPC)&&((getPC()&0xFFFF)<(thisPC+5)))){
			if(runGameboyCycle(screenRefreshCount)==0x10){
				return 0x10;
			}
			screenRefreshCount++;
			if(screenRefreshCount==70224){
				screenRefreshCount=0;
			}
		}
	} else if(condition&RUN_COND_UPTO){
		while(getPC()!=(condition&0xFFFF)){
			if(runGameboyCycle(screenRefreshCount)==0x10){
				return 0x10;
			}
			if(screenRefreshCount==70224){
				screenRefreshCount=0;
			}
		}
	} else {
		if(runGameboyCycle(screenRefreshCount)==0x10){
			return 0x10;
		}
		screenRefreshCount++;
		if(screenRefreshCount==70224){
			screenRefreshCount = 0;
		}
	}
	return 0;
}
	
//void runGameboyWithDebug(){
	
	
void dumpRegToFile(char* filename){
	FILE* regDump = fopen(filename, "wb");
	rewind(regDump);
	
	int i;
	for(i=0;i<6;i++){
		fprintf(regDump,"%.2X %.2X ",*((char*)(registerList+i*2+1))&0xFF,*((char*)(registerList+i*2))&0xFF);
	}
	
	fprintf(regDump,"\n\nAF: 0x%hX A: 0x%hhX F: 0x%hhX\nBC: 0x%hX B: 0x%hhX C: 0x%hhX\nDE: 0x%hX D: 0x%hhX E: 0x%hhX\nHL: 0x%hX H: 0x%hhX L: 0x%hhX\nSP: 0x%hX PC: 0x%hX\nZ: %i N: %i H: %i C: %i\nIME: %i",getAF(),getA()&0xFF,getF()&0xFF,getBC(),getB()&0xFF,getC()&0xFF,getDE(),getD()&0xFF,getE()&0xFF,getHL(),getH()&0xFF,getL()&0xFF,getSP(),getPC(),getFlagZ(),getFlagN(),getFlagH(),getFlagC(),IME);
	
	fclose(regDump);
	return;
}

void printPermissionTable(char* filename){
	FILE* pfile = fopen(filename,"w");
	
	int i;
	for(i=0;i<0x80;i++){
		fprintf(pfile,"Port: %hhX  Read: %hhX  Write: %hhX\n",i,checkPermissions(i)>>1,checkPermissions(i)&1);
	}
	fclose(pfile);
}	

void registerInstruction(int num,opcodeInstruction instruction){
	opcodes[num] = instruction;
}

void registerCB(int num,opcodeInstruction instruction){
	opcodes[num+0x100] = instruction;
}

void signal_INT_callback(int signum){
	printf("Caught signal, saving dump.bin");
	dumpMemToFile("dump.bin");
	
	exit(signum);
}	

void PCRecallAdd(PCRecall** first,short pc){
	
	return;
	
	int i;
	PCRecall* curr;
	PCRecall* new;
	PCRecall* prev;
	
	
	
	//Locate the last element
	i=0;
	curr = *first;
	while(curr->n!=NULL){
		prev = curr;
		curr = curr->n;
		i++;
		if(i>MAX_PC_RECALL_LENGTH){
			prev->n = NULL;
			free(curr);
		}
	}
	
	/*printf("i: %d\n",i);
	
	if(i>MAX_PC_RECALL_LENGTH){
		printf("List too long\n");
		free(curr);
		return;
	}*/
	
	new = (PCRecall*)malloc(sizeof(PCRecall));
	
	new->pc = pc;
	new->instruction = readCharFromMem(pc);
	if(((new->instruction)&0xFF)==0xCB){
		new->instruction = (readCharFromMem(pc+1))|0xCB00;
	}
	
	new->n = *first;
	*first = new;
}

PCRecall* getPCRecall(PCRecall** first,int index){
	
	int i;
	PCRecall* curr;
	
	curr = *first;
	i = 0;
	while(i!=index){
		if((curr->n)==NULL){
			return NULL;
		}
		curr = curr->n;
		i++;
	}
	return curr;
}

void printPCRecall(PCRecall** first,int num){
	
	PCRecall* curr;
	PCRecall* recallTable[MAX_PC_RECALL_LENGTH];
	
	memset(recallTable,0,MAX_PC_RECALL_LENGTH*sizeof(PCRecall*));
	
	int i;
	
	i=0;
	curr = *first;
	while(curr->n!=NULL){
		recallTable[i] = curr;
		curr = curr->n;
		i++;
	}
	
	i = num-1;
	if((num == -1)||(num>MAX_PC_RECALL_LENGTH)){	
		i=MAX_PC_RECALL_LENGTH-1;
	}
	
	while(recallTable[i]==0){
		i--;
	}
	
	while(i>=0){
		printf("[%d] PC: %hX Instruction: %hX\n",i,recallTable[i]->pc,recallTable[i]->instruction);
		i--;
	}
}

void PCRecallTest(){
	
	int i;
	PCRecall** first;
	PCRecall* curr;
	
	first = (PCRecall**)malloc(sizeof(PCRecall *));
	*first = (PCRecall*)malloc(sizeof(PCRecall));
	curr = *first;
	curr->pc = 0;
	curr->instruction = 0;
	curr->n = NULL;
	for(i=0;i<(MAX_PC_RECALL_LENGTH+50);i++){
		PCRecallAdd(first,0x150+i);
	}
	
	printPCRecall(first,-1);
	
	PCRecall *test;
	test = getPCRecall(first,80);
	printf("The pc of the 80th Element is: %hX\n",test->pc);
	
	while(1);
}

PCRecall* initPCRecall(){
	
	PCRecall* first;
	
	first = (PCRecall*)malloc(sizeof(PCRecall));
	first->pc = 0;
	first->instruction = 0;
	first->n = NULL;
	
	return first;
}
	
	
