
#include <stdio.h>

#include "main.h"
#include "core.h"
#include "mem.h"
#include "video.h"
#include "io.h"
#include "joypad.h"

#define INSTLDIMM(num,reg) \
void instruction ## num (){ \
	write ## reg (readCharFromMem(getPC()+1)); \
	writePC(getPC()+2); \
}

#define INSTINC16(num,reg) \
void instruction ## num (){ \
	write ## reg (get ## reg() + 1); \
	writePC(getPC()+1); \
}

#define INSTINC(num,reg) \
void instruction ## num (){ \
	unsigned char value = get ## reg () + 1; \
	write ## reg (value); \
	if(value == 0){ \
		setFlagZ(); \
	} else { \
		clearFlagZ(); \
	} \
	if((value & 0xF) == 0){ \
		setFlagH(); \
	} else { \
		clearFlagH(); \
	} \
	clearFlagN(); \
	writePC(getPC()+1); \
}

#define INSTDEC(num,reg) \
void instruction ## num (){ \
	unsigned char value = get ## reg () - 1; \
	write ## reg (value); \
	if(value == 0){ \
		setFlagZ(); \
	} else { \
		clearFlagZ(); \
	} \
	if((value&0xF) == 0xF){ \
		setFlagH(); \
	} else { \
		clearFlagH(); \
	} \
	setFlagN(); \
	writePC(getPC()+1); \
}

#define INSTDEC16(num,reg) \
void instruction ## num (){ \
	write ## reg (get ## reg() - 1); \
	writePC(getPC()+1); \
}

#define INSTLDIMM16(num,reg) \
void instruction ## num (){ \
	write ## reg (readShortFromMem(getPC()+1)); \
	writePC(getPC()+3); \
}

#define INSTLD(num,regdest,regsrc) \
void instruction ## num (){ \
	write ## regdest (get ## regsrc ()); \
	writePC(getPC()+1); \
}

#define INSTLDFROMMEM(num,reg) \
void instruction ## num (){ \
	write ## reg (readCharFromMem(getHL())); \
	writePC(getPC()+1); \
}

#define INSTLDTOMEM(num,reg) \
void instruction ## num (){ \
	writeCharToMem(getHL(),get ## reg ()); \
	writePC(getPC()+1); \
}

//	printf("0b: %X\n",getBC()&0xFFF + originalState&0xFFF); \

#define INSTADDREG16(num,reg) \
void instruction ## num (){ \
	unsigned short originalState = getHL(); \
	writeHL(get ## reg () + getHL()); \
	if((originalState&0xFFF)>(getHL()&0xFFF)){ \
		setFlagH(); \
	} else { \
		clearFlagH(); \
	} \
	if((originalState&0xFFFF) > (getHL()&0xFFFF)){ \
		setFlagC(); \
	} else { \
		clearFlagC(); \
	} \
	clearFlagN(); \
	writePC(getPC()+1); \
}

#define INSTADD(num,reg) \
void instruction ## num (){ \
unsigned char begin = getA(); \
	writeA(begin+get ## reg ()); \
	if((getA()&0xFF)==0){ \
		setFlagZ(); \
	} else { \
		clearFlagZ(); \
	} \
	clearFlagN(); \
	if((begin&0xF)>(getA()&0xF)){ \
		setFlagH(); \
	} else { \
		clearFlagH(); \
	} \
	if((begin&0xFF)>(getA()&0xFF)){ \
		setFlagC(); \
	} else { \
		clearFlagC(); \
	} \
	writePC(getPC()+1); \
}

#define INSTADC(num,reg) \
void instruction ## num (){ \
unsigned char begin = getA(); \
	writeA(begin+get ## reg ()); \
	if(getFlagC()) writeA(getA()+1); \
	if((getA()&0xFF)==0){ \
		setFlagZ(); \
	} else { \
		clearFlagZ(); \
	} \
	clearFlagN(); \
	if((begin&0xF)>(getA()&0xF)){ \
		setFlagH(); \
	} else { \
		clearFlagH(); \
	} \
	if((begin&0xFF)>(getA()&0xFF)){ \
		setFlagC(); \
	} else { \
		clearFlagC(); \
	} \
	writePC(getPC()+1); \
}

#define INSTSUB(num,reg) \
void instruction ## num (){ \
unsigned char begin = getA(); \
	writeA(begin-get ## reg ()); \
	if((getA()&0xFF)==0){ \
		setFlagZ(); \
	} else { \
		clearFlagZ(); \
	} \
	setFlagN(); \
	if((begin&0xF)<(getA()&0xF)){ \
		setFlagH(); \
	} else { \
		clearFlagH(); \
	} \
	if((begin&0xFF)<(getA()&0xFF)){ \
		setFlagC(); \
	} else { \
		clearFlagC(); \
	} \
	writePC(getPC()+1); \
}

#define INSTSBC(num,reg) \
void instruction ## num (){ \
unsigned char begin = getA(); \
	writeA(begin-get ## reg ()); \
	if(getFlagC()) writeA(getA()-1); \
	if((getA()&0xFF)==0){ \
		setFlagZ(); \
	} else { \
		clearFlagZ(); \
	} \
	setFlagN(); \
	if((begin&0xF)<(getA()&0xF)){ \
		setFlagH(); \
	} else { \
		clearFlagH(); \
	} \
	if((begin&0xFF)<(getA()&0xFF)){ \
		setFlagC(); \
	} else { \
		clearFlagC(); \
	} \
	writePC(getPC()+1); \
}

#define INSTAND(num,reg) \
void instruction ## num (){ \
	writeA(get ## reg ()&getA()); \
	if((getA()&0xFF)==0){ \
		setFlagZ(); \
	} else { \
		clearFlagZ(); \
	} \
	clearFlagN(); \
	setFlagH(); \
	clearFlagC(); \
	writePC(getPC()+1); \
}

#define INSTXOR(num,reg) \
void instruction ## num (){ \
	writeA(get ## reg ()^getA()); \
	if((getA()&0xFF)==0){ \
		setFlagZ(); \
	} else { \
		clearFlagZ(); \
	} \
	clearFlagN(); \
	clearFlagH(); \
	clearFlagC(); \
	writePC(getPC()+1); \
}

#define INSTOR(num,reg) \
void instruction ## num (){ \
	writeA(get ## reg ()|getA()); \
	if((getA()&0xFF)==0){ \
		setFlagZ(); \
	} else { \
		clearFlagZ(); \
	} \
	clearFlagN(); \
	clearFlagH(); \
	clearFlagC(); \
	writePC(getPC()+1); \
}

#define INSTCP(num,reg) \
void instruction ## num (){ \
unsigned char begin = getA(); \
unsigned char res; \
	res = begin-get ## reg (); \
	if((res&0xFF)==0){ \
		setFlagZ(); \
	} else { \
		clearFlagZ(); \
	} \
	setFlagN(); \
	if((begin&0xF)<(res&0xF)){ \
		setFlagH(); \
	} else { \
		clearFlagH(); \
	} \
	if((begin&0xFF)<(res&0xFF)){ \
		setFlagC(); \
	} else { \
		clearFlagC(); \
	} \
	writePC(getPC()+1); \
}

#define INSTRST(num,imm) \
void instruction ## num (){ \
	writeSP(getSP()-2); \
	writeShortToMem(getSP(),getPC()+1); \
	writePC(imm); \
}


#define INSTCBRLC(num,reg) \
void instructionCB ## num (){ \
	if(get ## reg ()&0x80){ \
		setFlagC();	\
		write ## reg ((get ## reg()<<1)|0x1); \
	} else {\
		clearFlagC(); \
		write ## reg ((get ## reg()<<1)&0xFE); \
	} \
	if((get ## reg()&0xFF)==0){ \
		setFlagZ(); \
	} else { \
		clearFlagZ(); \
	} \
	clearFlagN(); \
	clearFlagH(); \
	writePC(getPC()+1); \
}

#define INSTCBRRC(num,reg) \
void instructionCB ## num (){ \
	if(get ## reg()&0x1==1){ \
		setFlagC(); \
		write ## reg (((get ## reg()&0xFF)>>1)|0x80); \
	} else { \
		clearFlagC(); \
		write ## reg (((get ## reg()&0xFF)>>1)&0x7F); \
	} \
	if((get ## reg()&0xFF)==0){ \
		setFlagZ(); \
	} else { \
		clearFlagZ(); \
	} \
	clearFlagN(); \
	clearFlagH(); \
	writePC(getPC()+1); \
}

#define INSTCBRL(num,reg) \
void instructionCB ## num (){ \
	if(get ## reg ()&0x80){ \
		write ## reg ((get ## reg ()<<1)|(getFlagC()&1)); \
		setFlagC(); \
	} else { \
		write ## reg ((get ## reg ()<<1)|(getFlagC()&1)); \
		clearFlagC(); \
	} \
	if((get ## reg ()&0xFF)==0){ \
		setFlagZ(); \
	} else { \
		clearFlagZ(); \
	} \
	clearFlagN(); \
	clearFlagH(); \
	writePC(getPC()+1); \
}

#define INSTCBRR(num,reg) \
void instructionCB ## num (){ \
	if(get ## reg () &0x1){ \
		write ## reg ((((get ## reg ()&0xFF)>>1)&0x7F)|((getFlagC()&1)<<7)); \
		setFlagC(); \
	} else { \
		write ## reg ((((get ## reg ()&0xFF)>>1)&0x7F)|((getFlagC()&1)<<7)); \
		clearFlagC(); \
	} \
	if((get ## reg ()&0xFF)==0){ \
		setFlagZ(); \
	} else { \
		clearFlagZ(); \
	} \
	clearFlagN(); \
	clearFlagH(); \
	writePC(getPC()+1); \
}
		
#define INSTCBSLA(num,reg) \
void instructionCB ## num (){ \
	if(get ## reg ()&0x80){ \
		setFlagC(); \
	} else { \
		clearFlagC(); \
	} \
	write ## reg (get ## reg ()<<1); \
	if((get ## reg () &0xFF)==0){ \
		setFlagZ(); \
	} else { \
		clearFlagZ(); \
	} \
	clearFlagN(); \
	clearFlagH(); \
	writePC(getPC()+1); \
}	

#define INSTCBSRA(num,reg) \
void instructionCB ## num (){ \
	if(get ## reg ()&0x01){ \
		setFlagC(); \
	} else { \
		clearFlagC(); \
	} \
	write ## reg (((get ## reg ()&0xFF)>>1)|(get ## reg ()&0x80)); \
	if((get ## reg ()&0xFF) == 0){ \
		setFlagZ(); \
	} else { \
		clearFlagZ(); \
	} \
	clearFlagN(); \
	clearFlagH(); \
	writePC(getPC()+1); \
}

#define INSTCBSWAP(num,reg) \
void instructionCB ## num (){ \
	write ## reg (((get ## reg ()<<4)|((get ## reg ()>>4)&0x0F))&0xFF); \
	if((get ## reg ()&0xFF)==0){ \
		setFlagZ(); \
	} else { \
		clearFlagZ(); \
	} \
	clearFlagN(); \
	clearFlagH(); \
	clearFlagC(); \
	writePC(getPC()+1); \
}

#define INSTCBSRL(num,reg) \
void instructionCB ## num(){ \
	if(get ## reg ()&0x1){ \
		setFlagC(); \
	} else { \
		clearFlagC(); \
	} \
	write ## reg ((get ## reg ()&0xFF)>>1); \
	if((get ## reg ()&0xFF) == 0){ \
		setFlagZ(); \
	} else { \
		clearFlagZ(); \
	} \
	clearFlagN(); \
	clearFlagH(); \
	writePC(getPC()+1); \
}

#define INSTCBBIT(num,reg,bit) \
void instructionCB ## num (){ \
	if((get ## reg ()&(1<<bit))==0){ \
		setFlagZ(); \
	} else { \
		clearFlagZ(); \
	} \
	clearFlagN(); \
	setFlagH(); \
	writePC(getPC()+1); \
}

#define INSTCBBITMEM(num,bit) \
void instructionCB ## num (){ \
	if((readCharFromMem(getHL())&(1<<bit))==0){ \
		setFlagZ(); \
	} else { \
		clearFlagZ(); \
	} \
	clearFlagN(); \
	setFlagH(); \
	writePC(getPC()+1); \
}
	
#define INSTCBRES(num,reg,bit) \
void instructionCB ## num (){ \
	write ## reg (get ## reg() & ~(1<<bit)); \
	writePC(getPC()+1); \
}

#define INSTCBRESMEM(num,bit) \
void instructionCB ## num (){ \
	writeCharToMem(getHL(),readCharFromMem(getHL()) & ~(1<<bit)); \
	writePC(getPC()+1); \
}

#define INSTCBSET(num,reg,bit) \
void instructionCB ## num (){ \
	write ## reg (get ## reg()|(1<<bit)); \
	writePC(getPC()+1); \
}

#define INSTCBSETMEM(num,bit) \
void instructionCB ## num (){ \
	writeCharToMem(getHL(),readCharFromMem(getHL())|(1<<bit)); \
	writePC(getPC()+1); \
}

void instruction00(){
	writePC(getPC()+1);	//NOP
}

void instruction10(){
	return;	//STOP Should be handled in core.c
}

void instruction20(){
	unsigned char offset;
	if(getFlagZ() == 0){
		offset = readCharFromMem(getPC()+1);
		if(offset&0x80){
			writePC(getPC() + (offset|0xFF00) + 2);
		} else {
			writePC(getPC() + offset + 2);
		}
	} else {
		writePC(getPC() + 2);
	}
}

void instruction30(){
	unsigned char offset;
	if(getFlagC() == 0){
		offset = readCharFromMem(getPC()+1);
		if(offset&0x80){
			writePC(getPC() + (offset|0xFF00) + 2);
		} else {
			writePC(getPC() + offset + 2);
		}
	} else {
		writePC(getPC() + 2);
	}
}

INSTLDIMM16(01,BC)
INSTLDIMM16(11,DE)
INSTLDIMM16(21,HL)
INSTLDIMM16(31,SP)

void instruction02(){
	writeCharToMem(getBC(),getA());
	writePC(getPC()+1);
}
void instruction12(){
	writeCharToMem(getDE(),getA());
	writePC(getPC()+1);
}
void instruction22(){
	writeCharToMem(getHL(),getA());
	writeHL(getHL()+1);
	writePC(getPC()+1);
}
void instruction32(){
	writeCharToMem(getHL(),getA());
	writeHL(getHL()-1);
	writePC(getPC()+1);
}

INSTINC16(03,BC)
INSTINC16(13,DE)
INSTINC16(23,HL)
INSTINC16(33,SP)

INSTINC(04,B)
INSTINC(0C,C)
INSTINC(14,D)
INSTINC(1C,E)
INSTINC(24,H)
INSTINC(2C,L)
void instruction34(){
	unsigned char value = readCharFromMem(getHL()) + 1;
	writeCharToMem(getHL(),value);
	if(value == 0){
		setFlagZ();
	} else {
		clearFlagZ();
	}
	if((value&0xF) == 0){
		setFlagH();
	} else {
		clearFlagH();
	}
	clearFlagN();
	writePC(getPC()+1);
}
INSTINC(3C,A)

INSTDEC(05,B)
INSTDEC(0D,C)
INSTDEC(15,D)
INSTDEC(1D,E)
INSTDEC(25,H)
INSTDEC(2D,L)
void instruction35(){
	unsigned char value = readCharFromMem(getHL()) - 1;
	writeCharToMem(getHL(),value);
	if(value == 0){
		setFlagZ();
	} else {
		clearFlagZ();
	}
	if((value&0xF) == 0xF){
		setFlagH();
	} else {
		clearFlagH();
	}
	setFlagN();
	writePC(getPC()+1);
}
INSTDEC(3D,A)

INSTLDIMM(06,B)
INSTLDIMM(0E,C)
INSTLDIMM(16,D)
INSTLDIMM(1E,E)
INSTLDIMM(26,H)
INSTLDIMM(2E,L)
void instruction36(){
	writeCharToMem(getHL(),readCharFromMem(getPC()+1));
	writePC(getPC()+2);
}
INSTLDIMM(3E,A)

void instruction07(){
	//RLCA
	if(getA()&0x80){
		setFlagC();
		writeA((getA()<<1)&0xFF | 1);
	} else {
		clearFlagC();
		writeA((getA()<<1)&0xFE);
	}
	clearFlagZ();
	clearFlagH();
	clearFlagN();
	writePC(getPC()+1);
}

void instruction17(){
	//RLA
	if(getA()&0x80){
		writeA((getA()<<1)&0xFE | (getFlagC()&1));
		setFlagC();
	} else {
		writeA((getA()<<1)&0xFE | (getFlagC()&1));
		clearFlagC();
	}
	clearFlagH();
	clearFlagN();
	clearFlagZ();
	writePC(getPC()+1);
}

void instruction27(){
	//DAA
	if((getA()&0xF)>9||getFlagH()==1){
		if(getFlagN()==0){
			writeA(getA() + 6);
		} else {
			writeA(getA() - 6);
		}
	}
	if((getA()&0xF0)>0x9F||getFlagC()==1){
		if(getFlagN()==0){
			writeA(getA() + 0x60);
		} else {
			writeA(getA() - 0x60);
		}
		setFlagC();
	} else {
		clearFlagC();
	}
	if(getA() == 0){
		setFlagZ();
	} else {
		clearFlagZ();
	}
	clearFlagH();
	writePC(getPC()+1);
}

void instruction37(){
	//SCF
	clearFlagN();
	clearFlagH();
	setFlagC();
	writePC(getPC()+1);
}

void instruction08(){
	writeShortToMem(readShortFromMem(getPC()+1),getSP());
	writePC(getPC()+3);
}

void instruction18(){
	unsigned char offset;
	offset = readCharFromMem(getPC()+1);
	if(offset&0x80){
		writePC(getPC() + (offset|0xFF00) + 2);
	} else {
		writePC(getPC() + offset + 2);
	}
}

void instruction28(){
	unsigned char offset;
	if(getFlagZ() == 1){
		offset = readCharFromMem(getPC()+1);
		if(offset&0x80){
			writePC(getPC() + (offset|0xFF00) + 2);
		} else {
			writePC(getPC() + offset + 2);
		}
	} else {
		writePC(getPC() + 2);
	}
}

void instruction38(){
	unsigned char offset;
	if(getFlagC() == 1){
		offset = readCharFromMem(getPC()+1);
		if(offset&0x80){
			writePC(getPC() + (offset|0xFF00) + 2);
		} else {
			writePC(getPC() + offset + 2);
		}
	} else {
		writePC(getPC() + 2);
	}
}

INSTADDREG16(09,BC)
INSTADDREG16(19,DE)
INSTADDREG16(29,HL)
INSTADDREG16(39,SP)

void instruction0A(){
	writeA(readCharFromMem(getBC()));
	writePC(getPC()+1);
}
void instruction1A(){
	writeA(readCharFromMem(getDE()));
	writePC(getPC()+1);
}
void instruction2A(){
	writeA(readCharFromMem(getHL()));
	writeHL(getHL()+1);
	writePC(getPC()+1);
}
void instruction3A(){
	writeA(readCharFromMem(getHL()));
	writeHL(getHL()-1);
	writePC(getPC()+1);
}

INSTDEC16(0B,BC)
INSTDEC16(1B,DE)
INSTDEC16(2B,HL)
INSTDEC16(3B,SP)

void instruction0F(){
	//RRCA
	if(getA()&1){
		writeA((getA()>>1)&0x7F | 0x80);
		setFlagC();
	} else {
		writeA((getA()>>1)&0x7F);
		clearFlagC();
	}
	clearFlagZ();
	clearFlagH();
	clearFlagN();
	writePC(getPC()+1);
}

void instruction1F(){
	//RRA
	if(getA()&1){
		writeA((getA()>>1)&0x7F|(getFlagC()&1)<<7);
		setFlagC();
	} else {
		writeA((getA()>>1)&0x7F|(getFlagC()&1)<<7);
		clearFlagC();
	}
	clearFlagZ();
	clearFlagH();
	clearFlagN();
	writePC(getPC()+1);
}

void instruction2F(){
	//CPL
	writeA(getA()^0xFF);
	setFlagH();
	setFlagN();
	writePC(getPC()+1);
}

void instruction3F(){
	//CCF
	if(getFlagC()==0){
		setFlagC();
	} else {
		clearFlagC();
	}
	clearFlagH();
	clearFlagN();
	writePC(getPC()+1);
}

INSTLD(40,B,B)
INSTLD(41,B,C)
INSTLD(42,B,D)
INSTLD(43,B,E)
INSTLD(44,B,H)
INSTLD(45,B,L)
INSTLDFROMMEM(46,B)
INSTLD(47,B,A)

INSTLD(48,C,B)
INSTLD(49,C,C)
INSTLD(4A,C,D)
INSTLD(4B,C,E)
INSTLD(4C,C,H)
INSTLD(4D,C,L)
INSTLDFROMMEM(4E,C)
INSTLD(4F,C,A)

INSTLD(50,D,B)
INSTLD(51,D,C)
INSTLD(52,D,D)
INSTLD(53,D,E)
INSTLD(54,D,H)
INSTLD(55,D,L)
INSTLDFROMMEM(56,D)
INSTLD(57,D,A)

INSTLD(58,E,B)
INSTLD(59,E,C)
INSTLD(5A,E,D)
INSTLD(5B,E,E)
INSTLD(5C,E,H)
INSTLD(5D,E,L)
INSTLDFROMMEM(5E,E)
INSTLD(5F,E,A)

INSTLD(60,H,B)
INSTLD(61,H,C)
INSTLD(62,H,D)
INSTLD(63,H,E)
INSTLD(64,H,H)
INSTLD(65,H,L)
INSTLDFROMMEM(66,H)
INSTLD(67,H,A)

INSTLD(68,L,B)
INSTLD(69,L,C)
INSTLD(6A,L,D)
INSTLD(6B,L,E)
INSTLD(6C,L,H)
INSTLD(6D,L,L)
INSTLDFROMMEM(6E,L)
INSTLD(6F,L,A)

INSTLDTOMEM(70,B)
INSTLDTOMEM(71,C)
INSTLDTOMEM(72,D)
INSTLDTOMEM(73,E)
INSTLDTOMEM(74,H)
INSTLDTOMEM(75,L)
INSTLDTOMEM(77,A)

void instruction76(){
	//STOP SHOULD NEVER BE RUN
	return;
}

INSTLD(78,A,B)
INSTLD(79,A,C)
INSTLD(7A,A,D)
INSTLD(7B,A,E)
INSTLD(7C,A,H)
INSTLD(7D,A,L)
INSTLDFROMMEM(7E,A)
INSTLD(7F,A,A)

INSTADD(80,B)
INSTADD(81,C)
INSTADD(82,D)
INSTADD(83,E)
INSTADD(84,H)
INSTADD(85,L)
void instruction86(){
	unsigned char begin = getA();
	
	writeA(begin+readCharFromMem(getHL()));
	if(getA()==0){
		setFlagZ();
	} else {
		clearFlagZ();
	}
	clearFlagN();
	if((begin&0xF)>(getA()&0xF)){
		setFlagH();
	} else {
		clearFlagH();
	}
	if((begin&0xFF)>(getA()&0xFF)){
		setFlagC();
	} else {
		clearFlagC();
	}
	writePC(getPC()+1);
}
INSTADD(87,A)

INSTADC(88,B)
INSTADC(89,C)
INSTADC(8A,D)
INSTADC(8B,E)
INSTADC(8C,H)
INSTADC(8D,L)
void instruction8E(){
	unsigned char begin = getA();
	
	writeA(begin+readCharFromMem(getHL()));
	if(getFlagC()) writeA(getA()+1);
	if(getA()==0){
		setFlagZ();
	} else {
		clearFlagZ();
	}
	clearFlagN();
	if((begin&0xF)>(getA()&0xF)){
		setFlagH();
	} else {
		clearFlagH();
	}
	if((begin&0xFF)>(getA()&0xFF)){
		setFlagC();
	} else {
		clearFlagC();
	}
	writePC(getPC()+1);
}
INSTADC(8F,A)

INSTSUB(90,B)
INSTSUB(91,C)
INSTSUB(92,D)
INSTSUB(93,E)
INSTSUB(94,H)
INSTSUB(95,L)
void instruction96(){
	unsigned char begin = getA();
	
	writeA(begin-readCharFromMem(getHL()));
	if(getA()==0){
		setFlagZ();
	} else {
		clearFlagZ();
	}
	clearFlagN();
	if((begin&0xF)>(getA()&0xF)){
		setFlagH();
	} else {
		clearFlagH();
	}
	if((begin&0xFF)>(getA()&0xFF)){
		setFlagC();
	} else {
		clearFlagC();
	}
	writePC(getPC()+1);
}
INSTSUB(97,A)

INSTSBC(98,B)
INSTSBC(99,C)
INSTSBC(9A,D)
INSTSBC(9B,E)
INSTSBC(9C,H)
INSTSBC(9D,L)
void instruction9E(){
	unsigned char begin = getA();
	
	writeA(begin-readCharFromMem(getHL()));
	if(getFlagC()) writeA(getA()-1);
	if(getA()==0){
		setFlagZ();
	} else {
		clearFlagZ();
	}
	clearFlagN();
	if((begin&0xF)>(getA()&0xF)){
		setFlagH();
	} else {
		clearFlagH();
	}
	if((begin&0xFF)>(getA()&0xFF)){
		setFlagC();
	} else {
		clearFlagC();
	}
	writePC(getPC()+1);
}
INSTSBC(9F,A)

INSTAND(A0,B)
INSTAND(A1,C)
INSTAND(A2,D)
INSTAND(A3,E)
INSTAND(A4,H)
INSTAND(A5,L)
void instructionA6(){ 
	writeA(readCharFromMem(getHL())&getA()); 
	if((getA()&0xFF)==0){ 
		setFlagZ(); 
	} else { 
		clearFlagZ(); 
	} 
	clearFlagN(); 
	setFlagH(); 
	clearFlagC(); 
	writePC(getPC()+1); 
}
INSTAND(A7,A)

INSTXOR(A8,B)
INSTXOR(A9,C)
INSTXOR(AA,D)
INSTXOR(AB,E)
INSTXOR(AC,H)
INSTXOR(AD,L)
void instructionAE(){ 
	writeA(readCharFromMem(getHL())^getA()); 
	if((getA()&0xFF)==0){ 
		setFlagZ(); 
	} else { 
		clearFlagZ(); 
	} 
	clearFlagN(); 
	clearFlagH(); 
	clearFlagC(); 
	writePC(getPC()+1); 
}
INSTXOR(AF,A)
/*void instructionAF(){
	writeA(0);
	writePC(getPC()+1);
}*/

INSTOR(B0,B)
INSTOR(B1,C)
INSTOR(B2,D)
INSTOR(B3,E)
INSTOR(B4,H)
INSTOR(B5,L)
void instructionB6(){ 
	writeA(readCharFromMem(getHL())|getA()); 
	if((getA()&0xFF)==0){ 
		setFlagZ(); 
	} else { 
		clearFlagZ(); 
	} 
	clearFlagN(); 
	clearFlagH(); 
	clearFlagC(); 
	writePC(getPC()+1); 
}
INSTOR(B7,A)

INSTCP(B8,B)
INSTCP(B9,C)
INSTCP(BA,D)
INSTCP(BB,E)
INSTCP(BC,H)
INSTCP(BD,L)
void instructionBE(){
	unsigned char begin = getA();
	unsigned char res;
	
	res = begin-readCharFromMem(getHL());
	if(res==0){
		setFlagZ();
	} else {
		clearFlagZ();
	}
	clearFlagN();
	if((begin&0xF)>(res&0xF)){
		setFlagH();
	} else {
		clearFlagH();
	}
	if((begin&0xFF)>(res&0xFF)){
		setFlagC();
	} else {
		clearFlagC();
	}
	writePC(getPC()+1);
}
INSTCP(BF,A)

//RET NZ
void instructionC0(){

	if(!getFlagZ()){
		writePC(readShortFromMem(getSP()));
		writeSP(getSP()+2);
	} else {
		writePC(getPC()+1);
	}
}
//RET NC
void instructionD0(){

	if(!getFlagC()){
		writePC(readShortFromMem(getSP()));
		writeSP(getSP()+2);
	} else {
		writePC(getPC()+1);
	}
}

//LDH (a8),A
void instructionE0(){
	writeCharToMem(readCharFromMem(getPC()+1)+0xFF00,getA());
	
	writePC(getPC()+2);
}

//LDH A,(a8)
void instructionF0(){
	writeA(readCharFromMem(readCharFromMem(getPC()+1)+0xFF00));
	writePC(getPC()+2);
}	


//POP BC
void instructionC1(){
	writeBC(readShortFromMem(getSP()));
	
	writeSP(getSP()+2);
	writePC(getPC()+1);
}
//POP DE
void instructionD1(){
	writeDE(readShortFromMem(getSP()));
	
	writeSP(getSP()+2);
	writePC(getPC()+1);
}
//POP HL
void instructionE1(){
	writeHL(readShortFromMem(getSP()));
	
	writeSP(getSP()+2);
	writePC(getPC()+1);
}
//POP AF
void instructionF1(){
	writeAF(readShortFromMem(getSP()));
	
	writeSP(getSP()+2);
	writePC(getPC()+1);
}

//JP NZ,a16
void instructionC2(){

	if(!getFlagZ()){
		//printf("PC: %hX",getPC()&0xFFFF);
		writePC(readShortFromMem(getPC()+1));
		//printf(" JP: %hX\n",getPC()&0xFFFF);
		//while(1);
	} else {
		writePC(getPC()+3);
	}
}
//JP NC,a16
void instructionD2(){

	if(!getFlagC()){
		//printf("PC: %hX",getPC()&0xFFFF);
		writePC(readShortFromMem(getPC()+1));
		//printf(" JP: %hX\n",getPC()&0xFFFF);
		//while(1);
	} else {
		writePC(getPC()+3);
	}
}

//LDH (C),A
void instructionE2(){
	writeCharToMem((getC()&0xFF)+0xFF00,getA());
	
	writePC(getPC()+1);
}
//LDH A,(C)
void instructionF2(){
	writeA(readCharFromMem((getC()&0xFF)+0xFF00));
	
	writePC(getPC()+1);
}	

//JP a16
void instructionC3(){
	writePC(readShortFromMem(getPC()+1));
}
//DI	Disable Interrupts
void instructionF3(){
	IME = 0;
	writePC(getPC()+1);
}

//CALL NZ, a16
void instructionC4(){

	if(!getFlagZ()){
		writeSP(getSP()-2);
		writeShortToMem(getSP(),getPC()+3);
		writePC(readShortFromMem(getPC()+1));
		
	} else {
		writePC(getPC()+3);
	}
}
//CALL NC, a16
void instructionD4(){

	if(!getFlagC()){
		writeSP(getSP()-2);
		writeShortToMem(getSP(),getPC()+3);
		writePC(readShortFromMem(getPC()+1));
		
	} else {
		writePC(getPC()+3);
	}
}

//PUSH BC
void instructionC5(){

	writeSP(getSP()-2);
	writeShortToMem(getSP(),getBC());
	
	writePC(getPC()+1);
}
//PUSH DE
void instructionD5(){

	writeSP(getSP()-2);
	writeShortToMem(getSP(),getDE());
	
	writePC(getPC()+1);
}
//PUSH HL
void instructionE5(){

	writeSP(getSP()-2);
	writeShortToMem(getSP(),getHL());
	
	writePC(getPC()+1);
}
//PUSH AF
void instructionF5(){

	writeSP(getSP()-2);
	writeShortToMem(getSP(),getAF());
	
	writePC(getPC()+1);
}


//ADD A,d8
void instructionC6(){ 
unsigned char begin = getA(); 
	writeA(begin+readCharFromMem(getPC()+1)); 
	if((getA()&0xFF)==0){ 
		setFlagZ(); 
	} else { 
		clearFlagZ(); 
	} 
	clearFlagN(); 
	if((begin&0xF)>(getA()&0xF)){
		setFlagH(); 
	} else { 
		clearFlagH(); 
	} 
	if((begin&0xFF)>(getA()&0xFF)){ 
		setFlagC(); 
	} else { 
		clearFlagC(); 
	} 
	writePC(getPC()+2); 
}
//SUB A,d8
void instructionD6(){ 
unsigned char begin = getA(); 
	writeA(begin-readCharFromMem(getPC()+1)); 
	if((getA()&0xFF)==0){ 
		setFlagZ(); 
	} else { 
		clearFlagZ(); 
	} 
	setFlagN(); 
	if((begin&0xF)<(getA()&0xF)){ 
		setFlagH(); 
	} else { 
		clearFlagH(); 
	} 
	if((begin&0xFF)<(getA()&0xFF)){ 
		setFlagC(); 
	} else { 
		clearFlagC(); 
	} 
	writePC(getPC()+2); 
}
//AND d8
void instructionE6(){ 
	writeA(readCharFromMem(getPC()+1)&getA()); 
	if((getA()&0xFF)==0){ 
		setFlagZ(); 
	} else { 
		clearFlagZ(); 
	} 
	clearFlagN(); 
	setFlagH(); 
	clearFlagC(); 
	writePC(getPC()+2); 
}
//OR d8
void instructionF6(){ 
	writeA(readCharFromMem(getPC()+1)|getA()); 
	if((getA()&0xFF)==0){ 
		setFlagZ(); 
	} else { 
		clearFlagZ(); 
	} 
	clearFlagN(); 
	clearFlagH(); 
	clearFlagC(); 
	writePC(getPC()+2); 
}

INSTRST(C7,0x00)
INSTRST(D7,0x10)
INSTRST(E7,0x20)
INSTRST(F7,0x30)
INSTRST(CF,0x8)
INSTRST(DF,0x18)
INSTRST(EF,0x28)
INSTRST(FF,0x38)

//RET Z
void instructionC8(){

	if(getFlagZ()){
		writePC(readShortFromMem(getSP()));
		writeSP(getSP()+2);
	} else {
		writePC(getPC()+1);
	}
}
//RET C
void instructionD8(){

	if(getFlagC()){
		writePC(readShortFromMem(getSP()));
		writeSP(getSP()+2);
	} else {
		writePC(getPC()+1);
	}
}

//ADD SP,r8
void instructionE8(){
	unsigned short begin = getSP(); 
	signed char arg = (signed char)readCharFromMem(getPC()+1);
	writeSP(begin+arg); 
	clearFlagZ();
	clearFlagN(); 
	if((begin&0xF)>(getSP()&0xF)){
		setFlagH(); 
	} else { 
		clearFlagH(); 
	} 
	if((begin&0xFF)>(getSP()&0xFF)){ 
		setFlagC(); 
	} else { 
		clearFlagC(); 
	} 
	writePC(getPC()+2); 
}

//LD HL, SP+r8
void instructionF8(){
	unsigned short begin = getSP(); 
	signed char arg = (signed char)readCharFromMem(getPC()+1);
	writeHL(begin+arg); 
	clearFlagZ();
	clearFlagN(); 
	if((begin&0xF)>(getHL()&0xF)){ 
		setFlagH(); 
	} else {  
		clearFlagH(); 
	} 
	if((begin&0xFF)>(getHL()&0xFF)){ 
		setFlagC(); 
	} else { 
		clearFlagC(); 
	} 
	writePC(getPC()+2); 
}

//RET
void instructionC9(){
	writePC(readShortFromMem(getSP()));
	writeSP(getSP()+2);
}
//RETI
void instructionD9(){
	writePC(readShortFromMem(getSP()));
	writeSP(getSP()+2);
	IME = 1;
}

//JP (HL)
void instructionE9(){
	writePC(getHL());	//HL points to address??? from: writePC(getHL())
}
//LD SP,HL
void instructionF9(){
	writeSP(getHL());
	writePC(getPC()+1);
}

//JP Z,a16
void instructionCA(){
	if(getFlagZ()){
		writePC(readShortFromMem(getPC()+1));
	} else {
		writePC(getPC()+3);
	}
}
//JP C,a16
void instructionDA(){
	if(getFlagC()){
		writePC(readShortFromMem(getPC()+1));
	} else {
		writePC(getPC()+3);
	}
}

//LD (a16),A
void instructionEA(){
	writeCharToMem(readShortFromMem(getPC()+1),getA());
	writePC(getPC()+3);
}
//LD A,(a16)
void instructionFA(){
	writeA(readCharFromMem(readShortFromMem(getPC()+1)));
	writePC(getPC()+3);
}	

//CB PREFIX handled by Core

//EI - enable Interrupts
void instructionFB(){
	IME = 1;
	writePC(getPC()+1);
}
	
//CALL Z, a16
void instructionCC(){

	if(getFlagZ()){
		writeSP(getSP()-2);
		writeShortToMem(getSP(),getPC()+3);
		writePC(readShortFromMem(getPC()+1));
		
	} else {
		writePC(getPC()+3);
	}
}
//CALL C, a16
void instructionDC(){

	if(getFlagC()){
		writeSP(getSP()-2);
		writeShortToMem(getSP(),getPC()+3);
		writePC(readShortFromMem(getPC()+1));
		
	} else {
		writePC(getPC()+3);
	}
}
//CALL a16
void instructionCD(){
	writeSP(getSP()-2);
	writeShortToMem(getSP(),getPC()+3);
	writePC(readShortFromMem(getPC()+1));
}

//ADC A,d8
void instructionCE(){ 
unsigned char begin = getA(); 
	writeA(begin+readCharFromMem(getPC()+1));
	if(getFlagC()) writeA(getA()+1); 
	if((getA()&0xFF)==0){ 
		setFlagZ();
	} else { 
		clearFlagZ(); 
	}
	clearFlagN(); 
	if((begin&0xF)>(getA()&0xF)){ 
		setFlagH(); 
	} else { 
		clearFlagH(); 
	} 
	if((begin&0xFF)>(getA()&0xFF)){ 
		setFlagC(); 
	} else { 
		clearFlagC(); 
	} 
	writePC(getPC()+2); 
}
//SBC A,d8
void instructionDE(){ 
unsigned char begin = getA(); 
	writeA(begin-readCharFromMem(getPC()+1)); 
	if(getFlagC()) writeA(getA()-1); 
	if((getA()&0xFF)==0){ 
		setFlagZ(); 
	} else { 
		clearFlagZ(); 
	} 
	setFlagN(); 
	if((begin&0xF)<(getA()&0xF)){ 
		setFlagH(); 
	} else { 
		clearFlagH(); 
	} 
	if((begin&0xFF)<(getA()&0xFF)){ 
		setFlagC(); 
	} else { 
		clearFlagC();
	} 
	writePC(getPC()+2); 
}
//XOR d8
void instructionEE(){ 
	writeA(readCharFromMem(getPC()+1)^getA()); 
	if((getA()&0xFF)==0){ 
		setFlagZ(); 
	} else { 
		clearFlagZ(); 
	} 
	clearFlagN(); 
	clearFlagH(); 
	clearFlagC(); 
	writePC(getPC()+2); 
}
//CP d8
void instructionFE(){ 
unsigned char begin = getA(); 
unsigned char res; 
	res = begin-readCharFromMem(getPC()+1); 
	if((res&0xFF)==0){ 
		setFlagZ(); 
	} else { 
		clearFlagZ(); 
	} 
	setFlagN(); 
	if((begin&0xF)<(res&0xF)){ 
		setFlagH(); 
	} else { 
		clearFlagH(); 
	} 
	if((begin&0xFF)<(res&0xFF)){ 
		setFlagC(); 
	} else { 
		clearFlagC(); 
	} 
	//printf("0x%hhX\n",getF()&0xFF);
	writePC(getPC()+2); 
}

/**********************************\
*		CB INSTRUCTIONS!!!		   *
\**********************************/

INSTCBRLC(00,B)
INSTCBRLC(01,C)
INSTCBRLC(02,D)
INSTCBRLC(03,E)
INSTCBRLC(04,H)
INSTCBRLC(05,L)
void instructionCB06(){ 
	if(readCharFromMem(getHL())&0x80){ 
		setFlagC();	
		writeCharToMem(getHL(),(readCharFromMem(getHL())<<1)|0x1); 
	} else {
		clearFlagC(); 
		writeCharToMem(getHL(),readCharFromMem(getHL())<<1); 
	} 
	if((readCharFromMem(getHL())&0xFF)==0){ 
		setFlagZ(); 
	} else { 
		clearFlagZ(); 
	} 
	writePC(getPC()+1);
}
INSTCBRLC(07,A)

INSTCBRRC(08,B)
INSTCBRRC(09,C)
INSTCBRRC(0A,D)
INSTCBRRC(0B,E)
INSTCBRRC(0C,H)
INSTCBRRC(0D,L)
void instructionCB0E(){ 
	if(readCharFromMem(getHL())&0x1==1){ 
		setFlagC(); 
		writeCharToMem(getHL(),(readCharFromMem(getHL())>>1)&0x7F|0x80); 
	} else { 
		clearFlagC(); 
		writeCharToMem(getHL(),(readCharFromMem(getHL())>>1)&0x7F); 
	} 
	if((readCharFromMem(getHL())&0xFF)==0){ 
		setFlagZ(); 
	} else { 
		clearFlagZ(); 
	} 
	clearFlagN(); 
	clearFlagH(); 
	writePC(getPC()+1); 
}
INSTCBRRC(0F,A)
	
INSTCBRL(10,B)
INSTCBRL(11,C)
INSTCBRL(12,D)
INSTCBRL(13,E)
INSTCBRL(14,H)
INSTCBRL(15,L)
void instructionCB16(){ 
	if(readCharFromMem(getHL())&0x80){ 
		writeCharToMem(getHL(),(readCharFromMem(getHL())<<1)|getFlagC()); 
		setFlagC(); 
	} else { 
		writeCharToMem(getHL(),(readCharFromMem(getHL())<<1)|getFlagC()); 
		clearFlagC(); 
	} 
	if((readCharFromMem(getHL())&0xFF)==0){
		setFlagZ(); 
	} else { 
		clearFlagZ(); 
	} 
	clearFlagN(); 
	clearFlagH(); 
	writePC(getPC()+1); 
}
INSTCBRL(17,A)

INSTCBRR(18,B)
INSTCBRR(19,C)
INSTCBRR(1A,D)
INSTCBRR(1B,E)
INSTCBRR(1C,H)
INSTCBRR(1D,L)
void instructionCB1E(){ 
	if(readCharFromMem(getHL()) &0x1){ 
		writeCharToMem(getHL(),((readCharFromMem(getHL())&0xFF)>>1)|(getFlagC()<<7)); 
		setFlagC(); 
	} else { 
		writeCharToMem(getHL(),((readCharFromMem(getHL())&0xFF)>>1)|(getFlagC()<<7)); 
		clearFlagC(); 
	} 
	if((readCharFromMem(getHL())&0xFF)==0){
		setFlagZ(); 
	} else { 
		clearFlagZ(); 
	} 
	clearFlagN(); 
	clearFlagH(); 
	writePC(getPC()+1); 
}
INSTCBRR(1F,A)

INSTCBSLA(20,B)
INSTCBSLA(21,C)
INSTCBSLA(22,D)
INSTCBSLA(23,E)
INSTCBSLA(24,H)
INSTCBSLA(25,L)
void instructionCB26(){ 
	if(readCharFromMem(getHL())&0x80){ 
		setFlagC(); 
	} else { 
		clearFlagC(); 
	} 
	writeCharToMem(getHL(),readCharFromMem(getHL())<<1); 
	if((readCharFromMem(getHL()) &0xFF)==0){ 
		setFlagZ(); 
	} else { 
		clearFlagZ(); 
	} 
	clearFlagN(); 
	clearFlagH(); 
	writePC(getPC()+1); 
}
INSTCBSLA(27,A)

INSTCBSRA(28,B)
INSTCBSRA(29,C)
INSTCBSRA(2A,D)
INSTCBSRA(2B,E)
INSTCBSRA(2C,H)
INSTCBSRA(2D,L)
void instructionCB2E(){ 
	if(readCharFromMem(getHL())&0x01){ 
		setFlagC(); 
	} else { 
		clearFlagC(); 
	} 
	writeCharToMem(getHL(),((readCharFromMem(getHL())&0xFF)>>1)|(readCharFromMem(getHL())&0x80)); 
	if((readCharFromMem(getHL())&0xFF) == 0){ 
		setFlagZ(); 
	} else { 
		clearFlagZ(); 
	} 
	clearFlagN(); 
	clearFlagH(); 
	writePC(getPC()+1); 
}
INSTCBSRA(2F,A)

INSTCBSWAP(30,B)
INSTCBSWAP(31,C)
INSTCBSWAP(32,D)
INSTCBSWAP(33,E)
INSTCBSWAP(34,H)
INSTCBSWAP(35,L)
void instructionCB36(){ 
	writeCharToMem(getHL(),((readCharFromMem(getHL())<<4)|((readCharFromMem(getHL())>>4)&0x0F))&0xFF); 
	if((readCharFromMem(getHL())&0xFF)==0){ 
		setFlagZ(); 
	} else { 
		clearFlagZ(); 
	} 
	clearFlagN(); 
	clearFlagH(); 
	clearFlagC(); 
	writePC(getPC()+1); 
}
INSTCBSWAP(37,A)

INSTCBSRL(38,B)
INSTCBSRL(39,C)
INSTCBSRL(3A,D)
INSTCBSRL(3B,E)
INSTCBSRL(3C,H)
INSTCBSRL(3D,L)
void instructionCB3E(){ 
	if(readCharFromMem(getHL())&0x1){ 
		setFlagC(); 
	} else { 
		clearFlagC(); 
	} 
	writeCharToMem(getHL(),(readCharFromMem(getHL())&0xFF)>>1); 
	if((readCharFromMem(getHL())&0xFF) == 0){ 
		setFlagZ(); 
	} else { 
		clearFlagZ(); 
	} 
	clearFlagN(); 
	clearFlagH(); 
	writePC(getPC()+1); 
}

INSTCBSRL(3F,A)

INSTCBBIT(40,B,0)
INSTCBBIT(41,C,0)
INSTCBBIT(42,D,0)
INSTCBBIT(43,E,0)
INSTCBBIT(44,H,0)
INSTCBBIT(45,L,0)
INSTCBBITMEM(46,0)
INSTCBBIT(47,A,0)

INSTCBBIT(48,B,1)
INSTCBBIT(49,C,1)
INSTCBBIT(4A,D,1)
INSTCBBIT(4B,E,1)
INSTCBBIT(4C,H,1)
INSTCBBIT(4D,L,1)
INSTCBBITMEM(4E,1)
INSTCBBIT(4F,A,1)

INSTCBBIT(50,B,2)
INSTCBBIT(51,C,2)
INSTCBBIT(52,D,2)
INSTCBBIT(53,E,2)
INSTCBBIT(54,H,2)
INSTCBBIT(55,L,2)
INSTCBBITMEM(56,2)
INSTCBBIT(57,A,2)

INSTCBBIT(58,B,3)
INSTCBBIT(59,C,3)
INSTCBBIT(5A,D,3)
INSTCBBIT(5B,E,3)
INSTCBBIT(5C,H,3)
INSTCBBIT(5D,L,3)
INSTCBBITMEM(5E,3)
INSTCBBIT(5F,A,3)

INSTCBBIT(60,B,4)
INSTCBBIT(61,C,4)
INSTCBBIT(62,D,4)
INSTCBBIT(63,E,4)
INSTCBBIT(64,H,4)
INSTCBBIT(65,L,4)
INSTCBBITMEM(66,4)
INSTCBBIT(67,A,4)

INSTCBBIT(68,B,5)
INSTCBBIT(69,C,5)
INSTCBBIT(6A,D,5)
INSTCBBIT(6B,E,5)
INSTCBBIT(6C,H,5)
INSTCBBIT(6D,L,5)
INSTCBBITMEM(6E,5)
INSTCBBIT(6F,A,5)

INSTCBBIT(70,B,6)
INSTCBBIT(71,C,6)
INSTCBBIT(72,D,6)
INSTCBBIT(73,E,6)
INSTCBBIT(74,H,6)
INSTCBBIT(75,L,6)
INSTCBBITMEM(76,6)
INSTCBBIT(77,A,6)

INSTCBBIT(78,B,7)
INSTCBBIT(79,C,7)
INSTCBBIT(7A,D,7)
INSTCBBIT(7B,E,7)
INSTCBBIT(7C,H,7)
INSTCBBIT(7D,L,7)
INSTCBBITMEM(7E,7)
INSTCBBIT(7F,A,7)

INSTCBRES(80,B,0)
INSTCBRES(81,C,0)
INSTCBRES(82,D,0)
INSTCBRES(83,E,0)
INSTCBRES(84,H,0)
INSTCBRES(85,L,0)
INSTCBRESMEM(86,0)
INSTCBRES(87,A,0)

INSTCBRES(88,B,1)
INSTCBRES(89,C,1)
INSTCBRES(8A,D,1)
INSTCBRES(8B,E,1)
INSTCBRES(8C,H,1)
INSTCBRES(8D,L,1)
INSTCBRESMEM(8E,1)
INSTCBRES(8F,A,1)

INSTCBRES(90,B,2)
INSTCBRES(91,C,2)
INSTCBRES(92,D,2)
INSTCBRES(93,E,2)
INSTCBRES(94,H,2)
INSTCBRES(95,L,2)
INSTCBRESMEM(96,2)
INSTCBRES(97,A,2)

INSTCBRES(98,B,3)
INSTCBRES(99,C,3)
INSTCBRES(9A,D,3)
INSTCBRES(9B,E,3)
INSTCBRES(9C,H,3)
INSTCBRES(9D,L,3)
INSTCBRESMEM(9E,3)
INSTCBRES(9F,A,3)

INSTCBRES(A0,B,4)
INSTCBRES(A1,C,4)
INSTCBRES(A2,D,4)
INSTCBRES(A3,E,4)
INSTCBRES(A4,H,4)
INSTCBRES(A5,L,4)
INSTCBRESMEM(A6,4)
INSTCBRES(A7,A,4)

INSTCBRES(A8,B,5)
INSTCBRES(A9,C,5)
INSTCBRES(AA,D,5)
INSTCBRES(AB,E,5)
INSTCBRES(AC,H,5)
INSTCBRES(AD,L,5)
INSTCBRESMEM(AE,5)
INSTCBRES(AF,A,5)

INSTCBRES(B0,B,6)
INSTCBRES(B1,C,6)
INSTCBRES(B2,D,6)
INSTCBRES(B3,E,6)
INSTCBRES(B4,H,6)
INSTCBRES(B5,L,6)
INSTCBRESMEM(B6,6)
INSTCBRES(B7,A,6)

INSTCBRES(B8,B,7)
INSTCBRES(B9,C,7)
INSTCBRES(BA,D,7)
INSTCBRES(BB,E,7)
INSTCBRES(BC,H,7)
INSTCBRES(BD,L,7)
INSTCBRESMEM(BE,7)
INSTCBRES(BF,A,7)

INSTCBSET(C0,B,0)
INSTCBSET(C1,C,0)
INSTCBSET(C2,D,0)
INSTCBSET(C3,E,0)
INSTCBSET(C4,H,0)
INSTCBSET(C5,L,0)
INSTCBSETMEM(C6,0)
INSTCBSET(C7,A,0)

INSTCBSET(C8,B,1)
INSTCBSET(C9,C,1)
INSTCBSET(CA,D,1)
INSTCBSET(CB,E,1)
INSTCBSET(CC,H,1)
INSTCBSET(CD,L,1)
INSTCBSETMEM(CE,1)
INSTCBSET(CF,A,1)

INSTCBSET(D0,B,2)
INSTCBSET(D1,C,2)
INSTCBSET(D2,D,2)
INSTCBSET(D3,E,2)
INSTCBSET(D4,H,2)
INSTCBSET(D5,L,2)
INSTCBSETMEM(D6,2)
INSTCBSET(D7,A,2)

INSTCBSET(D8,B,3)
INSTCBSET(D9,C,3)
INSTCBSET(DA,D,3)
INSTCBSET(DB,E,3)
INSTCBSET(DC,H,3)
INSTCBSET(DD,L,3)
INSTCBSETMEM(DE,3)
INSTCBSET(DF,A,3)

INSTCBSET(E0,B,4)
INSTCBSET(E1,C,4)
INSTCBSET(E2,D,4)
INSTCBSET(E3,E,4)
INSTCBSET(E4,H,4)
INSTCBSET(E5,L,4)
INSTCBSETMEM(E6,4)
INSTCBSET(E7,A,4)

INSTCBSET(E8,B,5)
INSTCBSET(E9,C,5)
INSTCBSET(EA,D,5)
INSTCBSET(EB,E,5)
INSTCBSET(EC,H,5)
INSTCBSET(ED,L,5)
INSTCBSETMEM(EE,5)
INSTCBSET(EF,A,5)

INSTCBSET(F0,B,6)
INSTCBSET(F1,C,6)
INSTCBSET(F2,D,6)
INSTCBSET(F3,E,6)
INSTCBSET(F4,H,6)
INSTCBSET(F5,L,6)
INSTCBSETMEM(F6,6)
INSTCBSET(F7,A,6)

INSTCBSET(F8,B,7)
INSTCBSET(F9,C,7)
INSTCBSET(FA,D,7)
INSTCBSET(FB,E,7)
INSTCBSET(FC,H,7)
INSTCBSET(FD,L,7)
INSTCBSETMEM(FE,7)
INSTCBSET(FF,A,7)


