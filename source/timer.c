#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "main.h"
#include "instructions.h"
#include "core.h"
#include "mem.h"
#include "video.h"
#include "io.h"
#include "dma.h"
#include "video.h"
#include "joypad.h"

#define BIT(x) (1<<(x))

#define HZ_TO_SEC(x) (1./(x))

#define TIMA_START BIT(2)

#define TIMA_SELECT_0	4096
#define TIMA_SELECT_1	262144
#define TIMA_SELECT_2	65536
#define TIMA_SELECT_3	16384

#define FRACTION_COUNT_NEEDED(x)	((1042*1024*4)/(x))


/******************************************\
* This timer is synced with the core speed *
\******************************************/

int runTimer(){
	
	int static dividerFraction = 0;
	int static timerFraction = 0;
	
	
	dividerFraction++;
	if(dividerFraction == 256){
		(*divRegister) += 1;
		dividerFraction = 0;
	}
	
	
	if((*timerControl)&TIMA_START){
		timerFraction++;
	
		switch((*timerControl)&0x3){
			case 0:
				if(timerFraction == FRACTION_COUNT_NEEDED(TIMA_SELECT_0)){
					*timerCounter += 1;
					timerFraction = 0;
				}
				break;
			case 1:
				if(timerFraction == FRACTION_COUNT_NEEDED(TIMA_SELECT_1)){
					*timerCounter += 1;
					timerFraction = 0;
				}
				break;
			case 2:
				if(timerFraction == FRACTION_COUNT_NEEDED(TIMA_SELECT_2)){
					*timerCounter += 1;
					timerFraction = 0;
				}
				break;
			case 3:
				if(timerFraction == FRACTION_COUNT_NEEDED(TIMA_SELECT_3)){
					*timerCounter += 1;
					timerFraction = 0;
				}
				break;
		}
		if((*timerCounter) == 0){
			*timerCounter = (*timerModulo);
			(*interruptFlags) |= BIT(2);
		}
	
	}
	
	return;
}