#include <stdlib.h>
#include <climits>
#include <assert.h>
#include <stdio.h>

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
#ifdef hach
    int hash;
#endif
}; 

enum Error
{
    NO_ERROR = 0,
    ERROR_NULL_DATA = 1,
    ERROR_NEGATIVE_SIZE = 2,
    ERROR_NEGATIVE_CAPACITY = 4,
    ERROR_ARRAY_EXIT = 8,
#ifdef valera
    ERROR_LEFT_VALERA = 16,
    ERROR_RIGHT_VALERA = 32
#endif
};


int StackVerify(Stack* data);

void DumpErrors(int error_num);
void Verify(Stack* data);
int ErrorRate(Stack* data);

void CleanFile();

void StackDump(Stack* data, const char* func, const int line, const char* file);

int HashFunction(Stack* data);