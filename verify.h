#include <stdlib.h>
#include <climits>
#include <assert.h>
#include <stdio.h>
#include "enumstruct.h"


int StackVerify(Stack* data);

void DumpErrors(int error_num);
void Verify(Stack* data);
int ErrorRate(Stack* data);

void CleanFile();

void StackDump(Stack* data, const char* func, const int line, const char* file);

int HashFunction(Stack* data);