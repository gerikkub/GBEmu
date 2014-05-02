#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <SDL/SDL.h>

#include "main.h"
#include "core.h"
#include "instructions.h"
#include "mem.h"
#include "video.h"
#include "io.h"
#include "dma.h"
#include "joypad.h"
#include "instruction_count.h"

#define MAX_MEM	0xFFFF

typedef void (*opcodeInstruction)();

int IME = 0;	//Interrupt Mase Enable Flag
unsigned char* registerList;
int delayCyclesLeft=0;

opcodeInstruction* opcodes;

void setInterrupt(char a){
	setinterruptFlags(getinterruptFlags() | a);
}

void clearInterrupt(char a){
	setinterruptFlags(getinterruptFlags() & ~a);
}

//Probably would have better to use a struct with unions. Change later
void writeAF(short value){
	short* reg = (short*)(registerList);
	*reg = value;
}
void writeBC(short value){
	short* reg = (short*)(registerList+2);
	*reg = value;
}
void writeDE(short value){
	short* reg = (short*)(registerList+4);
	*reg = value;
}
void writeHL(short value){
	short* reg = (short*)(registerList+6);
	*reg = value;
}
void writeSP(short value){
	short* reg = (short*)(registerList+8);
	*reg = value;
}
void writePC(short value){
	short* reg = (short*)registerList;
	reg[5] = value;
}

//Big Endian :(
void writeA(char value){
	char* reg = (char*)(registerList+1);
	*reg = value;
}
void writeF(char value){
	char* reg = (char*)(registerList);
	*reg = value;
}
void writeB(char value){
	char* reg = (char*)(registerList+3);
	*reg = value&0xFF;
}
void writeC(char value){
	char* reg = (char*)(registerList+2);
	*reg = value;
}
void writeD(char value){
	char* reg = (char*)(registerList+5);
	*reg = value;
}
void writeE(char value){
	char* reg = (char*)(registerList+4);
	*reg = value;
}
void writeH(char value){
	char* reg = (char*)(registerList+7);
	*reg = value;
}
void writeL(char value){
	char* reg = (char*)(registerList+6);
	*reg = value;
}

unsigned short getAF(){
	return *((short *)registerList);
}
unsigned short getBC(){
	return *((short *)(registerList+2));
}
unsigned short getDE(){
	return *((short *)(registerList+4));
}
unsigned short getHL(){
	return *((short *)(registerList+6));
}
unsigned short getSP(){
	return *((short *)(registerList+8));
}
unsigned short getPC(){
	return *((short *)(registerList+10));
}

unsigned char getA(){
	return *((char*)registerList+1)&0xFF;
}
unsigned char getF(){
	return *((char*)(registerList))&0xFF;
}
unsigned char getB(){
	return *((char*)(registerList+3))&0xFF;
}
unsigned char getC(){
	return *((char*)(registerList+2))&0xFF;
}
unsigned char getD(){
	return *((char*)(registerList+5))&0xFF;
}
unsigned char getE(){
	return *((char*)(registerList+4))&0xFF;
}
unsigned char getH(){
	return *((char*)(registerList+7))&0xFF;
}
unsigned char getL(){
	return *((char*)(registerList+6))&0xFF;
}

void setFlagZ(){
	writeF(getF()|0x80);
}
void setFlagN(){
	writeF(getF()|0x40);
}
void setFlagH(){
	writeF(getF()|0x20);
}
void setFlagC(){
	writeF(getF()|0x10);
}

void clearFlagZ(){
	writeF(getF()&(~(0x80)));
}
void clearFlagN(){
	writeF(getF()&(~(0x40)));
}
void clearFlagH(){
	writeF(getF()&(~(0x20)));
}
void clearFlagC(){
	writeF(getF()&(~(0x10)));
}

int getFlagZ(){
	return (getF()&0x80)>>7;
}
int getFlagN(){
	return (getF()&0x40)>>6;
}
int getFlagH(){
	return (getF()&0x20)>>5;
}
int getFlagC(){
	return (getF()&0x10)>>4;
}

short signedAdd(short num1,char num2){
	if(num2&0x80){
		return num1+(num2|0xff00);
	} else {
		return num1+num2;
	}
}

//Holds Timings for every instruction
int instructionClockCycles[] = {4,12,8,8,4,4,8,4,20,8,8,8,4,4,8,4,
								4,12,8,8,4,4,8,4,12,8,8,8,4,4,8,4,
								-1,12,8,8,4,4,8,4,-1,8,8,8,4,4,8,4,
								-1,12,8,8,12,12,12,4,-1,8,8,8,4,4,8,4,
								4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,
								4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,
								4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,
								8,8,8,8,8,8,4,8,4,4,4,4,4,4,8,4,
								4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,
								4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,
								4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,
								4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,
								-1,12,-1,16,-1,16,8,16,-1,16,-1,0,-1,24,8,16,
								-1,12,-1,0,-1,16,8,16,-1,16,-1,0,-1,0,8,16,
								12,12,8,0,0,16,8,16,16,4,16,0,0,0,8,16,
								12,12,8,4,0,16,8,16,12,8,16,4,0,0,8,16};
								
int CBInstructionClockCycles[]={8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
								8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
								8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
								8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
								8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
								8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
								8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
								8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
								8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
								8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
								8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
								8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
								8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
								8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
								8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
								8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8};
								
								

int runCPUCycle(){

	
	//Both used in DAA
	opcodeInstruction instruction;	
	unsigned char currentInterrupts;
	
	if(delayCyclesLeft!=0){
		delayCyclesLeft--;
		return 0;
	}
	
	//Check for Interrupts
	if(IME == 1){
		currentInterrupts = getinterruptFlags()&interruptER;
		if(currentInterrupts&INT_VBLANK){
			writeSP(getSP()-2);
			writeShortToMem(getSP(),getPC());
			writePC(0x40);
			IME = 0;
			clearInterrupt(INT_VBLANK);
		} else if(currentInterrupts&INT_LCD){
			writeSP(getSP()-2);
			writeShortToMem(getSP(),getPC());
			writePC(0x48);
			IME = 0;
			clearInterrupt(INT_LCD);
		} else if(currentInterrupts&INT_TIMER){
			writeSP(getSP()-2);
			writeShortToMem(getSP(),getPC());
			writePC(0x50);
			IME = 0;
			clearInterrupt(INT_TIMER);
		} else if(currentInterrupts&INT_SERIAL){
			writeSP(getSP()-2);
			writeShortToMem(getSP(),getPC());
			writePC(0x58);
			IME = 0;
			clearInterrupt(INT_SERIAL);
		} else if(currentInterrupts&INT_JOYPAD){
			writeSP(getSP()-2);
			writeShortToMem(getSP(),getPC());
			writePC(0x60);
			IME = 0;
			clearInterrupt(INT_JOYPAD);
		}
	}	
	
	
	delayCyclesLeft = instructionClockCycles[readCharFromMem(getPC())];	//Will be overwritten is instruction is CB
	if(delayCyclesLeft == -1){
		delayCyclesLeft = 20;	//My not need any actual implementation
	}
	
	//Add the instruction to the list of called instructions
	PCRecallAdd(PCRecallHead,getPC());

	//Get the instruction from the jump table
	if((readCharFromMem(getPC())&0xFF)==0xCB){
		instruction = opcodes[readCharFromMem(getPC()+1)+0x100];
		writePC(getPC()+1);

		incrementInstructionCount(readCharFromMem(getPC())+0x100);

		delayCyclesLeft = CBInstructionClockCycles[readCharFromMem(getPC())];
		//printf("Using CB instruction at PC: %hX\n",getPC());
	} else {
		if((readCharFromMem(getPC())&0xFF)==0x10){
			return 0x10;
		}
		//printf("Instruction Index: %hhX PC: %hX\n",readCharFromMem(getPC()),getPC());

		incrementInstructionCount(readCharFromMem(getPC()));

		instruction = opcodes[readCharFromMem(getPC())];
	}
	//Call the instruction
	if(instruction!=0){
		instruction();
	} else {
		printf("Unknown Instruction: %hhX at PC: %hhX\n",readCharFromMem(getPC()),getPC());
		return 0x10;	//Stop
		writePC(getPC()+1);
	}	
	
	return 0;
}	
	

	



