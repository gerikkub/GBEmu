#include <stdlib.h>

#include "parse.h"
#include "getInst.h"

int IME; //Required so instructions will compile
   
static RegList activeReg;
static HashMap memory;

void writeAF(short value) {
   activeReg.A = (value >> 8) & 0xFF;
   activeReg.F = value & 0xFF;
}

void writeBC(short value) {
   activeReg.B = (value >> 8) & 0xFF;
   activeReg.C = value & 0xFF;
}

void writeDE(short value) {
   activeReg.D = (value >> 8) & 0xFF;
   activeReg.E = value & 0xFF;
}

void writeHL(short value) {
   activeReg.H = (value >> 8) & 0xFF;
   activeReg.L = value & 0xFF;
}

void writeSP(short value) {
   activeReg.SP = value;
}

void writePC(short value) {
   activeReg.PC = value;
}

void writeA(char value) {
   activeReg.A = value;
}

void writeF(char value) {
   activeReg.F = value;
}

void writeB(char value) {
   activeReg.B = value;
}

void writeC(char value) {
   activeReg.C = value;
}

void writeD(char value) {
   activeReg.D = value;
}

void writeE(char value) {
   activeReg.E = value;
}

void writeH(char value) {
   activeReg.H = value;
}

void writeL(char value) {
   activeReg.L = value;
}

unsigned short getAF() {
   return (activeReg.A << 8) | activeReg.F;
}

unsigned short getBC() {
   return (activeReg.B << 8) | activeReg.C;
}

unsigned short getDE() {
   return (activeReg.D << 8) | activeReg.E;
}

unsigned short getHL() {
   return (activeReg.H << 8) | activeReg.L;
}

unsigned short getSP() {
   return activeReg.SP;
}

unsigned short getPC() {
   return activeReg.PC;
}

unsigned char getA() {
   return activeReg.A;
}

unsigned char getF() {
   return activeReg.F;
}

unsigned char getB() {
   return activeReg.B;
}

unsigned char getC() {
   return activeReg.C;
}

unsigned char getD() {
   return activeReg.D;
}

unsigned char getE() {
   return activeReg.E;
}

unsigned char getH() {
   return activeReg.H;
}

unsigned char getL() {
   return activeReg.L;
}

void setFlagZ() {
   writeF(getF() | 0x80);
}
void setFlagN(){
	writeF(getF()|0x40);
}
void setFlagH(){
	writeF(getF()|0x20);
}
void setFlagC(){
	writeF(getF()|0x10);
}

void clearFlagZ(){
	writeF(getF()&(~(0x80)));
}

void clearFlagN(){
	writeF(getF()&(~(0x40)));
}

void clearFlagH(){
	writeF(getF()&(~(0x20)));
}

void clearFlagC(){
	writeF(getF()&(~(0x10)));
}

int getFlagZ(){
	return (getF()&0x80)>>7;
}

int getFlagN(){
	return (getF()&0x40)>>6;
}

int getFlagH(){
	return (getF()&0x20)>>5;
}

int getFlagC(){
	return (getF()&0x10)>>4;
}

void writeCharToMem(int loc, char value) {

   if(containsKeyHashMap(&memory, loc)) {
      deleteHashMap(&memory, loc);
   }
   addHashMap(&memory, loc, (int)value);
}

void writeShortToMem(int loc, short value) {
  
   writeCharToMem(loc + 1, (value&0xFF00) >> 8);
   writeCharToMem(loc, (value& 0xFF));
   
}

unsigned char readCharFromMem(int loc) {
   
   if(containsKeyHashMap(&memory, loc)) {
      return (unsigned char)getHashMap(&memory, loc);
   } else {
      return 0;
   }
}

unsigned short readShortFromMem(int loc){
	return (readCharFromMem(loc+1) <<8)|(readCharFromMem(loc)&0xFF);
}

int registerCompare(RegList reg1, RegList reg2) {
   return reg1.A == reg2.A && reg1.F == reg2.F
       && reg1.B == reg2.B && reg1.C == reg2.C
       && reg1.D == reg2.D && reg1.E == reg2.E
       && reg1.H == reg2.H && reg1.L == reg2.L
       && reg1.SP == reg2.SP && reg1.PC == reg2.PC;
}

int runTest(Test test, opcodeInstruction opcode, RegList *rResult, HashMap *mResult) {
   
   activeReg = test.regInit;
   memory = test.memInit;   

   opcode();

   *rResult = activeReg;
   *mResult = memory;

   if(!registerCompare(activeReg,test.regFinal)) {
      return -1;
   } else if(!equalsHashMap(&memory, &test.memFinal)) {
      return -2;
   }
   return 1;
}
