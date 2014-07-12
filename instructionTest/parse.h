#ifndef _PARSE_H_
#define _PARSE_H_

#include "hashMap.h"

typedef struct RegList {
   unsigned char A,F,B,C,D,E,H,L;
   unsigned short SP, PC;
} RegList;


typedef struct Test {
   RegList regInit, regFinal;
   HashMap memInit, memFinal;
   unsigned char args[8];
   struct Test *nextTest;
} Test;

typedef struct Instruction {
   unsigned char inst[2];
   Test *tests;
   struct Instruction *nextInst;
} Instruction;

Instruction* parseTests(char* filename);

#endif
