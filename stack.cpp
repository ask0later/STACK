#include "stack.h"


#define STACK_DUMP(data) StackDump(data, __PRETTY_FUNCTION__, line, file)


void StackCtor(Stack* data, const int line, const char* file)
{
    data->capacity = MIN_CAPACITY;
    data->size = 0;
    VerifyCapacity(data);

#ifdef valera
    char* ptr = (char*) calloc(2 * sizeof(unsigned long long) + (long unsigned) data->capacity * sizeof(elem_t), sizeof(char));
    
    data->leftValera = (unsigned long long*) ptr;
    data->rightValera = (unsigned long long*) (ptr + sizeof(unsigned long long) + (long unsigned) data->capacity * sizeof(elem_t));
    
    *(data->leftValera) = INT_MAX;
    *(data->rightValera) = INT_MAX; 
    
    data->sequence = (elem_t*) (ptr + sizeof(unsigned long long));
#else
    data->sequence = (elem_t*) calloc((long unsigned)data->capacity, sizeof(elem_t));
#endif

#ifdef haash
    data->hash = 0;
    data->hash = HashFunction((char*)data->sequence) + HashFunction((char*) &(data->leftValera));
#endif

    STACK_DUMP(data);
}
 
void StackDtor(Stack* data)
{
    data->size = INT_MAX;
    data->capacity = INT_MAX;

#ifdef valera
    int* ptr = data->sequence - sizeof(unsigned long long) / sizeof(elem_t);
    free(ptr);
#else
    free(data->sequence);
#endif
}

void StackPush(int value, Stack* data, const int line, const char* file)
{
    NullVerify(data);
    Verify(data);
#ifdef haash
    long unsigned int hash_old = data->hash;
    data->hash = 0;
    data->hash = HashFunction((char*)data->sequence) + HashFunction((char*) &(data->leftValera));
    if (hash_old != data->hash)
    {
        data->status |= ERROR_HASH_MISSMATCH;
    }
#endif

    if (data->size == data->capacity)
    {
        Re_Calloc(1, data);
    }

    *(data->sequence + data->size) = value;

    (data->size)++;

#ifdef haash
    data->hash = 0;
    data->hash = HashFunction((char*)data->sequence) + HashFunction((char*) &(data->leftValera));
#endif    

    STACK_DUMP(data);
    Verify(data); 
    printf("%lu\n", data->hash);
}
void StackPop(Stack* data, const int line, const char* file)
{
    NullVerify(data);
    Verify(data);
#ifdef haash
    long unsigned int hash_old = data->hash;
    data->hash = 0;
    data->hash = HashFunction(data->sequence) + HashFunction(&(data->leftValera));
    if (hash_old != data->hash)
    {
        data->status |= ERROR_HASH_MISSMATCH;
    }
#endif

    if (data->size == data->capacity / 4)
    {
        Re_Calloc(0, data);
    }
    
    (data->size)--;
    *(data->sequence + data->size) = 0;

#ifdef haash
    data->hash = 0;
    data->hash = HashFunction(data->sequence) + HashFunction(&(data->leftValera));
    //HashFunction(data->sequence, sizeof(data->sequence)) + HashFunction(&(data->leftValera), sizeof(data)
#endif  
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
    ptr = (char*) realloc(ptr, (2 * sizeof(unsigned long long) + (long unsigned) data->capacity * sizeof(elem_t)) * sizeof(char));
    
    data->sequence = (int*) (ptr + sizeof(unsigned long long));


    data->leftValera = (unsigned long long*) ptr;
    data->rightValera = (unsigned long long*) (ptr + sizeof(unsigned long long) + (long unsigned) data->capacity * sizeof(int));
    
    *(data->leftValera) = INT_MAX;
    *(data->rightValera) = INT_MAX;
#else
    data->sequence = (int*) realloc(data->sequence, data->capacity * sizeof(int));
#endif

    if (more_or_less == 1)
    {
        for(int counter = data->capacity / 2; counter < data->capacity; counter++)
        {
            *(data->sequence + counter) = INT_MAX;
        }
    }
}

