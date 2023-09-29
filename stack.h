#include <stdlib.h>
#include <climits>
#include <stdio.h>
#include <assert.h>
#include "enumstruct.h"


const int MIN_CAPACITY = 2;

void StackCtor(Stack* data, const int line, const char* file);
void StackDtor(Stack* data);

void StackPush(elem_t value, Stack* data, const int line, const char* file);
elem_t StackPop(Stack* data, const int line, const char* file);

void Re_Calloc(int more_or_less, Stack* data);

void VerifyCapacity(Stack* data);
long unsigned int HashFunction(void* ptr, size_t size);

void Verify(Stack* data, int errors, const char* func, const int line, const char* file);
int ErrorRate(Stack* data);



void NullVerify(Stack* data);


void StackDump(Stack* data, const char* func, const int line, const char* file);

void CleanFile();
