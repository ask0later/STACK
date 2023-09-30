#include <stdlib.h>
#include <climits>
#include <assert.h>
#include <stdio.h>

#include "stack.h"

#define STACK_DUMP(stk) StackDump(stk, errors, func, line, file)

const int NUM_ERRORS = 14;

int StackVerify(Stack* stk);

void DumpErrors(int error_num);
void StackDump(Stack* stk, int errors, const char* func, const int line, const char* file);