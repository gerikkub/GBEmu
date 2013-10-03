#ifndef __CORE_H__
#define __CORE_H__

typedef void (*opcodeInstruction)();

extern unsigned char* registerList;
extern opcodeInstruction* opcodes;
int delayCyclesLeft;

short signedAdd(short num1,char num2);

int runCPUCycle();

#endif