#ifndef __MEM_H__
#define __MEM_H__

extern unsigned char* romBanks;
extern unsigned char* vramBanks;
extern unsigned char* ramBanks;
extern unsigned char* workBanks;
extern unsigned char* OAMTable;
extern unsigned char* IOPorts;
extern unsigned char* hram;
extern unsigned char interruptER;	//Interrupt Enable Register

extern int currentRomBank;
extern int currentVramBank;
extern int currentRamBank;
extern int currentWorkBank;

extern int numROMBanks;
extern int numRAMBanks;
extern int numWRAMBanks; 

void initMem(int numMemBanks,int ramSize,char cartType);

int writeCharToMem(int loc,char value);
int writeShortToMem(int loc,short value);

unsigned short readShortFromMem(int loc);
unsigned char readCharFromMem(int loc);

unsigned short changeEndian(short num);

#endif
