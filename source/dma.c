
#include <stdio.h>

#include "main.h"
#include "core.h"
#include "mem.h"
#include "video.h"
#include "io.h"
#include "instructions.h"
#include "joypad.h"

int OAMDMAActive = 0;
int DMACurrentAddress;

int isOAMDMAActive(){
	return OAMDMAActive;
}	

void runOAMDMA(){
	/*if(readCharFromMem(currentAddress&0xFFFF)!=0){
		printf("trying to write: 0x%hhX\t\t",readCharFromMem(currentAddress&0xFFFF));
	}*/
	OAMTable[DMACurrentAddress&0xFF] = readCharFromMem(DMACurrentAddress&0xFFFF);
	/*if(readCharFromMem(currentAddress&0xFFFF)!=0){
		printf("Wrote: 0x%hhX\n",OAMTable[currentAddress&0xFF]);
	}*/
	DMACurrentAddress++;
	if((DMACurrentAddress&0xFF)==0xA0){
		OAMDMAActive = 0;
	}
}

void startOAMDMA(char value){
	DMACurrentAddress = value<<8;
	OAMDMAActive = 1;
}
