#include "stack.h"

void StackCtor(Stack* stk)
{
    stk->capacity = MIN_CAPACITY;
    stk->size = 0;

    VerifyCapacity(stk);

#ifdef VALERA_VERIFICATION
    char* ptr = (char*) calloc(2 * sizeof(unsigned long long) + (long unsigned) stk->capacity * sizeof(elem_t), sizeof(char));
    
    *((unsigned long long*) ptr) = 0xBAADF00D;

    *((unsigned long long*) (ptr + sizeof(unsigned long long) + (long unsigned) stk->capacity * sizeof(elem_t))) = 0xBAADF00D;

    stk->leftValera = 0xBAADF00D;
    stk->rightValera = 0xBAADF00D; 
    
    stk->sequence = (elem_t*) (ptr + sizeof(unsigned long long));
#else
    stk->sequence = (elem_t*) calloc((long unsigned)stk->capacity, sizeof(elem_t));
#endif

#ifdef HASH_VERIFICATION
    StackRehash(stk);
#endif

}
 
void StackDtor(Stack* stk)
{
    stk->size = INT_MAX;
    stk->capacity = INT_MAX;

#ifdef VALERA_VERIFICATION
    elem_t* ptr = stk->sequence - sizeof(unsigned long long) / sizeof(elem_t);
    free(ptr);
#else
    free(stk->sequence);
#endif
}

void StackPush(int value, Stack* stk, const int line, const char* file)
{
    int errors = ErrorRate(stk);
    if (errors == 0)
    {
        if (stk->size == stk->capacity)
        {
            Re_Calloc(1, stk);
        }

        *(stk->sequence + stk->size) = value;

        (stk->size)++;

    #ifdef HASH_VERIFICATION
        StackRehash(stk);
    #endif
    }
    VERIFY(stk, errors);
}

elem_t StackPop(Stack* stk, const int line, const char* file)
{
    int errors = ErrorRate(stk);
    //printf("%d\n", errors);
    if (errors == 0)
    {
        if (stk->size == stk->capacity / 4)
        {
            Re_Calloc(0, stk);
        }

        if (stk->size == 0)
        {
            return 0;
        }   

        (stk->size)--;
        int value = *(stk->sequence + stk->size);
        *(stk->sequence + stk->size) = 0;

    #ifdef HASH_VERIFICATION
        StackRehash(stk);
    #endif

        return value;
    }
    VERIFY(stk, errors);
    return NULL;
}

void Re_Calloc(bool more_or_less, Stack* stk)
{
    if (more_or_less == 1)
    {
        stk->capacity = (stk->capacity) * 2;
    }
    else if (more_or_less == 0)
    {
        stk->capacity = (stk->capacity) / 2;
    }

#ifdef VALERA_VERIFICATION
    char* ptr = (char*) (stk->sequence - sizeof(unsigned long long) / sizeof(int));
    ptr = (char*) realloc(ptr, (2 * sizeof(unsigned long long) + (long unsigned) stk->capacity * sizeof(elem_t)) * sizeof(char));
    
    stk->sequence = (elem_t*) (ptr + sizeof(unsigned long long));

    *(unsigned long long*) ptr = 0xBAADF00D;
    *(unsigned long long*) (ptr + sizeof(unsigned long long) + (long unsigned) stk->capacity * sizeof(int)) = 0xBAADF00D;
#else
    stk->sequence = (elem_t*) realloc(stk->sequence, stk->capacity * sizeof(int));
#endif

    if (more_or_less == 1)
    {
        for(int counter = stk->capacity / 2; counter < stk->capacity; counter++)
        {
            *(stk->sequence + counter) = INT_MAX;
        }
    }
}

void StackRehash(Stack* stk)
{
    stk->hash_struct = 0;
    stk->hash_buf = 0;
    stk->hash_struct = HashFunction(stk, sizeof(*stk));
    stk->hash_buf = HashFunction(stk->sequence, sizeof(elem_t) * stk->capacity);
}