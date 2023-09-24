#include <stdio.h>
#include <stdlib.h>

//#define valera

//typedef int elem_t;

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

enum Error
{
    NO_ERROR = 0,
    ERROR_NULL_DATA = 1, // *stk == NULL
    ERROR_NEGATIVE_SIZE = 2, // data == null
    ERROR_NEGATIVE_CAPACITY = 4,
    ERROR_ARRAY_EXIT = 8,
#ifdef valera
    ERROR_LEFT_VALERA = 16,
    ERROR_RIGHT_VALERA = 32
#endif
};

