#ifndef __CORE_H__
#define __CORE_H__

#define INT_VBLANK	1
#define INT_LCD		2
#define INT_TIMER	   4
#define INT_SERIAL	8
#define INT_JOYPAD	16

typedef void (*opcodeInstruction)();

extern unsigned char* registerList;
extern opcodeInstruction* opcodes;
int delayCyclesLeft;

void setInterrupt(char a);
void clearInterrupt(char a);

void writeAF(short value);
void writeBC(short value);
void writeDE(short value);
void writeHL(short value);
void writeSP(short value);
void writePC(short value);

void writeA(char value);
void writeF(char value);
void writeB(char value);
void writeC(char value);
void writeD(char value);
void writeE(char value);
void writeH(char value);
void writeL(char value);

unsigned short getAF();
unsigned short getBC();
unsigned short getDE();
unsigned short getHL();
unsigned short getSP();
unsigned short getPC();

unsigned char getA();
unsigned char getF();
unsigned char getB();
unsigned char getC();
unsigned char getD();
unsigned char getE();
unsigned char getH();
unsigned char getL();

void setFlagZ();
void setFlagN();
void setFlagH();
void setFlagC();

void clearFlagZ();
void clearFlagN();
void clearFlagH();
void clearFlagC();

int getFlagZ();
int getFlagN();
int getFlagH();
int getFlagC();

short signedAdd(short num1,char num2);

int runCPUCycle();

#endif
