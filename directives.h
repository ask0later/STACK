#ifndef DIRECTIVES_H
#define DIRECTIVES_H

#include <stdio.h>
#include <stdlib.h>

//typedef int elem_t;

struct Stack
{
    int* sequence;
    size_t size, capacity;
}; 

enum Error
{
    NO_ERROR = 0,
    ERROR_NULL_DATA = 1, // *stk == NULL
    ERROR_NEGATIVE_SIZE = 2, // data == null
    ERROR_NEGATIVE_CAPACITY = 4,
    ERROR_ARRAY_EXIT = 8
};

#endif

