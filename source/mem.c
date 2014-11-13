#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "instructions.h"
#include "core.h"
#include "video.h"
#include "io.h"
#include "dma.h"
#include "joypad.h"

#define CART_TYPE_ROM				0
#define CART_TYPE_MBC1				1
#define CART_TYPE_MBC1_RAM			2
#define CART_TYPE_MBC1_RAM_BAT		3
#define CART_TYPE_MBC2				5
#define CART_TYPE_MBC2_BAT			6
#define CART_TYPE_ROM_RAM			8
#define CART_TYPE_ROM_RAM_BAT		9
#define CART_TYPE_MMM01				0xB
#define CART_TYPE_MMM01_RAM			0xC
#define CART_TYPE_MMM01_RAM_BAT		0xD
#define CART_TYPE_MBC3_TIME_BAT		0xF
#define CART_TYPE_MBC3_TIME_RAM_BAT	0x10
#define CART_TYPE_MBC3				0x11
#define CART_TYPE_MBC3_RAM			0x12
#define CART_TYPE_MBC3_RAM_BAT		0x13
#define CART_TYPE_MBC4				0x15
#define CART_TYPE_MBC4_RAM			0x16
#define CART_TYPE_MBC4_RAM_BAT		0x17
#define CART_TYPE_MBC5				0x19
#define CART_TYPE_MBC5_RAM			0x1A
#define CART_TYPE_MBC5_RAM_BAT		0x1B
#define CART_TYPE_MBC5_RUMB			0x1C
#define CART_TYPE_MBC5_RUMB_RAM		0x1D
#define CART_TYPE_MBC5_RUMB_RAM_BAT	0x1E
#define CART_TYPE_POCKET_CAMERA		0xFC
#define CART_TYPE_BANDAI_TAMA5		0xFD
#define CART_TYPE_HUC3				0xFE
#define CART_TYPE_HUC1_RAM_BAT		0xFE

#define RAM_SIZE_0		0
#define RAM_SIZE_2K		1
#define RAM_SIZE_8K		2
#define RAM_SIZE_32K	3


unsigned char* romBanks;
unsigned char* vramBanks;
unsigned char* ramBanks;
unsigned char* workBanks;
unsigned char* OAMTable;
unsigned char* IOPorts;
unsigned char* hram;
unsigned char interruptER;	//Interrupt Enable Register

//Memory Banks
int currentRomBank = 1;
int currentVramBank = 0;
int currentRamBank = 0;
int currentWorkBank = 1;

int numROMBanks = 0;
int numRAMBanks = 0;
int numWRAMBanks = 0;

char RAMEnabled = 0;	
char ROMRAMMode = 0;	//used by MBC1 for access to more ROM/RAM

int mbcType;

//Membanks
void memBankROM(int a,char b){	//Nothing to be done
	return;
}

void memBankMBC1(int loc,char value){
	if(loc<0x2000){
		//printf("Enabling RAM\n");
		RAMEnabled = value;
	} else if(loc<0x4000){
		//printf("Changing rom bank to %hhX at PC: %hX\n", value, getPC());
		if((value&0x1F)==0){
			value++;
		}
		currentRomBank = (currentRomBank&0xE0)|(value&0x1F);
		//printf("Current ROM Bank changed to %d\n",currentRomBank);
	} else if(loc<0x6000){
		//printf("Changing rom/ram bank\n");
		if((ROMRAMMode&1)==0){
			currentRomBank = (currentRomBank&0x1F)|((value&0x3)<<5);
		} else {
			currentRamBank = value&0x3;
		}
	} else {
		//printf("Changing rom/ram bank mode\n");
		ROMRAMMode = value&0x1;
		if(value==0){
			currentRamBank = 0;
		} else {
			currentRomBank&=0x1F;
		}
	}
}

void memBankMBC2(int loc,char value){

	if(loc<0x2000){
		if((value&0x10)==0){
			//Not sure what to do here
		}
	} else if(loc<0x4000){
		if((value&0x10)==0){
			currentRomBank = value&0x0F;
		}
	}	
}

void memBankMBC3(int loc,char value){
	
	if(loc<0x2000){
		//Supposed to switch between RAM and Timer, will program later
	} else if(loc<0x4000){
		currentRomBank = value&0x7F;
		if(value==0) currentRomBank=0;
	} else if(loc<0x6000){
		if(value<=3){
			currentRamBank = value;
		} //Also must add in code for time, will program later
	}
}


void initMem(int numMemBanks,int ramSize,char cartType){
	//Initialize mem for memory banks
	
	if(numMemBanks<0x8){	
		romBanks = malloc(0x20000<<numMemBanks);	//Probably should change this based on Mem bank
	} else if(numMemBanks==0x52){
		romBanks = malloc(0x10000*72);
	} else if(numMemBanks==0x53){
		romBanks = malloc(0x10000*80);
	} else if(numMemBanks==0x54){
		romBanks = malloc(0x10000*92);
	}
	if(romBanks==NULL){
		printf("Couldn't allocate enough mem for memBanks!!!\n");
		exit(0);
	}
	if(numMemBanks<0x8){
		memset(romBanks,0,0x20000<<numMemBanks);
	} else if(numMemBanks==0x52){
		memset(romBanks,0,0x10000*72);
	} else if(numMemBanks==0x53){
		memset(romBanks,0,0x10000*80);
	} else if(numMemBanks==0x54){
		memset(romBanks,0,0x10000*92);
	}
	
	printf("romBanks: 0x%p\n",romBanks);

	vramBanks = calloc(0x4000, 1);	//16KB
	if(vramBanks==NULL){
		printf("Couldn't allocate enought mem for vramBank!!!\n");
		exit(0);
	}
	memset(vramBanks,0,0x4000);
	
	//strcpy(vramBanks,"VRAM Start\n");
	
	//Would allocate ramBanks size based on ROM, but games LIE!!!!!!!
   ramBanks = calloc(0x20000, 1);

	if(ramSize!=RAM_SIZE_0){
		//strcpy(ramBanks,"RAM BANKS!!!!");
	}
	workBanks = malloc(0x8000);
	if(workBanks==NULL){
		printf("Couldn't allocate enought mem for workBank!!!\n");
		exit(0);
	}
	memset(workBanks,0,0x8000);
	
	//strcpy(workBanks,"WorkBanks Start\n");
	
	OAMTable = malloc(0xA0);	//OAM Table
	if(OAMTable==NULL){
		printf("Couldn't allocate enought mem for OAMTable!!!\n");
		exit(0);
	}
	memset(OAMTable,0,0xA0);
	
	IOPorts = calloc(0x80, 1);
	if(IOPorts==NULL){
		printf("Couldn't allocate enought mem for IOPorts!!!\n");
		exit(0);
	}
	
	//strcpy(IOPorts,"IOPorts Start\n");
	
	hram = malloc(0x7F);	//High RAM
	if(hram==NULL){
		printf("Couldn't allocate enought mem for hram!!!\n");
		exit(0);
	}
	memset(hram,0,0x7F);
	
	//strcpy(hram,"HRAM Start\n");
	
	//select membank function to use based off cartridge header
	if(cartType == CART_TYPE_ROM||cartType == CART_TYPE_ROM_RAM||cartType == CART_TYPE_ROM_RAM_BAT){	//ROM only
		mbcType = 0;
	} else if(cartType >= CART_TYPE_MBC1 && cartType <= CART_TYPE_MBC1_RAM_BAT){
		mbcType = 1;
	} else if(cartType == CART_TYPE_MBC2||cartType == CART_TYPE_MBC2_BAT){
		mbcType = 2;
      ramBanks = calloc(512, 1);
	} else if(cartType >= CART_TYPE_MBC3_TIME_BAT && cartType <= CART_TYPE_MBC3_RAM_BAT){
		mbcType = 3;
	} else {
		printf("MemBank: %hhX not Supported!!!!!\n",cartType);
		exit(0);
	}
}	

void writeCharToMem(int loc,char value){
	loc&=0xFFFF;
	#if W_PRINTF == 1 
		printf("writeCharToMem loc: 0x%hhX value: 0x%hX\n",loc,value);
	#endif	
	
	/*if(loc == 0xFFA6){
		printf("writing %hhX to the value at PC: %hX\n",value,getPC());
	}*/
	
	if(loc<0xA000&&loc>=0x8000){	//VRam
		vramBanks[(loc-0x8000)+0x2000*currentVramBank] = value;
	} else if(loc<0x8000){	//Other Memcontroller stuff
		//Call MEMcontroller Stuff
		
		switch(mbcType){
			case 0:
			//	printf("Writing to MBC0! loc: %hX\n",loc);
				break;
			case 1:
			//	printf("Writing to MBC1! loc: %hX\n",loc);
				memBankMBC1(loc,value);
				break;
			case 2:
			//	printf("Writing to MBC2! loc: %hX\n",loc);
				memBankMBC2(loc,value);
				break;
			case 3:
			//	printf("Writing to MBC3! loc: %hX\n",loc);
				memBankMBC3(loc,value);
				break;
		}
		//memBankWrite(loc,value);
   } else if(loc<0xC000){
      ramBanks[(loc-0xA000) + 0x2000*currentRamBank] = value;
	} else if(loc<0xD000){
		workBanks[(loc-0xC000)] = value;
	} else if(loc<0xE000){
		workBanks[(loc-0xD000)+0x1000] = value;
	} else if(loc<0xFE00){	//Same as 0xC000-0xDDFF
		writeCharToMem(loc-0x2000,value);
	} else if(loc<0xFEA0){	//OAM Table
		OAMTable[(loc-0xFE00)] = value;
	} else if(loc<0xFF00){	//Not Usable
		//NOT USABLE
	} else if(loc<0xFF80){	//I/O Ports
		//IOPorts[(loc-0xFF00)] = value;
		#if W_PRINTF == 1 
			printf("Calling writeIO\n");
		#endif	
		writeIO(loc,value);
	} else if(loc<0xFFFF){	//High RAM
		//printf("Writing: 0x%hhX to 0x%X\n",value,loc);
		hram[(loc-0xFF80)] = value;
	} else {	//Interrupt Enable Register
		interruptER = value;
	}
}


void writeShortToMem(int loc,short value){
	loc&=0xFFFF;
	writeCharToMem(loc+1,(value&0xFF00)>>8);
	writeCharToMem(loc,(value&0xFF));
}

unsigned char readCharFromMem(int loc){
	loc&=0xFFFF;
	
	/*if(loc == 0xFFA6){
		printf("reading the value\n");
	}*/
	
	//return gbcMainMem[loc];
	if(loc<0x4000){	//Rom Bank 00 always this one
		//printf("romBanks: 0x%p\n",romBanks);
		return romBanks[loc];
	} else if(loc<0x8000){	//Other ROM banks, switchable
		return romBanks[(loc-0x4000)+0x4000*currentRomBank];
	} else if(loc<0xA000){	//8KB Video Ram, 2 Banks, switchable
		return vramBanks[(loc-0x8000)+0x2000*currentVramBank];
	} else if(loc<0xC000){	//External RAM, switchable
		return ramBanks[(loc-0xA000)+currentRamBank*0x2000];
	} else if(loc<0xD000){	//Work Ram Bank 0, fixed
		return workBanks[(loc-0xC000)];
	} else if(loc<0xE000){	//Work Ram Bank 1-7, switchable
		return workBanks[(loc-0xD000)+0x1000*currentWorkBank];
	} else if(loc<0xFE00){
		return readCharFromMem(loc-0x2000);
	} else if(loc<0xFEA0){
		return OAMTable[loc-0xFE00];
	} else if(loc<0xFF00){
		return 0;
	} else if(loc<0xFF80){
		return readIO(loc);
	} else if(loc<0xFFFF){
		return hram[loc-0xFF80];
	} else {
		return interruptER;
	}
}

unsigned short readShortFromMem(int loc){
	return (readCharFromMem(loc+1) <<8)|(readCharFromMem(loc)&0xFF);
}

unsigned short changeEndian(short num){
	return ((num&0xFF)<<8)|((num&0xFF00)>>8);
}



