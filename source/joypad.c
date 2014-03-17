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
#include "instruction_count.h"

#include <SDL/SDL.h>

#define BIT(x) (1<<x)

#define GAMEBOY_BTTN_A		SDLK_x
#define GAMEBOY_BTTN_B		SDLK_z
#define GAMEBOY_BTTN_START	SDLK_RETURN
#define GAMEBOY_BTTN_SELECT	SDLK_RSHIFT
#define GAMEBOY_BTTN_UP		SDLK_UP
#define GAMEBOY_BTTN_DOWN	SDLK_DOWN
#define GAMEBOY_BTTN_LEFT	SDLK_LEFT
#define GAMEBOY_BTTN_RIGHT	SDLK_RIGHT

SDL_Thread *joypadThread;
int buttonMatrix;	//Lower 8 bits are Buttons, Upper 8 bits are directions
int currentButtonSelect;	//Read upper or lower bits for buttons

void initJoypad(){
	
	buttonMatrix = 0xFF;
	
	/*joypadThread = SDL_CreateThread(joypadUpdate,NULL);
	if(joypadThread==NULL){
		printf("Unable to create joypadThread!!!\n");
		exit(1);
	}*/
	
}

void joypadUpdate(){
	
	SDL_Event event;
	
	//printf("Checking Input\n");
	
	if(SDL_PollEvent(&event) == 0){
		return;
	}
	
	//printf("Recieved an event\n");
	
	switch(event.type){
	case SDL_KEYDOWN:
		switch(event.key.keysym.sym){
			case GAMEBOY_BTTN_A:
				buttonMatrix &= ~BIT(0);
				break;
			case GAMEBOY_BTTN_B:
				buttonMatrix &= ~BIT(1);
				break;
			case GAMEBOY_BTTN_SELECT:
				buttonMatrix &= ~BIT(2);
				break;
			case GAMEBOY_BTTN_START:
				buttonMatrix &= ~BIT(3);
				break;
			case GAMEBOY_BTTN_RIGHT:
				buttonMatrix &= ~BIT(4);
				break;
			case GAMEBOY_BTTN_LEFT:
				buttonMatrix &= ~BIT(5);
				break;
			case GAMEBOY_BTTN_UP:
				buttonMatrix &= ~BIT(6);
				break;
			case GAMEBOY_BTTN_DOWN:
				buttonMatrix &= ~BIT(7);
				break;
			//Debugging case!!!!!!
			case SDLK_TAB:
				shouldDumpState= 1;
				break;
		}
		//Write Joypad Data
		if(currentButtonSelect == BUTTON_SELECT_BUTTON){
			*joypadRead = buttonMatrix&0xF;
		} else {
			*joypadRead = (buttonMatrix>>4)&0xF;
		}
		break;
	case SDL_KEYUP:
		switch(event.key.keysym.sym){
			case GAMEBOY_BTTN_A:
				buttonMatrix |= BIT(0);
				break;
			case GAMEBOY_BTTN_B:
				buttonMatrix |= BIT(1);
				break;
			case GAMEBOY_BTTN_SELECT:
				buttonMatrix |= BIT(2);
				break;
			case GAMEBOY_BTTN_START:
				buttonMatrix |= BIT(3);
				break;
			case GAMEBOY_BTTN_RIGHT:
				buttonMatrix |= BIT(4);
				break;
			case GAMEBOY_BTTN_LEFT:
				buttonMatrix |= BIT(5);
				break;
			case GAMEBOY_BTTN_UP:
				buttonMatrix |= BIT(6);
				break;
			case GAMEBOY_BTTN_DOWN:
				buttonMatrix |= BIT(7);
				break;
			
		}
		//Write Joypad Data
		if(currentButtonSelect == BUTTON_SELECT_BUTTON){
			*joypadRead = buttonMatrix&0xF;
		} else {
			*joypadRead = (buttonMatrix>>4)&0xF;
		}
		break;
	case SDL_QUIT:
		outputInstructionCount();
		exit(0);
		break;
	}
	
		//printf("Current Button Matrix: %hhX\n",buttonMatrix);
}	