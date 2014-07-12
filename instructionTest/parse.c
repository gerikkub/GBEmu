
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "parse.h"
#include "hashMap.h"

#define LINE_BUF_SIZE 256

Instruction* parseInstruction(char* line);
Test* parseTest(char* line); 
void addToReg(RegList *regList, HashMap *memory, char *reg, char *value);

int hashFunc(int a){
   return a;
}

Instruction* parseTests(char *filename) {
   
   char lineBuf[LINE_BUF_SIZE];
   FILE *testFile;
   Instruction *currInstruction, *firstInstruction = NULL;
   Test *currTest;


   testFile = fopen(filename, "r");
   if(testFile == NULL){
      printf("Error opening file!");
      return NULL;
   }

   while (fgets(lineBuf, LINE_BUF_SIZE, testFile)) {
      
      if(strncmp(lineBuf, "INST", 4) == 0) {
         if(currInstruction == NULL) {
            currInstruction = parseInstruction(&lineBuf[5]);
            firstInstruction = currInstruction;
         } else {
            currInstruction->nextInst = parseInstruction(&lineBuf[5]);
            currInstruction = currInstruction->nextInst;
         }
         
      } else if (strncmp(lineBuf, "TEST", 4) == 0) {
         if(currInstruction->tests == NULL) {
            currTest = parseTest(lineBuf + 5);
            currInstruction->tests = currTest;
         } else {
            currTest->nextTest = parseTest(&lineBuf[5]);
            currTest = currTest->nextTest;
         }
      }
   }

   return firstInstruction;
}

Instruction* parseInstruction(char* line) {
   Instruction *retInst = calloc(1, sizeof(Instruction));

   sscanf(line, " %hhX", &retInst->inst[0]);
   sscanf(line + 2, " %hhX", &retInst->inst[1]);
   
   return retInst;
}

Test* parseTest(char* line) {
   RegList *regInit = calloc(1, sizeof(RegList));
   RegList *regFinal = calloc(1, sizeof(RegList));
   HashMap *memInit, *memFinal;
   Test *retTest = calloc(1, sizeof(Test));
   char *reg, *value;
   char *initList, *finalList, *argList;

   memInit = createHashMap(hashFunc);
   memFinal = createHashMap(hashFunc);

   initList = strtok(line, ">");
   argList = strtok(NULL, ">");
   finalList = strtok(NULL, ">");
   if(finalList == NULL) {
      finalList = argList;
      argList = NULL;
   }

   reg = strtok(initList, "=");
   value = strtok(NULL, ",");
   while (value) {
      addToReg(regInit, memInit, reg, value);
      reg = strtok(NULL, "=");
      value = strtok(NULL, ",");
   }

   reg = strtok(finalList, "=");
   value = strtok(NULL, ",");
   while (value) {
      addToReg(regFinal, memFinal, reg, value);
      reg = strtok(NULL, "=");
      value = strtok(NULL, ",");
   }

   int i;
   memset(retTest->args, 0, 8 * sizeof(char));
   if(argList) {
      for(i = 0; i < 8; i++) {
         retTest->args[i] = strtol(argList, &argList, 16);
      }
   }

   retTest->regInit = *regInit;
   retTest->regFinal = *regFinal;

   retTest->memInit = *memInit;
   retTest->memFinal = *memFinal;
}

void addToReg(RegList *regList, HashMap *memory, char *regString, char *valueString) {
   char *reg;
   int value;
   int addr;

   while(isspace(*regString)) {
      regString++;
   }

   sscanf(regString, " %s", reg);
   sscanf(valueString, " %X", &value);

   if (strcmp(regString, "A") == 0) {
      regList->A = (unsigned char)value;
   } else if (strcmp(regString, "F") == 0) {
      regList->F = (unsigned char)value;
   } else if (strcmp(regString, "B") == 0) {
      regList->B = (unsigned char)value;
   } else if (strcmp(regString, "C") == 0) {
      regList->C = (unsigned char)value;
   } else if (strcmp(regString, "D") == 0) {
      regList->D = (unsigned char)value;   
   } else if (strcmp(regString, "E") == 0) {
      regList->E = (unsigned char)value;   
   } else if (strcmp(regString, "H") == 0) {
      regList->H = (unsigned char)value;
   } else if (strcmp(regString, "L") == 0) {
      regList->L = (unsigned char)value;
   } else if (strcmp(regString, "AF") == 0) {
      regList->A = (unsigned char)((value >> 8) & 0xFF);
      regList->F = (unsigned char)(value & 0xFF);
   } else if (strcmp(regString, "BC") == 0) {
      regList->B = (unsigned char)((value >> 8) & 0xFF);
      regList->C = (unsigned char)(value & 0xFF);
   } else if (strcmp(regString, "DE") == 0) {
      regList->D = (unsigned char)((value >> 8) & 0xFF);
      regList->E = (unsigned char)(value & 0xFF);   
   } else if (strcmp(regString, "HL") == 0) {
      regList->H = (unsigned char)((value >> 8) & 0xFF);
      regList->L = (unsigned char)(value & 0xFF);
   } else if (strcmp(regString, "SP") == 0) {
      regList->SP = (unsigned short)(value & 0xFFFF);
   } else if (strcmp(regString, "PC") == 0 ) {
      regList->PC = (unsigned short)(value & 0xFFFF);
   } else {
      sscanf(regString, "%X", &addr);
      addHashMap(memory, addr, value & 0xFFFF);
   }
}
