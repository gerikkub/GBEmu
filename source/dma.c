
#include <stdio.h>

#include "main.h"
#include "core.h"
#include "mem.h"
#include "video.h"
#include "io.h"
#include "instructions.h"
#include "joypad.h"

int OAMDMAActive = 0;
int currentAddress;

int isOAMDMAActive(){
	return OAMDMAActive;
}	

void runOAMDMA(){
	/*if(readCharFromMem(currentAddress&0xFFFF)!=0){
		printf("trying to write: 0x%hhX\t\t",readCharFromMem(currentAddress&0xFFFF));
	}*/
	OAMTable[currentAddress&0xFF] = readCharFromMem(currentAddress&0xFFFF);
	/*if(readCharFromMem(currentAddress&0xFFFF)!=0){
		printf("Wrote: 0x%hhX\n",OAMTable[currentAddress&0xFF]);
	}*/
	currentAddress++;
	if((currentAddress&0xFF)==0xA0){
		OAMDMAActive = 0;
	}
}

void startOAMDMA(char value){
	currentAddress = value<<8;
	OAMDMAActive = 1;
}