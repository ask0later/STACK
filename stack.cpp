#include "stack.h"
#include <stdlib.h>
#include <climits>

#include <assert.h>

#define STACK_DUMP(data) StackDump(data, __PRETTY_FUNCTION__, line, file)


void StackCtor(Stack* data, const int line, const char* file)
{
    data->capacity = MIN_CAPACITY;
    data->size = 0;
#ifdef valera
    char* ptr = (char*) calloc(2 * sizeof(unsigned long long) + data->capacity * sizeof(int), sizeof(char));

    data->leftValera = (unsigned long long*) ptr;
    data->rightValera = (unsigned long long*) (ptr + sizeof(unsigned long long) + data->capacity * sizeof(int));
    
    *(data->leftValera) = INT_MAX;
    *(data->rightValera) = INT_MAX; 
    
    data->sequence = (int*) (ptr + sizeof(unsigned long long));
    printf("Ouh shit...");
#else
    data->sequence = (int*) calloc(data->capacity, sizeof(int));
#endif
    STACK_DUMP(data);
}
 
void StackDtor(Stack* data)
{
    data->size = INT_MAX;
    data->capacity = INT_MAX;
#ifdef valera
    int* ptr = data->sequence - sizeof(unsigned long long) / sizeof(int);
    free(ptr);
#else
    free(data->sequence);
#endif
    data->sequence = NULL;
}

void StackPush(int value, Stack* data, const int line, const char* file)
{
    if (data->size == data->capacity)
    {
        Re_Calloc(1, data);
        printf("%lu\n", data->capacity);
    }

    *(data->sequence + data->size) = value;

    (data->size)++;

    STACK_DUMP(data);
    Verify(data);
}
void StackPop(Stack* data, const int line, const char* file)
{
    if (data->size == data->capacity / 4)
    {
        Re_Calloc(0, data);
    }
    
    (data->size)--;
    
    *(data->sequence + data->size) = 0;
    
    STACK_DUMP(data);
    Verify(data);
}

void Re_Calloc(int more_or_less, Stack* data)
{
    if (more_or_less == 1)
    {
        data->capacity = (data->capacity) * 2;
    }
    else if (more_or_less == 0)
    {
        data->capacity = (data->capacity) / 2;
    }

#ifdef valera
    char* ptr = (char*) (data->sequence - sizeof(unsigned long long) / sizeof(int));
    ptr = (char*) realloc(ptr, (2 * sizeof(unsigned long long) + data->capacity * sizeof(int)) * sizeof(char));
    
    data->sequence = (int*) (ptr + (char) sizeof(unsigned long long));

    data->rightValera = (unsigned long long*) (ptr + sizeof(unsigned long long) + data->capacity * sizeof(int));
    *(data->rightValera) = INT_MAX;
#else
    data->sequence = (int*) realloc(data->sequence, data->capacity * sizeof(int));
#endif

    if (more_or_less == 1)
    {
        for(size_t counter = data->capacity / 2; counter < data->capacity; counter++)
        {
            *(data->sequence + counter) = INT_MAX;
        }
    }
}

