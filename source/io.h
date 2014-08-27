#ifndef __IO_H__
#define __IO_H__

#define GET_SET_IO_PORT_PROTO(x) \
unsigned char get ##  x (); \
unsigned char set ## x ();

/************
*	LCD		*
************/
GET_SET_IO_PORT_PROTO(LCDControl)		//LCD Control Register 0xFF40
GET_SET_IO_PORT_PROTO(LCDStatus)		//LCD Status Register 0xFF41
GET_SET_IO_PORT_PROTO(scrollY)			//Scroll Y 0xFF42
GET_SET_IO_PORT_PROTO(scrollX)			//Scroll X 0xFF43
GET_SET_IO_PORT_PROTO(LY)				//Current line being written 0xFF44 READONLY
GET_SET_IO_PORT_PROTO(LYC)				//LY Compare	0xFF45
GET_SET_IO_PORT_PROTO(WY)				//Window Y Position 0xFF4A
GET_SET_IO_PORT_PROTO(WX)				//Window X Position minus 7

GET_SET_IO_PORT_PROTO(BGPaletteData)	//Background Palette Data - Non CGB Mode Only 0xFF47
GET_SET_IO_PORT_PROTO(obj0Palette)		//Object Palette 0 Data - Non CGB Mode Only 0xFF48
GET_SET_IO_PORT_PROTO(obj1Palette)		//Object Palette 1 Data - Non CGB Mode Only 0xFF49

GET_SET_IO_PORT_PROTO(BGPaletteIndex)	//Background Palette Index - CGB Mode Only 0xFF68
GET_SET_IO_PORT_PROTO(BGPaletteDataCGB)//Background Palette Data - CGB Mode Only 0xFF69
GET_SET_IO_PORT_PROTO(spritePaletteIndex)//Sprite Palette Index - CGB Mode Only 0xFF6A
GET_SET_IO_PORT_PROTO(spritePaletteData)//Sprite Palette Data - CGB Mode Only 0xFF6B


/****************
*   VRAM & DMA	*
****************/

GET_SET_IO_PORT_PROTO(VRAMBank)		//Select VRAM Bank - CGB only 0xFF4F
GET_SET_IO_PORT_PROTO(DMATransfer)		//DMA Transfer and Start Address 0xFF46

GET_SET_IO_PORT_PROTO(DMASourceHigh)	//New DMA Source, High - CGB Mode Only 0xFF51
GET_SET_IO_PORT_PROTO(DMASourceLow)	//New DMA Source, Low - CGB Mode Only 0xFF52
GET_SET_IO_PORT_PROTO(DMADestHigh)		//New DMA Destination, High - CGB Mode Only 0xFF53
GET_SET_IO_PORT_PROTO(DMADestLow)		//New DMA Destination, Low - CGB Mode Only 0xFF54
GET_SET_IO_PORT_PROTO(DMAVRAMStart)	//New DMA Lenght/Mode/Start - CGB Mode Only 0xFF55

/************
*	Sound	*			//NOT SUPPORTED AT THIS TIME
************/
GET_SET_IO_PORT_PROTO(ch1Sweep)		//Channel 1 Sweep 0xFF10
GET_SET_IO_PORT_PROTO(ch1Length)		//Channel 1 Sound Length/Wave pattern duty 0xFF11
GET_SET_IO_PORT_PROTO(ch1VolumeEnv)	//Channel 1 Volume Envelope 0xFF12
GET_SET_IO_PORT_PROTO(ch1FreqLow)		//Channel 1 Frequency Low 0xFF13
GET_SET_IO_PORT_PROTO(ch1FreqHigh)		//Channel 1 Frequency High 0xFF14

GET_SET_IO_PORT_PROTO(ch2Length)		//Channel 2 SoundLength/Wave pattern duty 0xFF16
GET_SET_IO_PORT_PROTO(ch2VolumeEnv)	//Channel 2 Volume Envelope 0xFF17
GET_SET_IO_PORT_PROTO(ch2FreqLow)		//Channel 2 Frequency Low 0xFF18
GET_SET_IO_PORT_PROTO(ch2FreqHigh)		//Channel 2 Frequency High 0xFF19

GET_SET_IO_PORT_PROTO(ch3On)			//Channel 3 On/Off 0xFF1A
GET_SET_IO_PORT_PROTO(ch3Length)		//Channel 3 Sound Length 0xFF1B
GET_SET_IO_PORT_PROTO(ch3Level)		//Channel 3 Output Level 0xFF1C
GET_SET_IO_PORT_PROTO(ch3FreqLow)		//Channel 3 Frequency Low 0xFF1D
GET_SET_IO_PORT_PROTO(ch3FreqHigh)		//Channel 3 Frequency High 0xFF1E
GET_SET_IO_PORT_PROTO(ch3WaveRAM)		//Channel 3 Wave Pattern RAM

GET_SET_IO_PORT_PROTO(ch4Length)		//Channel 4 Sound Length 0xFF20
GET_SET_IO_PORT_PROTO(ch4VolumeEnv)	//Channel 4 Volume Envelope 0xFF21
GET_SET_IO_PORT_PROTO(ch4PolyCounter)	//Channel 4 Polynomial Counter 0xFF22
GET_SET_IO_PORT_PROTO(ch4Counter)		//Channel 4 Counter 0xFF23

GET_SET_IO_PORT_PROTO(channelControl)	//Channel Control/ON-OFF/Volume 0xFF24
GET_SET_IO_PORT_PROTO(soundOutput)		//Selection of Sound Output Terminal 0xFF25
GET_SET_IO_PORT_PROTO(soundON)			//Sound ON/OFF 0xFF26

/************
*	Joypad	*
************/

GET_SET_IO_PORT_PROTO(joypadRead)		//Read/Select Which Buttton Pressed 0xFF00

/****************
*	Link Cable	*
****************/

GET_SET_IO_PORT_PROTO(serialData)		//Read/Write Serial Data 0xFF01
GET_SET_IO_PORT_PROTO(serialControl)	//Serial Transfer Control 0xFF02

/************
*	Timer	*
************/

GET_SET_IO_PORT_PROTO(divRegister)		//Divider Register 0xFF04
GET_SET_IO_PORT_PROTO(timerCounter)	//Timer Counter 0xFF05
GET_SET_IO_PORT_PROTO(timerModulo)		//Timer Modulo 0xFF06
GET_SET_IO_PORT_PROTO(timerControl)	//Timer Control 0xFF07

GET_SET_IO_PORT_PROTO(interruptFlags)	//Interrupt Flags 0xFF0F

/****************
*	CBG Only	*
****************/

GET_SET_IO_PORT_PROTO(speedSwitch)		//Prepare Speed Switch 0xFF4D
GET_SET_IO_PORT_PROTO(IRPort)			//Infrared Communications Port 0xFF56
GET_SET_IO_PORT_PROTO(WRAMBank)		//WRAM Bank Switch 0xFF70

extern signed int lastAddrWritten;


void initIO();
void writeIO(int loc,char value);
char readIO(int loc);
int checkPermissions(int port);

#endif