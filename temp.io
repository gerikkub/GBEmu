#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "instructions.h"
#include "core.h"
#include "mem.h"
#include "video.h"
#include "dma.h"
#include "joypad.h"
#include "timer.h"

#define IO_READABLE		0x1
#define IO_WRITEABLE	0x2
#define IO_READWRITE	0x3
#define IO_SPECIAL		0x4

#define GET_SET_IO_PORT(x) \
static GET_SET_IO_PORT(## x;\
uint8_t get ## x (){ \
	return * ## x ;
} \
void set ## x () { \
	* ## x = 
}

/************
*	LCD		*
************/

GET_SET_IO_PORT(LCDControl)		//LCD Control Register 0xFF40
GET_SET_IO_PORT(LCDStatus)		//LCD Status Register 0xFF41
GET_SET_IO_PORT(scrollY)			//Scroll Y 0xFF42
GET_SET_IO_PORT(scrollX)			//Scroll X 0xFF43
GET_SET_IO_PORT(LY)				//Current line being written 0xFF44 READONLY
GET_SET_IO_PORT(LYC)				//LY Compare	0xFF45
GET_SET_IO_PORT(WY)				//Window Y Position 0xFF4A
GET_SET_IO_PORT(WX)				//Window X Position minus 7

GET_SET_IO_PORT(BGPaletteData)	//Background Palette Data - Non CGB Mode Only 0xFF47
GET_SET_IO_PORT(obj0Palette)		//Object Palette 0 Data - Non CGB Mode Only 0xFF48
GET_SET_IO_PORT(obj1Palette)		//Object Palette 1 Data - Non CGB Mode Only 0xFF49

GET_SET_IO_PORT(BGPaletteIndex)	//Background Palette Index - CGB Mode Only 0xFF68
GET_SET_IO_PORT(BGPaletteDataCGB;//Background Palette Data - CGB Mode Only 0xFF69
GET_SET_IO_PORT(spritePaletteIndex;//Sprite Palette Index - CGB Mode Onl: 0xFF6A
GET_SET_IO_PORT(spritePaletteData;//Sprite Palette Data - CGB Mode Only 0xFF6B


/****************
*   VRAM & DMA	*
****************/

GET_SET_IO_PORT(VRAMBank)		//Select VRAM Bank - CGB only 0xFF4F
GET_SET_IO_PORT(DMATransfer)		//DMA Transfer and Start Address 0xFF46

GET_SET_IO_PORT(DMASourceHigh)	//New DMA Source, High - CGB Mode Only 0xFF51
GET_SET_IO_PORT(DMASourceLow)	//New DMA Source, Low - CGB Mode Only 0xFF52
GET_SET_IO_PORT(DMADestHigh)		//New DMA Destination, High - CGB Mode Only 0xFF53
GET_SET_IO_PORT(DMADestLow)		//New DMA Destination, Low - CGB Mode Only 0xFF54
GET_SET_IO_PORT(DMAVRAMStart)	//New DMA Lenght/Mode/Start - CGB Mode Only 0xFF55

/************
*	Sound	*			//NOT SUPPORTED AT THIS TIME
************/
GET_SET_IO_PORT(ch1Sweep)		//Channel 1 Sweep 0xFF10
GET_SET_IO_PORT(ch1Length)		//Channel 1 Sound Length/Wave pattern duty 0xFF11
GET_SET_IO_PORT(ch1VolumeEnv)	//Channel 1 Volume Envelope 0xFF12
GET_SET_IO_PORT(ch1FreqLow)		//Channel 1 Frequency Low 0xFF13
GET_SET_IO_PORT(ch1FreqHigh)		//Channel 1 Frequency High 0xFF14

GET_SET_IO_PORT(ch2Length)		//Channel 2 SoundLength/Wave pattern duty 0xFF16
GET_SET_IO_PORT(ch2VolumeEnv)	//Channel 2 Volume Envelope 0xFF17
GET_SET_IO_PORT(ch2FreqLow)		//Channel 2 Frequency Low 0xFF18
GET_SET_IO_PORT(ch2FreqHigh)		//Channel 2 Frequency High 0xFF19

GET_SET_IO_PORT(ch3On)			//Channel 3 On/Off 0xFF1A
GET_SET_IO_PORT(ch3Length)		//Channel 3 Sound Length 0xFF1B
GET_SET_IO_PORT(ch3Level)		//Channel 3 Output Level 0xFF1C
GET_SET_IO_PORT(ch3FreqLow)		//Channel 3 Frequency Low 0xFF1D
GET_SET_IO_PORT(ch3FreqHigh)		//Channel 3 Frequency High 0xFF1E
GET_SET_IO_PORT(ch3WaveRAM)		//Channel 3 Wave Pattern RAM

GET_SET_IO_PORT(ch4Length)		//Channel 4 Sound Length 0xFF20
GET_SET_IO_PORT(ch4VolumeEnv)	//Channel 4 Volume Envelope 0xFF21
GET_SET_IO_PORT(ch4PolyCounter)	//Channel 4 Polynomial Counter 0xFF22
GET_SET_IO_PORT(ch4Counter)		//Channel 4 Counter 0xFF23

GET_SET_IO_PORT(channelControl)	//Channel Control/ON-OFF/Volume 0xFF24
GET_SET_IO_PORT(soundOutput)		//Selection of Sound Output Terminal 0xFF25
GET_SET_IO_PORT(soundON)			//Sound ON/OFF 0xFF26

/************
*	Joypad	*
************/

GET_SET_IO_PORT(joypadRead)		//Read/Select Which Buttton Pressed 0xFF00

/****************
*	Link Cable	*
****************/

GET_SET_IO_PORT(serialData)		//Read/Write Serial Data 0xFF01
GET_SET_IO_PORT(serialControl)	//Serial Transfer Control 0xFF02

/************
*	Timer	*
************/

GET_SET_IO_PORT(divRegister)		//Divider Register 0xFF04
GET_SET_IO_PORT(timerCounter)	//Timer Counter 0xFF05
GET_SET_IO_PORT(timerModulo)		//Timer Modulo 0xFF06
GET_SET_IO_PORT(timerControl)	//Timer Control 0xFF07

GET_SET_IO_PORT(interruptFlags)	//Interrupt Flags 0xFF0F

/****************
*	CBG Only	*
****************/

GET_SET_IO_PORT(speedSwitch)		//Prepare Speed Switch 0xFF4D
GET_SET_IO_PORT(IRPort)			//Infrared Communications Port 0xFF56
GET_SET_IO_PORT(WRAMBank)		//WRAM Bank Switch 0xFF70
