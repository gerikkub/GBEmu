#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "core.h"
#include "mem.h"

#define CMD_BUFFER_LEN 128
#define NUM_BREAK_ADDRS 128

#define CMD_NONE 0
#define CMD_STEP 1
#define CMD_CONTINUE 2
#define CMD_STEP_OVER 3
#define CMD_STEP_OUT 4
#define CMD_BREAK 5
#define CMD_REMOVE_BREAK 6
#define CMD_BREAK_VBLANK 7


#define CMD_VIEW_REG 10
#define CMD_VIEW_MEM_CHAR 11
#define CMD_VIEW_MEM_SHORT 12
#define CMD_VIEW_MEM_RANGE 13

#define CMD_QUIT 100

typedef struct {
	char str1[12], str2[12];
	int cmd;
} cmdCmp;

int strcmp2(char *src, char *cmp1, char *cmp2){
	return !strcmp(src,cmp1) || !strcmp(src,cmp2);
}

int getCommand(char *cmdBuffer){

	cmdCmp compare[] =
		{{"step","s",CMD_STEP},
		{"continue","c",CMD_CONTINUE},
		{"stepOver","o",CMD_STEP_OVER},
		{"stepOut","w",CMD_STEP_OUT},
		{"viewReg","r",CMD_VIEW_REG},
		{"memShort","ms",CMD_VIEW_MEM_SHORT},
		{"memChar","mc",CMD_VIEW_MEM_CHAR},
		{"break","b",CMD_BREAK},
		{"unbreak","rb",CMD_REMOVE_BREAK},
		{"vblank","bv",CMD_BREAK_VBLANK},
		{"quit","q",CMD_QUIT},
		{"","",0}};

	int ndx;
	for(ndx = 0; compare[ndx].cmd; ndx++){
		if(strcmp2(cmdBuffer,compare[ndx].str1,compare[ndx].str2))
			return compare[ndx].cmd;
	}

	return 0;

}

int checkForBreak(int *breakAddrs) {
	int i;

	for(i = 0; breakAddrs[i] != -1; i++){
		if((0xFFFF & getPC()) == (0xFFFF & (unsigned short)breakAddrs[i]))
			return 1;
	}

	return 0;
}

void addBreakAddr(int *breakAddrs, int newAddr){
	int i;
	for(i = 0; breakAddrs[i] != -1 && i < NUM_BREAK_ADDRS; i++){
		if(breakAddrs[i] == newAddr){
			return;
		}
	}
	if(i != NUM_BREAK_ADDRS){
		breakAddrs[i] = newAddr;
	}
}

void removeBreakAddr(int *breakAddrs, int removeAddr){
	int i;
	for(i = 0; breakAddrs[i] != removeAddr; i++){
		if(breakAddrs[i] == -1 || i >= NUM_BREAK_ADDRS)
			return;
	}
	for(;breakAddrs[i] != -1 && i < NUM_BREAK_ADDRS;i++){
		breakAddrs[i] = breakAddrs[i+1];
	}
}

int debugGameboy(void *argv){
	
	int screenRefreshCount = 0;
	char cmdBuffer[CMD_BUFFER_LEN];
	int breakAddrs[NUM_BREAK_ADDRS];
	int ndx;
	char *cmdString;
	int tempBreak;
	int tempMem;
	int quit = 0;
	int stop = 0;
	int startPC;
	int *quitProg;

	memset(cmdBuffer,0,CMD_BUFFER_LEN);
	memset(breakAddrs,-1,NUM_BREAK_ADDRS);

	SDL_Delay(500);

	while(!quit && !stop){
		printf("0x%.4hX > ", getPC());
		fgets(cmdBuffer, CMD_BUFFER_LEN, stdin);
		cmdString = strtok(cmdBuffer, " \n");

		if(cmdString == NULL)
			continue;

		switch(getCommand(cmdString)){
		case CMD_STEP:
			startPC = getPC();
			while(!stop && getPC() == startPC){
				if(0x10 == runGameboyCycle(screenRefreshCount))
					stop = 1;
				updateScreenRefresh(&screenRefreshCount);
			}
			break;
		case CMD_CONTINUE:
			startPC = getPC();
			while(!stop && getPC() == startPC){
				if(0x10 == runGameboyCycle(screenRefreshCount))
					stop = 1;
				updateScreenRefresh(&screenRefreshCount);
			}

			while(!stop){
				if(0x10 == runGameboyCycle(screenRefreshCount))
					stop = 1;
				updateScreenRefresh(&screenRefreshCount);
				if(checkForBreak(breakAddrs)){
					break;
				}
			}
			break;
		case CMD_BREAK:
			cmdString = strtok(NULL, " \n");
			if(tempBreak){
				sscanf(cmdString, "%hX", &tempBreak);
				addBreakAddr(breakAddrs, tempBreak);
			}
			break;
		case CMD_REMOVE_BREAK:
			cmdString = strtok(NULL, " \n");
			if(tempBreak){
				sscanf(cmdString, "%hX", &tempBreak);
				removeBreakAddr(breakAddrs, tempBreak);
			}
			break;
		case CMD_BREAK_VBLANK:
			addBreakAddr(breakAddrs, 0x40);
			break;
		case CMD_VIEW_REG:
			printf("AF: 0x%hX A: 0x%hhX F: 0x%hhX\nBC: 0x%hX B: 0x%hhX C: 0x%hhX\nDE: 0x%hX D: 0x%hhX E: 0x%hhX\nHL: 0x%hX H: 0x%hhX L: 0x%hhX\nSP: 0x%hX PC: 0x%hX\nZ: %i N: %i H: %i C: %i\nIME: %i\n",getAF(),getA()&0xFF,getF()&0xFF,getBC(),getB()&0xFF,getC()&0xFF,getDE(),getD()&0xFF,getE()&0xFF,getHL(),getH()&0xFF,getL()&0xFF,getSP(),getPC(),getFlagZ(),getFlagN(),getFlagH(),getFlagC(),IME);
			break;
		case CMD_VIEW_MEM_SHORT:
			cmdString = strtok(NULL, " \n");
			if(tempMem){
				sscanf(cmdString, "%hX", &tempMem);
				printf("0x%hX\n", readShortFromMem(tempMem));
			}
			break;
		case CMD_VIEW_MEM_CHAR:
			cmdString = strtok(NULL, " \n");
			if(tempMem){
				sscanf(cmdString, "%hX", &tempMem);
				printf("0x%hhX\n", readShortFromMem(tempMem));
			}
			break;
		case CMD_QUIT:
			quit = 1;

			break;
		default:
			printf("\n");
			break;
		}
	}

	quitProg = (int*)argv;
	*quitProg = 1;
	return 0;

}