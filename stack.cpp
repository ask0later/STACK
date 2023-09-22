#include "stack.h"
#include <stdlib.h>
#include <climits>

#include <assert.h>

void StackCtor(Stack* data)
{
    assert(data != nullptr);

    data->capacity = MIN_CAPACITY;
    data->sequence = (int*) calloc( data->capacity, sizeof(int));
    data->size = 0;
    printf("abcd");
    
    StackDump(data);
}
 

void StackDtor(Stack* data)
{
    free(data->sequence);
    data->sequence = NULL;
    data->size = INT_MAX;
    data->capacity = INT_MAX;
    StackDump(data);
}

void StackPush(int value, Stack* data)
{
    assert(data != nullptr);
    // if (data->size == data->capacity)
    // {
    //     //ReCalloc(1, data);
    // }

    // *(data->sequence + data->size) = value;

    // (data->size)++;

    // StackDump(data);
    // Verify(data);
}
void StackPop(Stack* data)
{
    if (data->size == data->capacity / 4)
    {
        //ReCalloc(0, data);
    }
    
    (data->size)--;
    
    *(data->sequence + data->size) = 0;
    
    StackDump(data);
    Verify(data);
}

void ReCalloc(int more_or_less, Stack* data)
{
    if (more_or_less == 1)
    {
        data->capacity = data->capacity * 2;
    }
    else if (more_or_less == 0)
    {
        data->capacity = data->capacity / 2;
    }

    
    data->sequence = (int*) realloc(data->sequence, (size_t)(data->capacity));

    if (more_or_less == 1)
        for(int counter = data->capacity / 2; counter < data->capacity; counter++)
            *(data->sequence + counter) = 0;

    if (more_or_less == 1)
        for(int counter = data->capacity; counter < data->capacity * 2; counter++)
            *(data->sequence + counter) = 0;
    
    Verify(data);
}

