#include <stdlib.h>
#include <climits>
#include <stdio.h>
#include <assert.h>

//#define valera
//#define hash


struct Stack
{
#ifdef valera
    unsigned long long int* leftValera;
#endif
    int* sequence;
    size_t size, capacity;
#ifdef valera
    unsigned long long int* rightValera;
#endif 
}; 



const size_t MIN_CAPACITY = 3;

void StackCtor(Stack* data, const int line, const char* file);
void StackDtor(Stack* data);

void StackPush(int value, Stack* data, const int line, const char* file);
void StackPop(Stack* data, const int line, const char* file);

void Re_Calloc(int more_or_less, Stack* data);


void Verify(Stack* data);
void StackDump(Stack* data, const char* func, const int line, const char* file);

void CleanFile();
