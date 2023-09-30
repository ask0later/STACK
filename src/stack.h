#include <stdlib.h>
#include <climits>
#include <stdio.h>
#include <assert.h>

#define VERIFY(stk, err) Verify(stk, err, __PRETTY_FUNCTION__, line, file)

#define STACK_PUSH(value, stk) StackPush(value, stk, __LINE__, __FILE__)
#define STACK_POP(stk) StackPop(stk, __LINE__, __FILE__)

typedef int elem_t;

#ifndef STRUCT

#define STRUCT
struct Stack
{
#ifdef VALERA_VERIFICATION
    unsigned long long int leftValera;
#endif
    elem_t* sequence;
    int size;
    int capacity;

#ifdef HASH_VERIFICATION
    long unsigned int hash_buf;
    long unsigned int hash_struct;
#endif

#ifdef VALERA_VERIFICATION
    unsigned long long int rightValera;
#endif 
}; 
#endif

enum Error
{
    NO_ERROR = 0,            
    NEGATIVE_CAPACITY = 1,      
    NEGATIVE_SIZE = 2,
    ERROR_NULL_STK = 4,
    ERROR_ARRAY_EXIT = 8,
    ERROR_EXTRA_MEM = 16,
    ERROR_MEMORY = 32,
#ifdef VALERA_VERIFICATION
    ERROR_LEFT_VALERA = 64,
    ERROR_RIGHT_VALERA = 128,
    ERROR_LEFT_BUF = 256,
    ERROR_RIGHT_BUF = 512,
#endif
#ifdef HASH_VERIFICATION
    ERROR_HASH_STRUCT = 1024,  
    ERROR_HASH_BUFFER = 2048   
#endif
};

const int MIN_CAPACITY = 3;

void StackCtor(Stack* stk);
void StackDtor(Stack* stk);

void StackPush(elem_t value, Stack* stk, const int line, const char* file);
elem_t StackPop(Stack* stk, const int line, const char* file);

void Re_Calloc(bool more_or_less, Stack* stk);

void VerifyCapacity(Stack* stk);
long unsigned int HashFunction(void* ptr, size_t size);
void StackRehash(Stack* stk);

void Verify(Stack* stk, int errors, const char* func, const int line, const char* file);
int ErrorRate(Stack* stk);

void CleanFile();