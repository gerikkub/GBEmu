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

/************
*	LCD		*
************/
unsigned char* LCDControl;		//LCD Control Register 0xFF40
unsigned char* LCDStatus;		//LCD Status Register 0xFF41
unsigned char* scrollY;			//Scroll Y 0xFF42
unsigned char* scrollX;			//Scroll X 0xFF43
unsigned char* LY;				//Current line being written 0xFF44 READONLY
unsigned char* LYC;				//LY Compare	0xFF45
unsigned char* WY;				//Window Y Position 0xFF4A
unsigned char* WX;				//Window X Position minus 7

unsigned char* BGPaletteData;	//Background Palette Data - Non CGB Mode Only 0xFF47
unsigned char* obj0Palette;		//Object Palette 0 Data - Non CGB Mode Only 0xFF48
unsigned char* obj1Palette;		//Object Palette 1 Data - Non CGB Mode Only 0xFF49

unsigned char* BGPaletteIndex;	//Background Palette Index - CGB Mode Only 0xFF68
unsigned char* BGPaletteDataCGB;//Background Palette Data - CGB Mode Only 0xFF69
unsigned char* spritePaletteIndex;//Sprite Palette Index - CGB Mode Only 0xFF6A
unsigned char* spritePaletteData;//Sprite Palette Data - CGB Mode Only 0xFF6B


/****************
*   VRAM & DMA	*
****************/

unsigned char* VRAMBank;		//Select VRAM Bank - CGB only 0xFF4F
unsigned char* DMATransfer;		//DMA Transfer and Start Address 0xFF46

unsigned char* DMASourceHigh;	//New DMA Source, High - CGB Mode Only 0xFF51
unsigned char* DMASourceLow;	//New DMA Source, Low - CGB Mode Only 0xFF52
unsigned char* DMADestHigh;		//New DMA Destination, High - CGB Mode Only 0xFF53
unsigned char* DMADestLow;		//New DMA Destination, Low - CGB Mode Only 0xFF54
unsigned char* DMAVRAMStart;	//New DMA Lenght/Mode/Start - CGB Mode Only 0xFF55

/************
*	Sound	*			//NOT SUPPORTED AT THIS TIME
************/
unsigned char* ch1Sweep;		//Channel 1 Sweep 0xFF10
unsigned char* ch1Length;		//Channel 1 Sound Length/Wave pattern duty 0xFF11
unsigned char* ch1VolumeEnv;	//Channel 1 Volume Envelope 0xFF12
unsigned char* ch1FreqLow;		//Channel 1 Frequency Low 0xFF13
unsigned char* ch1FreqHigh;		//Channel 1 Frequency High 0xFF14

unsigned char* ch2Length;		//Channel 2 SoundLength/Wave pattern duty 0xFF16
unsigned char* ch2VolumeEnv;	//Channel 2 Volume Envelope 0xFF17
unsigned char* ch2FreqLow;		//Channel 2 Frequency Low 0xFF18
unsigned char* ch2FreqHigh;		//Channel 2 Frequency High 0xFF19

unsigned char* ch3On;			//Channel 3 On/Off 0xFF1A
unsigned char* ch3Length;		//Channel 3 Sound Length 0xFF1B
unsigned char* ch3Level;		//Channel 3 Output Level 0xFF1C
unsigned char* ch3FreqLow;		//Channel 3 Frequency Low 0xFF1D
unsigned char* ch3FreqHigh;		//Channel 3 Frequency High 0xFF1E
unsigned char* ch3WaveRAM;		//Channel 3 Wave Pattern RAM

unsigned char* ch4Length;		//Channel 4 Sound Length 0xFF20
unsigned char* ch4VolumeEnv;	//Channel 4 Volume Envelope 0xFF21
unsigned char* ch4PolyCounter;	//Channel 4 Polynomial Counter 0xFF22
unsigned char* ch4Counter;		//Channel 4 Counter 0xFF23

unsigned char* channelControl;	//Channel Control/ON-OFF/Volume 0xFF24
unsigned char* soundOutput;		//Selection of Sound Output Terminal 0xFF25
unsigned char* soundON;			//Sound ON/OFF 0xFF26

/************
*	Joypad	*
************/

unsigned char* joypadRead;		//Read/Select Which Buttton Pressed 0xFF00

/****************
*	Link Cable	*
****************/

unsigned char* serialData;		//Read/Write Serial Data 0xFF01
unsigned char* serialControl;	//Serial Transfer Control 0xFF02

/************
*	Timer	*
************/

unsigned char* divRegister;		//Divider Register 0xFF04
unsigned char* timerCounter;	//Timer Counter 0xFF05
unsigned char* timerModulo;		//Timer Modulo 0xFF06
unsigned char* timerControl;	//Timer Control 0xFF07

unsigned char* interruptFlags;	//Interrupt Flags 0xFF0F

/****************
*	CBG Only	*
****************/

unsigned char* speedSwitch;		//Prepare Speed Switch 0xFF4D
unsigned char* IRPort;			//Infrared Communications Port 0xFF56
unsigned char* WRAMBank;		//WRAM Bank Switch 0xFF70

signed int lastAddrWritten;

char* permissionTable;

typedef void (*writeSpecial)(char);
typedef char (*readSpecial)();

writeSpecial* specialWriteFunctions;
readSpecial* specialReadFunctions;

void writeAttribute(int loc,char value){
	permissionTable[loc] = value;
}	

void setSpecialWriteFunction(int loc,writeSpecial funct){
	
	printf("Loc: %X\tto mem: %p\n",loc,&specialWriteFunctions[loc]);
	specialWriteFunctions[loc] = funct;
}

void setSpecialReadFunction(int loc,readSpecial funct){
	specialReadFunctions[loc] = funct;
}

void writeLCDStatus(char value){
	*LCDStatus = (*LCDStatus&0x3)|(value&0xFC);
}

char readLCDStatus(){
	//printf("Read 0x%hhX from LCD\n",*LCDStatus);
	return *LCDStatus;
}	
	
void writeSoundON(char value){
	*soundON = (*soundON&0x7F)|(value&0x80);	//Only top bit is writeable
}

void writeJoypadRead(char value){
	value ^= 0xFF;
	if(value&0x20){
		//button keys selected
		currentButtonSelect = BUTTON_SELECT_DIRECTION;
	} else if(value&0x10){
		currentButtonSelect = BUTTON_SELECT_BUTTON;
	}
	
}

char readJoypadRead(){
	//printf("Reading 0x%hhX from the Joypad\n",*joypadRead);
	//return *joypadRead;
	if(currentButtonSelect == BUTTON_SELECT_DIRECTION){
		return buttonMatrix&0xF;
	} else {
		return (buttonMatrix>>4)&0xF;
	}
}	

void writeSpeedSwitch(char value){
	*speedSwitch = (*speedSwitch&0xFE)|(value&0x1);
}

void writeDMATransfer(char value){
	*DMATransfer = value;
	//printf("Starting DMA\n");
	startOAMDMA(value);
	spriteTableChanged = 1;
}

void writeIRPort(char value){
	*IRPort = (*IRPort&0xE3)|(value&0x1C);
}

void writeDivRegister(char value){
	(*divRegister) = 0;
}

char readDivRegister(){
	return (*divRegister);
}

void writeTimerControl(char value){
	(*timerControl) = value;
	printf("Writing %hhX to timerControl\n",value);
}

char readTimerControl(){
	return (*timerControl);
}

void initIO(){
	permissionTable = (char*)malloc(0x80);	
	if(permissionTable==NULL){
		printf("Couldn't Allocate Enough Memory for permissionTable!!!!\n");
		exit(0);
	}
	specialWriteFunctions = (writeSpecial*)malloc(SIZE_OF_INSTRUCTION*0x80);
	if(specialWriteFunctions == NULL){
		printf("Couldn't Allocate Enough Memory for specialFunctions!!!!\n");
		exit(0);
	}
	
	specialReadFunctions = (readSpecial*)malloc(SIZE_OF_INSTRUCTION*0x80);
	if(specialReadFunctions == NULL){
		printf("Couldn't Allocate Enough Memory for specialFunctions!!!!\n");
		exit(0);
	}
	
	memset(permissionTable,0x55,0x20);	//Set Attributes to Read, no Write. Will be overwritten
	memset(specialReadFunctions,0,SIZE_OF_INSTRUCTION*0x80);
	memset(specialWriteFunctions,0,SIZE_OF_INSTRUCTION*0x80);
	
	writeAttribute(0x40,IO_READWRITE);	//LCD Control
	writeAttribute(0x41,IO_SPECIAL);	//LCD Status
	writeAttribute(0x42,IO_READWRITE);	//Scroll Y
	writeAttribute(0x43,IO_READWRITE);	//Scroll X
	writeAttribute(0x44,IO_READABLE);	//LCD Y-Corrdinate
	writeAttribute(0x45,IO_READWRITE);	//LY Compare
	writeAttribute(0x4A,IO_READWRITE);	//Window Y
	writeAttribute(0x4B,IO_READWRITE);	//Window X-7
	writeAttribute(0x47,IO_READWRITE);	//BG Palette Data GB
	writeAttribute(0x48,IO_READWRITE);	//Object Palette 0 Data GB
	writeAttribute(0x49,IO_READWRITE);	//Object Palette 1 Data GB
	writeAttribute(0x68,IO_READWRITE);	//Background Palette Index CGB
	writeAttribute(0x69,IO_READWRITE);	//Background Palette Data CGB
	writeAttribute(0x6A,IO_READWRITE);	//Sprite Palette Index CGB
	writeAttribute(0x6B,IO_READWRITE);	//Sprite Palette Data CGB
	writeAttribute(0x4F,IO_READWRITE);	//VRAM Bank	CGB
	writeAttribute(0x46,IO_SPECIAL);	//DMA OAM Transfer and Start Address
	writeAttribute(0x51,IO_READWRITE);	//DMA source, High CGB
	writeAttribute(0x52,IO_READWRITE);	//DMA Source, Low CGB
	writeAttribute(0x53,IO_READWRITE);	//DMA Destination, High CGB
	writeAttribute(0x54,IO_READWRITE);	//DMA Destination, Low CGB
	writeAttribute(0x55,IO_READWRITE);	//DMA Length/Mode/Start CGB
	writeAttribute(0x10,IO_READWRITE);	//Channel 1 Sweep Register
	writeAttribute(0x11,IO_READWRITE);	//Channel 1 Sound length/Wave pattern duty
	writeAttribute(0x12,IO_READWRITE);	//Channel 1 Volume Envelope
	writeAttribute(0x13,IO_WRITEABLE);	//Channel 1 Frequence Low
	writeAttribute(0x14,IO_READWRITE);	//Channel 1 Frequency High
	writeAttribute(0x16,IO_READWRITE);	//Channel 2 Sound Length/Wave Pattern Duty
	writeAttribute(0x17,IO_READWRITE);	//Channel 2 Volume Envelope
	writeAttribute(0x18,IO_WRITEABLE);	//Channel 2 Frequency Low
	writeAttribute(0x19,IO_READWRITE);	//Channel 2 Frequency High
	writeAttribute(0x1A,IO_READWRITE);	//Channel 3 Sound on/off
	writeAttribute(0x1B,IO_READWRITE);	//Channel 3 Sound Length
	writeAttribute(0x1C,IO_READWRITE);	//Channel 3 Select output level
	writeAttribute(0x1D,IO_WRITEABLE);	//Channel 3 Frequency Low
	writeAttribute(0x1E,IO_READWRITE);	//Channel 3 Frequency High
	
	int i;
	for(i=0x30;i<0x40;i++){
		writeAttribute(i,IO_READWRITE);	//Wave Pattern RAM
	}
	
	writeAttribute(0x20,IO_READWRITE);	//Channel 4 Sound Length
	writeAttribute(0x21,IO_READWRITE);	//Channel 4 Volume Envelope
	writeAttribute(0x22,IO_READWRITE);	//Channel 4 Polynomial Counter
	writeAttribute(0x23,IO_READWRITE);	//Channel 4 Counter/consecutive; Initial
	writeAttribute(0x24,IO_READWRITE);	//Channel Control/On-OFF/ Volume
	writeAttribute(0x25,IO_READWRITE);	//Sound output terminal
	writeAttribute(0x26,IO_SPECIAL);	//Sound On/Off	SPECIAL
	writeAttribute(0x00,IO_SPECIAL);	//Joypad SPECIAL
	writeAttribute(0x01,IO_READWRITE);	//Serial Transfer Data
	writeAttribute(0x02,IO_READWRITE);	//Serial Transfer Control
	writeAttribute(0x04,IO_SPECIAL);	//Divider Register
	writeAttribute(0x05,IO_READWRITE);	//Timer Counter
	writeAttribute(0x06,IO_READWRITE);	//Timer Modulo
	writeAttribute(0x07,IO_SPECIAL);	//Timer Control
	writeAttribute(0x0F,IO_READWRITE);	//Interrupt Flags
	writeAttribute(0x4D,IO_SPECIAL);	//Prepare Speed Switch CGB
	writeAttribute(0x56,IO_SPECIAL);	//IR Communications Port CGB
	writeAttribute(0x70,IO_READWRITE);	//WRAM Bank CGB
	
	setSpecialWriteFunction(0x26,writeSoundON);
	setSpecialWriteFunction(0x00,writeJoypadRead);
	setSpecialWriteFunction(0x4D,writeSpeedSwitch);
	setSpecialWriteFunction(0x56,writeIRPort);
	setSpecialWriteFunction(0x46,writeDMATransfer);
	setSpecialWriteFunction(0x41,writeLCDStatus);
	setSpecialWriteFunction(0x04,writeDivRegister);
	setSpecialWriteFunction(0x07,writeTimerControl);
	
	setSpecialReadFunction(0x00,readJoypadRead);
	setSpecialReadFunction(0x41,readLCDStatus);
	setSpecialReadFunction(0x04,readDivRegister);
	setSpecialReadFunction(0x07,readTimerControl);
	
	LCDControl = IOPorts+0x40;
	LCDStatus = IOPorts+0x41;
	scrollY = IOPorts+0x42;
	scrollX = IOPorts+0x43;
	LY = IOPorts+0x44;
	LYC = IOPorts+0x45;
	WY = IOPorts+0x4A;
	WX = IOPorts+0x4B;
	
	BGPaletteData = IOPorts+0x47;
	obj0Palette = IOPorts+0x48;
	obj1Palette = IOPorts+0x49;
	
	BGPaletteIndex = IOPorts+0x68;
	BGPaletteDataCGB = IOPorts+0x69;
	spritePaletteIndex = IOPorts+0x6A;
	spritePaletteData = IOPorts+0x6B;
	
	VRAMBank = IOPorts+0x4F;
	DMATransfer = IOPorts+0x46;
	
	DMASourceHigh = IOPorts+0x51;
	DMASourceLow = IOPorts+0x52;
	DMADestHigh = IOPorts+0x53;
	DMADestLow = IOPorts+0x54;
	DMAVRAMStart = IOPorts+0x55;
	
	ch1Sweep = IOPorts+0x10;
	ch1Length = IOPorts+0x11;
	ch1VolumeEnv = IOPorts+0x12;
	ch1FreqLow = IOPorts+0x13;
	ch1FreqHigh = IOPorts+0x14;
	
	ch2Length = IOPorts+0x16;
	ch2VolumeEnv = IOPorts+0x17;
	ch2FreqLow = IOPorts+0x18;
	ch2FreqHigh = IOPorts+0x19;
	
	ch3On = IOPorts+0x1A;
	ch3Length = IOPorts+0x1B;
	ch3Level = IOPorts+0x1C;
	ch3FreqLow = IOPorts+0x1D;
	ch3FreqHigh = IOPorts+0x1E;
	ch3WaveRAM = IOPorts+0x30;
	
	ch4Length = IOPorts+0x20;
	ch4VolumeEnv = IOPorts+0x21;
	ch4PolyCounter = IOPorts+0x22;
	ch4Counter = IOPorts+0x23;
	
	channelControl = IOPorts+0x24;
	soundOutput = IOPorts+0x25;
	soundON = IOPorts+0x26;
	
	joypadRead = IOPorts+0x00;
	
	serialData = IOPorts+0x01;
	serialControl = IOPorts+0x02;
	
	divRegister = IOPorts+0x04;
	timerCounter = IOPorts+0x05;
	timerModulo = IOPorts+0x06;
	timerControl = IOPorts+0x07;
	
	interruptFlags = IOPorts+0x0F;
	
	speedSwitch = IOPorts+0x4D;
	IRPort = IOPorts+0x56;
	WRAMBank = IOPorts+0x70;
	
	printf("Leaving initIO\n");
}	

void writeIO(int loc,char value){
	
	#if W_PRINTF == 1 
		printf("WriteIO Called with loc: 0x%hX and value: 0x%hhX\n",loc,value);
		printf("Read: %d Write: %d Special: %d\n",permissionTable[loc-0xFF00]&IO_READABLE,(permissionTable[loc-0xFF00]&IO_WRITEABLE)>>1,(permissionTable[loc-0xFF00]&IO_SPECIAL)>>2);
	#endif
	
	writeSpecial specialFunct;		//Will hold the special function to call if neccessary
	
	if(permissionTable[loc-0xFF00] & IO_WRITEABLE){		//If the port is writeable
		IOPorts[loc-0xFF00] = value;
		#if W_PRINTF == 1 
			printf("Writing Port 0x%hhX with value: 0x%hhX\n",loc-0xFF00,value);
		#endif
	} else if(permissionTable[loc-0xFF00] & IO_SPECIAL){ //Special case if both read and write are == 0
		specialFunct = specialWriteFunctions[loc-0xFF00];
		if(specialFunct==NULL){
			printf("Couldn't Call Special Function at Address for Writing: 0x%hX\n",loc);
			//printf("Intentionally Crashing!\n");
			//char * crashPointer = NULL;
			//*crashPointer = 0x5;
		} else {
			//printf("Calling Funct for Port 0x%hhX with value: 0x%hhX\n",loc-0xFF00,value);
			specialFunct(value);
		}
	} else {
		#if W_PRINTF == 1 
			printf("loc: 0x%hX not writeable\n");
		#endif
	}	
	lastAddrWritten = loc;
}

char readIO(int loc){

	#if W_PRINTF == 1 
		printf("ReadIO Called\tloc: 0x%hhX\n",loc);
	#endif
		
	readSpecial specialFunct;
	if(permissionTable[loc-0xFF00] & IO_READABLE){

		#if W_PRINTF == 1 
			printf("Read: 0x%hhX From: 0x%hX\n",IOPorts[loc-0xFF00],loc);
		#endif
	
		return IOPorts[loc-0xFF00];
	} else if(permissionTable[loc-0xFF00] & IO_SPECIAL){
		specialFunct = specialReadFunctions[loc-0xFF00];
		if(specialFunct == NULL){
			printf("Couldn't Call Special Function at Address for Reading: 0x%hX\n",loc);
			
		} else {
			//printf("Calling specialFunct for loc: 0x%hX\n",loc);
			return specialFunct();
		}
	}
}

int checkPermissions(int port){
	return permissionTable[port];
}	










