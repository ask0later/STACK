#include "verify.h"

int ErrorRate(Stack* stk)
{
    int err = 0;

    if (stk == NULL)                                err |= ERROR_NULL_STK;
    else
    {
        if (stk->capacity < 0)                      err |= NEGATIVE_CAPACITY;
        if (stk->size < 0)                          err |= NEGATIVE_SIZE;
        if ((stk->capacity) < (stk->size))          err |= ERROR_ARRAY_EXIT; 
        if (stk->capacity > 255)                    err |= ERROR_MEMORY;

        #ifdef HASH_VERIFICATION

        long unsigned int old_hash_struct = stk->hash_struct, old_hash_buf = stk->hash_buf;
        stk->hash_struct = 0; stk->hash_buf = 0; 

        long unsigned int new_hash_struct = HashFunction(stk, sizeof(*stk));
        stk->hash_struct = old_hash_struct;
        
        stk->hash_buf = old_hash_buf;

        if (old_hash_struct != new_hash_struct) 
        {                                           err |= ERROR_HASH_STRUCT;}
        else
        {
            if (stk->hash_buf != HashFunction(stk->sequence, (long unsigned int) stk->capacity * sizeof(elem_t)))
            {                                       err |= ERROR_HASH_BUFFER;}
        }
        #endif

#ifdef VALERA_VERIFICATION
        if (stk->sequence == nullptr)               err |= ERROR_ALLOC;
        else
        {
            if ((stk->leftValera) != 0xBAADF00D)    err |= ERROR_LEFT_VALERA; 
            if ((stk->rightValera) != 0xBAADF00D)   err |= ERROR_RIGHT_VALERA;
        
            if (*((valera_t*) ((char*) stk->sequence - sizeof(valera_t))) != 0xBAADF00D)
                                                    err |= ERROR_LEFT_BUF;
        
#ifdef HASH_VERIFICATION    
            if (!(err & ERROR_HASH_STRUCT))
            {
                if (*((valera_t*) ((char*) stk->sequence + (long unsigned)stk->capacity * sizeof(elem_t))) != 0xBAADF00D)
                                                    err |= ERROR_RIGHT_BUF;     
            }
        }

#endif                                     
#endif
    }  
    
    return err;
} 

void Verify(Stack* stk, int errors, const char* func, const int line, const char* file)
{
    if (errors == 0)
        return;
    int error_bit = 1;
    if (!((ERROR_NULL_STK & errors) || (ERROR_ALLOC & errors)))
    {
        STACK_DUMP(stk);
    }
    for(size_t counter = 0; counter < NUM_ERRORS; counter++)
    {
        if (counter != 0)
            error_bit <<= 1;  
        //      
        if (errors & error_bit)
            DumpErrors(error_bit);
    }
}

void StackDump(Stack* stk, int errors, const char* func, const int line, const char* file)
{
    FILE* fp = fopen("logfile.txt", "a");
    
    fprintf(fp, "______________________________________________________________\n"
                "Stack[%p] called %s(%d) from %s\n"
                "{\n"
                "   size = %d;\n"
                "   capacity = %d;\n"
                "   stk[%p]\n"
                "   {\n", stk->sequence, func, line, file, stk->size, stk->capacity, stk->sequence);
#ifdef HASH_VERIFICATION
    if (!(errors & ERROR_HASH_STRUCT))
    { 
        PrintSequence(stk, fp);
    }
#else
    PrintSequence(stk, fp);
#endif
    
    fprintf(fp,"   }\n"
               "}\n");
    
    fclose(fp);
}

void DumpErrors(int error_num)
{
    FILE* fp = fopen("logfile.txt", "a");
    switch(error_num)
    {
        case ERROR_NULL_STK:
            fprintf(fp, "ABORT:\n"
                        "ERROR_NULL_stk or ERROR_ALLOC\n\n");
            break;
        case NEGATIVE_CAPACITY:
            fprintf(fp, "ABORT\n"
                        "NEGATIVE_CAPACITY\n\n");
            break;
        case NEGATIVE_SIZE:
            fprintf(fp, "ABORT\n"
                        "NEGATIVE_SIZE\n\n");
            break;

        case ERROR_ARRAY_EXIT:
            fprintf(fp, "ABORT\n"
                        "ERROR_ARRAY_EXIT\n\n");
            break;

        case ERROR_EXTRA_MEM:
            fprintf(fp, "ABORT\n"
                        "ERROR_EXTRA_MEM\n\n");
            break;
        case ERROR_MEMORY:
            fprintf(fp, "ABORT\n"
                        "ERROR_MEMORY\n\n");
            break;
        case ERROR_ALLOC:
            fprintf(fp, "ABORT\n"
                        "ERROR)ALLOC\n\n");
            break;

#ifdef VALERA_VERIFICATION
        case ERROR_LEFT_VALERA:
            fprintf(fp, "ABORT\n"
                        "ERROR_LEFT_VALERA\n\n");
            break;

        case ERROR_RIGHT_VALERA:
            fprintf(fp, "ABORT\n"
                        "ERROR_RIGHT_VALERA\n\n");
            break;

        case ERROR_LEFT_BUF:
            fprintf(fp, "ABORT\n"
                        "ERROR_LEFT_BUF\n\n");
            break;

        case ERROR_RIGHT_BUF:
            fprintf(fp, "ABORT\n"
                        "ERROR_RIGHT_BUF\n\n");
            break;
#endif

#ifdef HASH_VERIFICATION
        case ERROR_HASH_BUFFER:
            fprintf(fp, "ABORT\n"
                        "ERROR_HASH_BUFFER\n\n");
            break;

        case ERROR_HASH_STRUCT:
            fprintf(fp, "ABORT\n"
                        "ERROR_HASH_STRUCT\n\n");
            break;

#endif

        default:
            fprintf(fp, "error not founded\n");
            break;
    }
    fclose(fp);
}


void CleanFile()
{
    FILE* fp = fopen("logfile.txt", "w");
    fclose(fp);
}

long unsigned int HashFunction(void* ptr, size_t size)
{
    char *stk = (char*) ptr;
	long unsigned int hash = 5381;
    for(size_t i = 0; i < size; i++)
    {
		hash = ((hash << 5) + hash) + (long unsigned int) stk[i];
    }

	return hash;
}
void VerifyCapacity(Stack* stk)
{
    while ((unsigned long) stk->capacity % (sizeof(valera_t) / sizeof(elem_t)) != 0)
    { 
        stk->capacity++;
    }
}

void PrintSequence(Stack* stk, FILE* fp)
{
    for (int counter = 0; counter < stk->size; counter++)
        {
            fprintf(fp,"       *stk[%2d] = %d\n", counter, *(stk->sequence + counter)); 
        }
        
    for (int counter = stk->size; counter < stk->capacity; counter++)
    {
        if (*(stk->sequence + counter) == 0)
        {
            fprintf(fp, "       *stk[%2d] = %d\n", counter, *(stk->sequence + counter)); 
        }
        else
        {
            fprintf(fp, "       *stk[%d] = %d (POISON)\n", counter, *(stk->sequence + counter));
        }
    }    
}