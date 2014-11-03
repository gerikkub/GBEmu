#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_mutex.h>

#include "mem.h"
#include "core.h"

extern int IME;
extern int halted;
extern unsigned char* registerList;
extern int screenRefreshCount;
extern int OAMDMAActive;
extern int DMACurrentAddress;
extern char RAMEnabled;
extern char ROMRAMMode;

extern SDL_sem *drawVideoStartSem;
extern SDL_sem *drawVideoCompleteSem;
extern SDL_sem *fillBuffersSem;
extern SDL_sem *spriteStartSem;
extern SDL_sem *windowStartSem;
extern SDL_sem *backgroundStartSem;
extern SDL_sem *spriteEndSem;
extern SDL_sem *windowEndSem;
extern SDL_sem *backgroundEndSem;

void dumpState(char *filename) {

   unsigned int semValue;
   int count = 0;
   FILE* dumpFile = fopen(filename, "wb");

   //fwrite(&screenRefreshCount, sizeof(int), 1, dumpFile);
   count += fwrite(&OAMDMAActive, sizeof(int), 1, dumpFile);
   count += fwrite(&DMACurrentAddress, sizeof(int), 1, dumpFile);
   count += fwrite(registerList, 12, 1, dumpFile);
   count += fwrite(&IME, sizeof(int), 1, dumpFile);
   count += fwrite(&halted, sizeof(int), 1, dumpFile);
   count += fwrite(&currentRomBank, sizeof(int), 1, dumpFile);
   count += fwrite(&currentVramBank, sizeof(int), 1, dumpFile);
   count += fwrite(&currentRamBank, sizeof(int), 1, dumpFile);
   count += fwrite(&currentWorkBank, sizeof(int), 1, dumpFile);
   count += fwrite(&RAMEnabled, sizeof(char), 1, dumpFile);
   count += fwrite(&ROMRAMMode, sizeof(char), 1, dumpFile);
   

   /*semValue = SDL_SemValue(drawVideoStartSem);
   fwrite(&semValue, sizeof(int), 1, dumpFile);
   semValue = SDL_SemValue(drawVideoCompleteSem);
   fwrite(&semValue, sizeof(int), 1, dumpFile);
   semValue = SDL_SemValue(fillBuffersSem);
   fwrite(&semValue, sizeof(int), 1, dumpFile);
   semValue = SDL_SemValue(spriteStartSem);
   fwrite(&semValue, sizeof(int), 1, dumpFile);
   semValue = SDL_SemValue(windowStartSem);
   fwrite(&semValue, sizeof(int), 1, dumpFile);
   semValue = SDL_SemValue(backgroundStartSem);
   fwrite(&semValue, sizeof(int), 1, dumpFile);
   semValue = SDL_SemValue(spriteEndSem);
   fwrite(&semValue, sizeof(int), 1, dumpFile);
   semValue = SDL_SemValue(windowEndSem);
   fwrite(&semValue, sizeof(int), 1, dumpFile);
   semValue = SDL_SemValue(backgroundEndSem);
   fwrite(&semValue, sizeof(int), 1, dumpFile);*/

   fwrite(vramBanks, 0x2000, 1, dumpFile);
   fwrite(ramBanks, 0x2000, numRAMBanks, dumpFile);
   fwrite(workBanks, 0x8000, 1, dumpFile);
   fwrite(OAMTable, 0xA0, 1, dumpFile);
   fwrite(IOPorts, 0x80, 1, dumpFile);
   fwrite(hram, 0x7F, 1, dumpFile);
   printf("Writing at :%x\n", ftell(dumpFile));
   fwrite(&interruptER, 1, 1, dumpFile);


}

void readState(char *filename) {
 
   int semValue; 
   FILE* readFile = fopen(filename, "rb");

   //fread(&screenRefreshCount, sizeof(int), 1, readFile);
   fread(&OAMDMAActive, sizeof(int), 1, readFile);
   fread(&DMACurrentAddress, sizeof(int), 1, readFile);
   fread(registerList, 12, 1, readFile);
   fread(&IME, sizeof(int), 1, readFile);
   fread(&halted, sizeof(int), 1, readFile);
   fread(&currentRomBank, sizeof(int), 1, readFile);
   fread(&currentVramBank, sizeof(int), 1, readFile);
   fread(&currentRamBank, sizeof(int), 1, readFile);
   fread(&currentWorkBank, sizeof(int), 1, readFile);
   fread(&RAMEnabled, sizeof(char), 1, readFile);
   fread(&ROMRAMMode, sizeof(char), 1, readFile);

   /*fread(&semValue, sizeof(int), 1, readFile);
   free(drawVideoStartSem);
   drawVideoStartSem = SDL_CreateSemaphore(semValue);

   fread(&semValue, sizeof(int), 1, readFile);
   free(drawVideoCompleteSem);
   drawVideoCompleteSem = SDL_CreateSemaphore(semValue);

   fread(&semValue, sizeof(int), 1, readFile);
   free(fillBuffersSem);
   fillBuffersSem = SDL_CreateSemaphore(semValue);

   fread(&semValue, sizeof(int), 1, readFile);
   free(spriteStartSem);
   spriteStartSem = SDL_CreateSemaphore(semValue);

   fread(&semValue, sizeof(int), 1, readFile);
   free(windowStartSem);
   windowStartSem = SDL_CreateSemaphore(semValue);

   fread(&semValue, sizeof(int), 1, readFile);
   free(backgroundStartSem);
   backgroundStartSem = SDL_CreateSemaphore(semValue);

   fread(&semValue, sizeof(int), 1, readFile);
   free(spriteEndSem);
   spriteEndSem = SDL_CreateSemaphore(semValue);

   fread(&semValue, sizeof(int), 1, readFile);
   free(windowEndSem);
   windowEndSem = SDL_CreateSemaphore(semValue);

   fread(&semValue, sizeof(int), 1, readFile);
   free(backgroundEndSem);
   backgroundEndSem = SDL_CreateSemaphore(semValue);*/

   fread(vramBanks, 0x2000, 1, readFile);
   fread(ramBanks, 0x2000, numRAMBanks, readFile);
   fread(workBanks, 0x8000, 1, readFile);
   fread(OAMTable, 0xA0, 1, readFile);
   fread(IOPorts, 0x80, 1, readFile);
   fread(hram, 0x7F, 1, readFile);
   printf("Reading at addr: %x\n", ftell(readFile));
   fread(&interruptER, 1, 1, readFile);
   printf("InterruptER: %hhX\n", interruptER);


   screenRefreshCount = 0;
}
   
