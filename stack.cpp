#include "stack.h"
#include <stdlib.h>
#include <climits>

#include <assert.h>

#define STACK_DUMP(data) StackDump(data, __PRETTY_FUNCTION__, line, file)


void StackCtor(Stack* data, const int line, const char* file)
{
    assert(data != nullptr);

    data->capacity = MIN_CAPACITY;
    data->sequence = (int*) calloc(data->capacity, sizeof(int));
    data->size = 0;
    printf("abcd");
    
    STACK_DUMP(data);
}
 

void StackDtor(Stack* data, const int line, const char* file)
{
    free(data->sequence);
    data->sequence = NULL;
    data->size = INT_MAX;
    data->capacity = INT_MAX;
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
    printf("WTF\n");
    if (more_or_less == 1)
    {
        data->capacity = (data->capacity) * 2;
    }
    else if (more_or_less == 0)
    {
        data->capacity = (data->capacity) / 2;
    }

    printf("%lu\n", data->capacity);
    data->sequence = (int*) realloc(data->sequence, data->capacity);
    printf("WTF\n");
    

    if (more_or_less == 1)
    {
        for(size_t counter = data->capacity / 2; counter < data->capacity; counter++)
        {
            *(data->sequence + counter) = INT_MAX;
        }
    }
        
    
    printf("WTF\n");
}

