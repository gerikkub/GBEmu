
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "main.h"
#include "instructions.h"
#include "mem.h"
#include "video.h"
#include "io.h"
#include "dma.h"
#include "joypad.h"
#include "instruction_count.h"

#define CASE(num,funct) case num: funct break;

#define CASEDEC5D(num,reg) CASE(num,\
write ## reg (get ## reg ()-1);	\
setFlagN();	\
if((get ## reg ()&0xF)==0xF) setFlagH(); else clearFlagH(); \
if(get ## reg ()==0) setFlagZ(); else clearFlagZ();)

#define CASEINC4C(num,reg) CASE(num,\
write ## reg (get ## reg () +1); \
if((get ## reg ()&0xF)==0) setFlagH(); else clearFlagH(); \
if(get ## reg ()==0) setFlagZ(); else clearFlagZ();)

#define CASEDEC(num,reg) CASE(num,write ## reg (get ## reg () -1);)
#define CASEINC(num,reg) CASE(num,write ## reg (get ## reg () +1);)

#define CASEJMP(num,cond) CASE(num,\
if(cond) writePC(signedAdd(getPC(),readCharFromMem(getPC()+1)+2)); \
else writePC(getPC()+2););

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

void dummyFunct() {return;}

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
	
	PCRecallAdd(PCRecallHead,getPC());
	
	//printf("Reading opcode: %X\n",(readCharFromMem(getPC())&0xff));
	if(readCharFromMem(getPC()) < 0x40){

		incrementInstructionCount(readCharFromMem(getPC()));

		if((readCharFromMem(getPC())&0xF)==0x9){	//Opcodes 09 19 29 39
			//short bit13 = (getHL() & 0x0800);
			//short bit15 = (getHL() & 0x8000);
			beforeHL = getHL();
			switch((readCharFromMem(getPC())&0xF0)>>4){
				CASE(0x0,writeHL(getHL()+getBC());)
				CASE(0x1,writeHL(getHL()+getDE());)
				CASE(0x2,writeHL(getHL()+getHL());)
				CASE(0x3,writeHL(getHL()+getSP());)
			}
			clearFlagN();

		
			if(beforeHL&0xFFF>getHL()&0xFFF){
				setFlagH();
			} else {
				clearFlagH();
			}
			if(beforeHL>getHL()){
				setFlagC();
			} else {
				clearFlagC();
			}
			writePC(getPC()+1);
		} else if((readCharFromMem(getPC())&0xF)==0xB){	//Opcodes 0B 1B 2B 3B
			switch((readCharFromMem(getPC())&0xF0)>>4){
				CASEDEC(0x0,BC)
				CASEDEC(0x1,DE)
				CASEDEC(0x2,HL)
				CASEDEC(0x3,SP)
			}
			writePC(getPC()+1);
		} else if(((readCharFromMem(getPC())&0xF)==0x5)||((readCharFromMem(getPC())&0xF)==0xD)){	//Opcodes 05 0D 15 1D 25 2D 35 3D
			short bit4;
			switch(readCharFromMem(getPC())){
				CASEDEC5D(0x05,B)
				CASEDEC5D(0x0D,C)
				CASEDEC5D(0x15,D)
				CASEDEC5D(0x1D,E)
				CASEDEC5D(0x25,H)
				CASEDEC5D(0x2D,L)
				CASEDEC5D(0x3D,A)
				case 0x35:
					temp = readCharFromMem(getHL());
					writeCharToMem(getHL(),temp-1);
					setFlagN();
					if(temp==0x01) { setFlagZ();} else {clearFlagZ();}
					if((temp&0xF)==0) {setFlagH();} else {clearFlagH();}
					break;
			}
			writePC(getPC()+1);
		} else if((readCharFromMem(getPC())&0xF)==0x3){
			switch((readCharFromMem(getPC())&0xF0)>>4){
				CASEINC(0x0,BC)
				CASEINC(0x1,DE)
				CASEINC(0x2,HL)
				CASEINC(0x3,SP)
			}
			writePC(getPC()+1);
		} else if(((readCharFromMem(getPC())&0xF)==0x4)||((readCharFromMem(getPC())&0xF)==0xC)){	//Opcodes 04 0C 14 1C 24 2C 34 3C
			switch(readCharFromMem(getPC())){
				CASEINC4C(0x04,B)
				CASEINC4C(0x0C,C)
				CASEINC4C(0x14,D)
				CASEINC4C(0x1C,E)
				CASEINC4C(0x24,H)
				CASEINC4C(0x2C,L)
				CASEINC4C(0x3C,A)
				case 0x34:
					writeCharToMem(getHL(),readCharFromMem(getHL())+1);
					if((readCharFromMem(getHL())&0xF)==0) setFlagH(); else clearFlagH();
					if(readCharFromMem(getHL())==0) setFlagZ(); else clearFlagZ();
					break;
			}	
			writePC(getPC()+1);
		} else if((readCharFromMem(getPC())>=0x18)&&((readCharFromMem(getPC())&0xF)==8||(readCharFromMem(getPC())&0xF)==0)){	//Opcodes 18 20 28 30 38
			switch(readCharFromMem(getPC())){
				CASEJMP(0x18,1)
				CASEJMP(0x20,getFlagZ()==0)
				CASEJMP(0x28,getFlagZ()==1)
				CASEJMP(0x30,getFlagC()==0)
				CASEJMP(0x38,getFlagC()==1)
			}
			//PC increment done in switch define
		} else if((readCharFromMem(getPC())&0xF)==1){
			switch(readCharFromMem(getPC())){
				CASE(0x01,writeBC(readShortFromMem(getPC()+1));)
				CASE(0x11,writeDE(readShortFromMem(getPC()+1));)
				CASE(0x21,writeHL(readShortFromMem(getPC()+1));)
				CASE(0x31,writeSP(readShortFromMem(getPC()+1));)
			}
			writePC(getPC()+3);
		} else if((readCharFromMem(getPC())&0xF)==2){
			switch(readCharFromMem(getPC())){
				CASE(0x02,writeCharToMem(getBC(),getA());)
				CASE(0x12,writeCharToMem(getDE(),getA());)
				CASE(0x22,writeCharToMem(getHL(),getA());writeHL(getHL()+1);)
				CASE(0x32,writeCharToMem(getHL(),getA());writeHL(getHL()-1);)
			}
			writePC(getPC()+1);
		} else if((readCharFromMem(getPC())&0xF)==6){
			switch(readCharFromMem(getPC())){
				CASE(0x06,writeB(readCharFromMem(getPC()+1));)
				CASE(0x16,writeD(readCharFromMem(getPC()+1));)
				CASE(0x26,writeH(readCharFromMem(getPC()+1));)
				CASE(0x36,writeCharToMem(getHL(),readCharFromMem(getPC()+1));)
			}
			writePC(getPC()+2);	//One operand was a 8-bit immediate
		} else if((readCharFromMem(getPC())&0xF)==0xA){
			switch(readCharFromMem(getPC())){
				CASE(0x0A,writeA(readCharFromMem(getBC()));)
				CASE(0x1A,writeA(readCharFromMem(getDE()));)
				CASE(0x2A,writeA(readCharFromMem(getHL()));writeHL(getHL()+1);)
				CASE(0x3A,writeA(readCharFromMem(getHL()));writeHL(getHL()-1);)
			}
			writePC(getPC()+1);
		} else if((readCharFromMem(getPC())&0xF)==0xE){
			switch(readCharFromMem(getPC())){
				CASE(0x0E,writeC(readCharFromMem(getPC()+1));)
				CASE(0x1E,writeE(readCharFromMem(getPC()+1));)
				CASE(0x2E,writeL(readCharFromMem(getPC()+1));)
				CASE(0x3E,writeA(readCharFromMem(getPC()+1));)
			}
			writePC(getPC()+2);
		} else {
			switch(readCharFromMem(getPC())){
				case 0: writePC(getPC()+1); break;
					
				case 0x10:
					return 0x10;
				case 0x07:	//RLCA Left Shift w/ Carry
					if(getA()&0x80){
						setFlagC(); 
						writeA((getA()<<1)|0x1);
					} else {
						clearFlagC();
						writeA(getA()<<1);
					}
					clearFlagZ();
					clearFlagN();
					clearFlagH();
					writePC(getPC()+1);
					break;
				case 0x17:	//RLA Left Shift through Carry
					if(getA()&0x80){
						writeA((getA()<<1)|getFlagC());
						setFlagC();
					} else {
						writeA((getA()<<1)|getFlagC());
						clearFlagC();
					}
					clearFlagZ();
					clearFlagN();
					clearFlagH();
					writePC(getPC()+1);
					break;
				case 0x27:	//DAA	Correct for BCD addition and subraction
					correction = 0;	//Correction Factor
					beforeA = getA();
					//printf("getA(): %X",getA());
					if(((getA()&0xF0)>>4)>0x9||getFlagC()){
						correction=0x60;
						setFlagC();
					} else {
						clearFlagC();
					}
					if((getA()&0xF)>0x9||getFlagH()){
						correction|=0x6;
					}
					//printf("Correction: %X\n",correction);
					if(getFlagN()){	//If N is Set Subract from A
						writeA(getA()-correction);
					} else {	//Else Add to A
						writeA(getA()+correction);
					}
					if(getA()==0) setFlagZ(); else clearFlagZ();
					
					//NOTICE!!!! Currently nothing is being done to the H flag
					//			 Unsure of what to do
					
					//If bit 4 has changed set the H flag
					//if((beforeA^getA())&0x10) setFlagH(); else clearFlagH();
					
					clearFlagH();
					
					writePC(getPC()+1);
					break;
				
				case 0x37:	//SCF
					clearFlagN();
					clearFlagH();
					setFlagC();
					writePC(getPC()+1);
					break;
					
				case  0x08:	//LD (a16),SP
					writeShortToMem(readShortFromMem(getPC()+1),getSP());
					writePC(getPC()+3);
					break;
					
				case 0x0F: //RRCA Right rotate w/ carry
					if(getA()&0x1){
						setFlagC();
						writeA((getA()>>1)|0x80);
					} else {
						clearFlagC();
						writeA(getA()>>1);
					}
					writePC(getPC()+1);
					break;
				
				case 0x1F: //RRA right rotate through carry
					if(getA()&0x1){
						writeA((getA()>>1)|(getFlagC()<<7));
						setFlagC();
					} else {
						writeA((getA()>>1)|(getFlagC()<<7));
						clearFlagC();
					}
					writePC(getPC()+1);
					break;
				
				case 0x2F:	//CPL
					writeA(getA()^0xFF);
					setFlagH();
					setFlagN();
					writePC(getPC()+1);
					break;
				
				case 0x3F:	//CCF invert carry
					if(getFlagC()){
						clearFlagC();
					} else {
						setFlagC();
					}
					writePC(getPC()+1);
					clearFlagN();
					clearFlagH();
					break;
				
				
			}
		}
	} else if(readCharFromMem(getPC())<0x80){

		incrementInstructionCount(readCharFromMem(getPC()));

		switch(readCharFromMem(getPC())&0xF){	//0x40 to 0x80 is a series of load instructions
			case 0:
				switch(readCharFromMem(getPC())){
					CASE(0x40,writeB(getB());)
					CASE(0x50,writeD(getB());)
					CASE(0x60,writeH(getB());)
					CASE(0x70,writeCharToMem(getHL(),getB());)
				} break;
			case 0x1:
				switch(readCharFromMem(getPC())){
					CASE(0x41,writeB(getC());)
					CASE(0x51,writeD(getC());)
					CASE(0x61,writeH(getC());)
					CASE(0x71,writeCharToMem(getHL(),getC());)
				} break;
			case 0x2:
				switch(readCharFromMem(getPC())){
					CASE(0x42,writeB(getD());)
					CASE(0x52,writeD(getD());)
					CASE(0x62,writeH(getD());)
					CASE(0x72,writeCharToMem(getHL(),getD());)
				} break;
			case 0x3:
				switch(readCharFromMem(getPC())){
					CASE(0x43,writeB(getE());)
					CASE(0x53,writeD(getE());)
					CASE(0x63,writeH(getE());)
					CASE(0x73,writeCharToMem(getHL(),getE());)
				} break;
			case 0x4:
				switch(readCharFromMem(getPC())){
					CASE(0x44,writeB(getH());)
					CASE(0x54,writeD(getH());)
					CASE(0x64,writeH(getH());)
					CASE(0x74,writeCharToMem(getHL(),getH());)
				} break;
			case 0x5:
				switch(readCharFromMem(getPC())){
					CASE(0x45,writeB(getL());)
					CASE(0x55,writeD(getL());)
					CASE(0x65,writeH(getL());)
					CASE(0x75,writeCharToMem(getHL(),getL());)
				} break;
			case 0x6:
				switch(readCharFromMem(getPC())){
					CASE(0x46,writeB(readCharFromMem(getHL()));)
					CASE(0x56,writeD(readCharFromMem(getHL()));)
					CASE(0x66,writeH(readCharFromMem(getHL()));)
					case 0x76: break;//HALT I don't know what to do for this
				} break;
			case 0x7:
				switch(readCharFromMem(getPC())){
					CASE(0x47,writeB(getA());)
					CASE(0x57,writeD(getA());)
					CASE(0x67,writeH(getA());)
					CASE(0x77,writeCharToMem(getHL(),(getA()));)
				} break;
			case 0x8:
				switch(readCharFromMem(getPC())){
					CASE(0x48,writeC(getB());)
					CASE(0x58,writeE(getB());)
					CASE(0x68,writeL(getB());)
					CASE(0x78,writeA(getB());)
				} break;
			case 0x9:
				switch(readCharFromMem(getPC())){
					CASE(0x49,writeC(getC());)
					CASE(0x59,writeE(getC());)
					CASE(0x69,writeL(getC());)
					CASE(0x79,writeA(getC());)
				} break;
			case 0xA:
				switch(readCharFromMem(getPC())){
					CASE(0x4A,writeC(getD());)
					CASE(0x5A,writeE(getD());)
					CASE(0x6A,writeL(getD());)
					CASE(0x7A,writeA(getD());)
				} break;
			case 0xB:
				switch(readCharFromMem(getPC())){
					CASE(0x4B,writeC(getE());)
					CASE(0x5B,writeE(getE());)
					CASE(0x6B,writeL(getE());)
					CASE(0x7B,writeA(getE());)
				} break;
			case 0xC:
				switch(readCharFromMem(getPC())){
					CASE(0x4C,writeC(getH());)
					CASE(0x5C,writeE(getH());)
					CASE(0x6C,writeL(getH());)
					CASE(0x7C,writeA(getH());)
				} break;
			case 0xD:
				switch(readCharFromMem(getPC())){
					CASE(0x4D,writeC(getL());)
					CASE(0x5D,writeE(getL());)
					CASE(0x6D,writeL(getL());)
					CASE(0x7D,writeA(getL());)
				} break;
			case 0xE:
				switch(readCharFromMem(getPC())){
					CASE(0x4E,writeC(readCharFromMem(getHL()));)
					CASE(0x5E,writeE(readCharFromMem(getHL()));)
					CASE(0x6E,writeL(readCharFromMem(getHL()));)
					CASE(0x7E,writeA(readCharFromMem(getHL()));)
				} break;
			case 0xF:
				switch(readCharFromMem(getPC())){
					CASE(0x4F,writeC(getA());)
					CASE(0x5F,writeE(getA());)
					CASE(0x6F,writeL(getA());)
					CASE(0x7F,writeA(getA());)
				} break;
				
		}
		writePC(getPC()+1);
	} else {
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
		if(instruction!=0){
			//printf("Instruction Loc: %p\n",instruction);
			instruction();
		} else {
			printf("Unknown Instruction: %hhX at PC: %hhX\n",readCharFromMem(getPC()),getPC());
			return 0x10;	//Stop
			writePC(getPC()+1);
		}	
	}
	
	return 0;
}	
	

	



