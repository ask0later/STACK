#include "stack.h"

#define VERIFY(data, err) Verify(data, err, __PRETTY_FUNCTION__, line, file)


void StackCtor(Stack* data, const int line, const char* file)
{
    data->capacity = MIN_CAPACITY;
    data->size = 0;
    VerifyCapacity(data);


#ifdef valera
    char* ptr = (char*) calloc(2 * sizeof(unsigned long long) + (long unsigned) data->capacity * sizeof(elem_t), sizeof(char));
    
    *((unsigned long long*) ptr) = 0xBAADF00D;

    *((unsigned long long*) (ptr + sizeof(unsigned long long) + (long unsigned) data->capacity * sizeof(elem_t))) = 0xBAADF00D;

    data->leftValera = 0xBAADF00D;
    data->rightValera = 0xBAADF00D; 
    
    data->sequence = (elem_t*) (ptr + sizeof(unsigned long long));
#else
    data->sequence = (elem_t*) calloc((long unsigned)data->capacity, sizeof(elem_t));

#endif

#ifdef haash
    data->status_buf = 0;
    data->status_struct = 0;

    data->hash_struct = 0;
    data->hash_struct = HashFunction(&data->leftValera, 2 * sizeof(unsigned long long) + (long unsigned) data->capacity * sizeof(elem_t*));
    data->hash_buf = HashFunction((char*)data->sequence, data->capacity * sizeof(elem_t));
#endif

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

#ifdef haash
    long unsigned int hash_old_struct = data->hash_struct;
    data->hash_struct = 0;
    data->hash_struct = HashFunction(&data->leftValera, 2 * sizeof(unsigned long long) + 2 * sizeof(int) + sizeof(elem_t*));
    if (hash_old_struct != data->hash_struct)
    {
        data->status_struct |= ERROR_HASH_STRUCT;
    }

    long unsigned int hash_old_buf = data->hash_buf;
    
    data->hash_buf = HashFunction((char*)data->sequence, data->capacity * sizeof(elem_t));

    if (hash_old_buf != data->hash_buf)
    {
        data->status_buf |= ERROR_HASH_BUFFER;
    }
#endif

    int err = ErrorRate(data);
    if (err != 0)
    {
        VERIFY(data, err);
    }


    if (data->size == data->capacity)
    {
        Re_Calloc(1, data);
    }

    *(data->sequence + data->size) = value;

    (data->size)++;

#ifdef haash
    data->hash_struct = 0;
    data->hash_struct = HashFunction(&data->leftValera, 2 * sizeof(unsigned long long) + 2 * sizeof(int) + sizeof(elem_t*));
    data->hash_buf = HashFunction((char*)data->sequence, data->capacity * sizeof(elem_t));
#endif    

    err = ErrorRate(data);
    if (err != 0)
    {
        VERIFY(data, err);
    }
}
elem_t StackPop(Stack* data, const int line, const char* file)
{
    NullVerify(data);

#ifdef haash
    long unsigned int hash_old_struct = data->hash_struct;
    data->hash_struct = 0;
    data->hash_struct = HashFunction(&data->leftValera, 2 * sizeof(unsigned long long) + 2 * sizeof(int) + sizeof(elem_t*));
    if (hash_old_struct != data->hash_struct)
    {
        data->status_struct |= ERROR_HASH_STRUCT;
    }

    long unsigned int hash_old_buf = data->hash_buf;
    data->hash_buf = HashFunction((char*)data->sequence, data->capacity * sizeof(elem_t));
    if (hash_old_buf != data->hash_buf)
    {
        data->status_buf |= ERROR_HASH_BUFFER;
    }
#endif    

    int err = ErrorRate(data);
    if (err != 0)
    {
        VERIFY(data, err);
    }



    if (data->size == data->capacity / 4)
    {
        Re_Calloc(0, data);
    }

    if (data->size == 0)
    {
        return 0;
    }
    
    (data->size)--;
    int value = *(data->sequence + data->size);
    *(data->sequence + data->size) = 0;

#ifdef haash
    data->hash_struct = 0;
    data->hash_struct = HashFunction(&data->leftValera, 2 * sizeof(unsigned long long) + 2 * sizeof(int) + sizeof(elem_t*));
    data->hash_buf = HashFunction((char*)data->sequence, data->capacity * sizeof(elem_t));
#endif  

    err = ErrorRate(data);
    if (err != 0)
    {
        VERIFY(data, err);
    }
    return value;
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

    *(unsigned long long*) ptr = 0xBAADF00D;
    *(unsigned long long*) (ptr + sizeof(unsigned long long) + (long unsigned) data->capacity * sizeof(int)) = 0xBAADF00D;
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

