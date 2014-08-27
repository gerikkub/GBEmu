#ifndef _RUNTEST_H_
#define _RUNTEST_H_

#include "parse.h"
#include "hashMap.h"
#include "getInst.h"

int runTest(Test test, opcodeInstruction opcode, RegList *rResult, HashMap *mResult);

#endif
