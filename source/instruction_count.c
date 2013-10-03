#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long int* instructionCount;

void initInstructionCounter(){
	instructionCount = malloc(512*sizeof(long int));
	memset(instructionCount,0,512*sizeof(long int));
}

void incrementInstructionCount(int instruction){
	instructionCount[instruction]++;
}

void outputInstructionCount(){

	int i;
	FILE* pFile = fopen("instructionCount.txt","w");

	if(pFile == NULL){
		printf("Unable to open file instructionCount for Writing");
		fclose(pFile);
	}

	for(i=0;i<512;i++){
		fprintf(pFile,"%#.4x: %lu\n",i,instructionCount[i]);
	}

	fclose(pFile);

}