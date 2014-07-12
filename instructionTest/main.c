#include <stdio.h>


#include "parse.h"

void printArgs(RegList reg) {
   printf("A: %hhX F: %hhX\n", reg.A, reg.F);
   printf("B: %hhX C: %hhX\n", reg.B, reg.C);
   printf("D: %hhX E: %hhX\n", reg.D, reg.E);
   printf("H: %hhX L: %hhX\n", reg.H, reg.L);
   printf("SP: %hX\n", reg.SP);
   printf("PC: %hX\n", reg.PC);
}

int main(int argc, char** argv){
  
   Instruction* currInst; 
   Test* currTest;
   int i = 0,j = 0,k = 0;
   
   currInst = parseTests(argv[1]);
   
   while(currInst) {
      printf("Instruction %d\n", i);
      printf("Inst: %hhX %hhX\n", currInst->inst[0], currInst->inst[1]);
      
      currTest = currInst->tests;
      j = 0;
      while(currTest) {
         printf("\nTest %d\n", j);
         printf("Init Reg:\n");
         printArgs(currTest->regInit);

         printf("Init Memory:\n");
         printHashMap(&currTest->memInit);

         printf("\nArgs: ");
         for(k = 0;k < 8;k++) {
            printf("%hhX ", currTest->args[k]);
         }
         printf("\n\nFinal Reg:\n");
         printArgs(currTest->regFinal);

         printf("Final Memory:\n");
         printHashMap(&currTest->memFinal);
         
         currTest = currTest->nextTest;
         j++;
      }
   
      currInst = currInst->nextInst;
      i++;
   }
}
