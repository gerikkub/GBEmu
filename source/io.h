#ifndef __IO_H__
#define __IO_H__

/************
*	LCD		*
************/
extern unsigned char* LCDControl;		//LCD Control Register 0xFF40
extern unsigned char* LCDStatus;		//LCD Status Register 0xFF41
extern unsigned char* scrollY;			//Scroll Y 0xFF42
extern unsigned char* scrollX;			//Scroll X 0xFF43
extern unsigned char* LY;				//Current line being written 0xFF44 READONLY
extern unsigned char* LYC;				//LY Compare	0xFF45
extern unsigned char* WY;				//Window Y Position 0xFF4A
extern unsigned char* WX;				//Window X Position minus 7

extern unsigned char* BGPaletteData;	//Background Palette Data - Non CGB Mode Only 0xFF47
extern unsigned char* obj0Palette;		//Object Palette 0 Data - Non CGB Mode Only 0xFF48
extern unsigned char* obj1Palette;		//Object Palette 1 Data - Non CGB Mode Only 0xFF49

extern unsigned char* BGPaletteIndex;	//Background Palette Index - CGB Mode Only 0xFF68
extern unsigned char* BGPaletteDataCGB;//Background Palette Data - CGB Mode Only 0xFF69
extern unsigned char* spritePaletteIndex;//Sprite Palette Index - CGB Mode Only 0xFF6A
extern unsigned char* spritePaletteData;//Sprite Palette Data - CGB Mode Only 0xFF6B


/****************
*   VRAM & DMA	*
****************/

extern unsigned char* VRAMBank;		//Select VRAM Bank - CGB only 0xFF4F
extern unsigned char* DMATransfer;		//DMA Transfer and Start Address 0xFF46

extern unsigned char* DMASourceHigh;	//New DMA Source, High - CGB Mode Only 0xFF51
extern unsigned char* DMASourceLow;	//New DMA Source, Low - CGB Mode Only 0xFF52
extern unsigned char* DMADestHigh;		//New DMA Destination, High - CGB Mode Only 0xFF53
extern unsigned char* DMADestLow;		//New DMA Destination, Low - CGB Mode Only 0xFF54
extern unsigned char* DMAVRAMStart;	//New DMA Lenght/Mode/Start - CGB Mode Only 0xFF55

/************
*	Sound	*			//NOT SUPPORTED AT THIS TIME
************/
extern unsigned char* ch1Sweep;		//Channel 1 Sweep 0xFF10
extern unsigned char* ch1Length;		//Channel 1 Sound Length/Wave pattern duty 0xFF11
extern unsigned char* ch1VolumeEnv;	//Channel 1 Volume Envelope 0xFF12
extern unsigned char* ch1FreqLow;		//Channel 1 Frequency Low 0xFF13
extern unsigned char* ch1FreqHigh;		//Channel 1 Frequency High 0xFF14

extern unsigned char* ch2Length;		//Channel 2 SoundLength/Wave pattern duty 0xFF16
extern unsigned char* ch2VolumeEnv;	//Channel 2 Volume Envelope 0xFF17
extern unsigned char* ch2FreqLow;		//Channel 2 Frequency Low 0xFF18
extern unsigned char* ch2FreqHigh;		//Channel 2 Frequency High 0xFF19

extern unsigned char* ch3On;			//Channel 3 On/Off 0xFF1A
extern unsigned char* ch3Length;		//Channel 3 Sound Length 0xFF1B
extern unsigned char* ch3Level;		//Channel 3 Output Level 0xFF1C
extern unsigned char* ch3FreqLow;		//Channel 3 Frequency Low 0xFF1D
extern unsigned char* ch3FreqHigh;		//Channel 3 Frequency High 0xFF1E
extern unsigned char* ch3WaveRAM;		//Channel 3 Wave Pattern RAM

extern unsigned char* ch4Length;		//Channel 4 Sound Length 0xFF20
extern unsigned char* ch4VolumeEnv;	//Channel 4 Volume Envelope 0xFF21
extern unsigned char* ch4PolyCounter;	//Channel 4 Polynomial Counter 0xFF22
extern unsigned char* ch4Counter;		//Channel 4 Counter 0xFF23

extern unsigned char* channelControl;	//Channel Control/ON-OFF/Volume 0xFF24
extern unsigned char* soundOutput;		//Selection of Sound Output Terminal 0xFF25
extern unsigned char* soundON;			//Sound ON/OFF 0xFF26

/************
*	Joypad	*
************/

extern unsigned char* joypadRead;		//Read/Select Which Buttton Pressed 0xFF00

/****************
*	Link Cable	*
****************/

extern unsigned char* serialData;		//Read/Write Serial Data 0xFF01
extern unsigned char* serialControl;	//Serial Transfer Control 0xFF02

/************
*	Timer	*
************/

extern unsigned char* divRegister;		//Divider Register 0xFF04
extern unsigned char* timerCounter;	//Timer Counter 0xFF05
extern unsigned char* timerModulo;		//Timer Modulo 0xFF06
extern unsigned char* timerControl;	//Timer Control 0xFF07

extern unsigned char* interruptFlags;	//Interrupt Flags 0xFF0F

/****************
*	CBG Only	*
****************/

extern unsigned char* speedSwitch;		//Prepare Speed Switch 0xFF4D
extern unsigned char* IRPort;			//Infrared Communications Port 0xFF56
extern unsigned char* WRAMBank;		//WRAM Bank Switch 0xFF70

extern signed int lastAddrWritten;


void initIO();
void writeIO(int loc,char value);
int checkPermissions(int port);

#endif