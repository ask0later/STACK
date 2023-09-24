#include <stdlib.h>
#include <climits>
#include <stdio.h>
#include <assert.h>
#include "enumstruct.h"


const size_t MIN_CAPACITY = 4;

void StackCtor(Stack* data, const int line, const char* file);
void StackDtor(Stack* data);

void StackPush(int value, Stack* data, const int line, const char* file);
void StackPop(Stack* data, const int line, const char* file);

void Re_Calloc(int more_or_less, Stack* data);

int HashFunction(Stack* data);
void Verify(Stack* data);
void StackDump(Stack* data, const char* func, const int line, const char* file);

void CleanFile();
