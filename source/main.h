#ifndef __MAIN_H__
#define __MAIN_H__

#include <assert.h>

#include <stdlib.h>

static void* malloc_line(int x,int line,char* file){
	printf("Malloc called on line %d in file %s\n",line,file);
	return malloc(x);
}

static void* calloc_line(int x,int y,int line,char* file){
	printf("Calloc called on line %d in file %s\n",line,file);
	return calloc(x,y);
}

#define malloc(x) malloc_line(x,__LINE__,__FILE__)

#define calloc(x,y) calloc_line(x,y,__LINE__,__FILE__)

#define W_PRINTF	0
#define DEBUG_INSTRUCTIONS 0

#define LINUX	1
#define SIZE_OF_INSTRUCTION	8

extern unsigned char* registerList;
//extern unsigned char* gbcMainMem;
extern int IME;

extern int shouldDumpState;

extern unsigned int screenRefreshCount;	

typedef struct PCRecall_t{
	int pc;
	int instruction;
	
	struct PCRecall_t* n;
} PCRecall;


PCRecall** PCRecallHead;

void dumpMemToFile(char* filename);
void dumpRegToFile(char* filename);

int runCPUCycle();

void PCRecallAdd(PCRecall** first,short pc);
PCRecall* getPCRecall(PCRecall** first,int index);
void printPCRecall(PCRecall** first,int num);
PCRecall* initPCRecall();


#endif
