
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <SDL/SDL.h>

#include "main.h"
#include "instructions.h"
#include "mem.h"
#include "video.h"
#include "io.h"
#include "dma.h"
#include "joypad.h"
#include "instruction_count.h"

#define INT_VBLANK	1
#define INT_LCD		2
#define INT_TIMER	4
#define INT_SERIAL	8
#define INT_JOYPAD	16


#define MAX_MEM	0xFFFF

typedef void (*opcodeInstruction)();

int IME = 0;	//Interrupt Mase Enable Flag
unsigned char* registerList;
int delayCyclesLeft=0;

opcodeInstruction* opcodes;

//Probably would have better to use a struct with unions. Change later
inline void writeAF(short value){
	short* reg = (short*)(registerList);
	*reg = value;
}
inline void writeBC(short value){
	short* reg = (short*)(registerList+2);
	*reg = value;
}
inline void writeDE(short value){
	short* reg = (short*)(registerList+4);
	*reg = value;
}
inline void writeHL(short value){
	short* reg = (short*)(registerList+6);
	*reg = value;
}
inline void writeSP(short value){
	short* reg = (short*)(registerList+8);
	*reg = value;
}
inline void writePC(short value){
	short* reg = (short*)registerList;
	reg[5] = value;
}

//Big Endian :(
inline void writeA(char value){
	char* reg = (char*)(registerList+1);
	*reg = value;
}
inline void writeF(char value){
	char* reg = (char*)(registerList);
	*reg = value;
}
inline void writeB(char value){
	char* reg = (char*)(registerList+3);
	*reg = value&0xFF;
}
inline void writeC(char value){
	char* reg = (char*)(registerList+2);
	*reg = value;
}
inline void writeD(char value){
	char* reg = (char*)(registerList+5);
	*reg = value;
}
inline void writeE(char value){
	char* reg = (char*)(registerList+4);
	*reg = value;
}
inline void writeH(char value){
	char* reg = (char*)(registerList+7);
	*reg = value;
}
inline void writeL(char value){
	char* reg = (char*)(registerList+6);
	*reg = value;
}

inline unsigned short getAF(){
	return *((short *)registerList);
}
inline unsigned short getBC(){
	return *((short *)(registerList+2));
}
inline unsigned short getDE(){
	return *((short *)(registerList+4));
}
inline unsigned short getHL(){
	return *((short *)(registerList+6));
}
inline unsigned short getSP(){
	return *((short *)(registerList+8));
}
inline unsigned short getPC(){
	return *((short *)(registerList+10));
}

inline unsigned char getA(){
	return *((char*)registerList+1)&0xFF;
}
inline unsigned char getF(){
	return *((char*)(registerList))&0xFF;
}
inline unsigned char getB(){
	return *((char*)(registerList+3))&0xFF;
}
inline unsigned char getC(){
	return *((char*)(registerList+2))&0xFF;
}
inline unsigned char getD(){
	return *((char*)(registerList+5))&0xFF;
}
inline unsigned char getE(){
	return *((char*)(registerList+4))&0xFF;
}
inline unsigned char getH(){
	return *((char*)(registerList+7))&0xFF;
}
inline unsigned char getL(){
	return *((char*)(registerList+6))&0xFF;
}

inline void setFlagZ(){
	writeF(getF()|0x80);
}
inline void setFlagN(){
	writeF(getF()|0x40);
}
inline void setFlagH(){
	writeF(getF()|0x20);
}
inline void setFlagC(){
	writeF(getF()|0x10);
}

inline void clearFlagZ(){
	writeF(getF()&(~(0x80)));
}
inline void clearFlagN(){
	writeF(getF()&(~(0x40)));
}
inline void clearFlagH(){
	writeF(getF()&(~(0x20)));
}
inline void clearFlagC(){
	writeF(getF()&(~(0x10)));
}

inline int getFlagZ(){
	return (getF()&0x80)>>7;
}
inline int getFlagN(){
	return (getF()&0x40)>>6;
}
inline int getFlagH(){
	return (getF()&0x20)>>5;
}
inline int getFlagC(){
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
	char correction;
	char beforeA;
	unsigned short beforeHL;
	char temp;
	opcodeInstruction instruction;	
	unsigned char currentInterrupts;
	
	if(delayCyclesLeft!=0){
		delayCyclesLeft--;
		return 0;
	}
	
	//Check for Interrupts
	if(IME == 1){
		currentInterrupts = (*interruptFlags)&interruptER;
		if(currentInterrupts&INT_VBLANK){
			writeSP(getSP()-2);
			writeShortToMem(getSP(),getPC());
			writePC(0x40);
			IME = 0;
			*interruptFlags = (*interruptFlags)& ~(INT_VBLANK);
		} else if(currentInterrupts&INT_LCD){
			writeSP(getSP()-2);
			writeShortToMem(getSP(),getPC());
			writePC(0x48);
			IME = 0;
			*interruptFlags = (*interruptFlags)& ~(INT_LCD);
		} else if(currentInterrupts&INT_TIMER){
			writeSP(getSP()-2);
			writeShortToMem(getSP(),getPC());
			writePC(0x50);
			IME = 0;
			*interruptFlags = (*interruptFlags)& ~(INT_TIMER);
		} else if(currentInterrupts&INT_SERIAL){
			writeSP(getSP()-2);
			writeShortToMem(getSP(),getPC());
			writePC(0x58);
			IME = 0;
			*interruptFlags = (*interruptFlags)& ~(INT_SERIAL);
		} else if(currentInterrupts&INT_JOYPAD){
			writeSP(getSP()-2);
			writeShortToMem(getSP(),getPC());
			writePC(0x60);
			IME = 0;
			*interruptFlags = (*interruptFlags)& ~(INT_JOYPAD);
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
	

	



