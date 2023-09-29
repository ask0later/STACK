#include "verify.h"

#define STACK_DUMP(data) StackDump(data, func, line, file)

int ErrorRate(Stack* data)
{
    int err = 0;
    if (data == NULL)                           err |= ERROR_NULL_DATA;  
    if (data->capacity < 0)                     err |= NEGATIVE_CAPACITY;
    if (data->size < 0)                         err |= NEGATIVE_SIZE;
    if ((data->capacity) < (data->size))        err |= ERROR_ARRAY_EXIT; 

#ifdef valera
    if ((data->leftValera) != 0xBAADF00D)       err |= ERROR_LEFT_VALERA;
    if ((data->rightValera) != 0xBAADF00D)      err |= ERROR_RIGHT_VALERA;

    char* ptr = (char*) data->sequence;

    //if (((unsigned long long)*(data->sequence - sizeof(unsigned long long) / sizeof(elem_t))) != 0xBAADF00D)
    if (*((unsigned long long*) (ptr - sizeof(unsigned long long))) != 0xBAADF00D)
                                                err |= ERROR_LEFT_BUF;
    //if (((unsigned long long) *(data->sequence + data->capacity)) != 0xBAADF00D)
    if (*((unsigned long long*) (ptr + data->capacity * sizeof(elem_t))) != 0xBAADF00D)
                                                err |= ERROR_RIGHT_BUF;                                          
#endif

#ifdef haash
                                                err |= data->status_buf;
                                                err |= data->status_struct;
#endif
    return err;
} 

void Verify(Stack* data, int errors, const char* func, const int line, const char* file)
{
    if (errors == 0)
        return;
    int value = 1;
    STACK_DUMP(data);
    for(int counter = 0; counter < NUM_ERRORS; counter++)
    {
        if (counter != 0)
            value = value * 2;        
        if (errors & value)
            DumpErrors(value);
    }
    exit(1);
}

void StackDump(Stack* data, const char* func, const int line, const char* file)
{
    FILE* fp = fopen("logfile.txt", "a");
    
    fprintf(fp, "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"
                "Stack[%p] called %s(%d) from %s\n"
                "{\n"
                "   size = %d;\n"
                "   capacity = %d;\n"
                "   data[%p]\n"
                "   {\n", data->sequence, func, line, file, data->size, data->capacity, data->sequence);

    if (data->status_struct == 0)
    {
        
        for (int counter = 0; counter < data->size; counter++)
        {
            fprintf(fp,"       *data[%2d] = %d\n", counter, *(data->sequence + counter)); 
        }
        if (data->capacity > data->size)
        {
            for (int counter = data->size; counter < data->capacity; counter++)
            {
                if (*(data->sequence + counter) == 0)
                {
                    fprintf(fp, "       *data[%2d] = %d\n", counter, *(data->sequence + counter)); 
                }
                else
                {
                    fprintf(fp, "       *data[%d] = %d (POISON)\n", counter, *(data->sequence + counter));
                }
            }
        }
    }
    

    fprintf(fp,"    }\n"
               "}\n");
    
    fclose(fp);
}

void DumpErrors(int error_num)
{
    FILE* fp = fopen("logfile.txt", "a");
    switch(error_num)
    {
        case ERROR_NULL_DATA:
            fprintf(fp, "!!!!!!!!!!!!ABORT!!!!!!!!!!!!!!!\n"
                        "       ERROR_NULL_DATA\n");
            break;
        case NEGATIVE_CAPACITY:
            fprintf(fp, "!!!!!!!!!!!!ABORT!!!!!!!!!!!!!!!\n"
                        "       NEGATIVE_CAPACITY\n");
            break;
        case NEGATIVE_SIZE:
            fprintf(fp, "!!!!!!!!!!!!ABORT!!!!!!!!!!!!!!!\n"
                        "       NEGATIVE_SIZE\n");
            break;

        case ERROR_ARRAY_EXIT:
            fprintf(fp, "!!!!!!!!!!!!ABORT!!!!!!!!!!!!!!!\n"
                        "      ERROR_ARRAY_EXIT\n");
            break;

        case ERROR_EXTRA_MEM:
            fprintf(fp, "!!!!!!!!!!!!ABORT!!!!!!!!!!!!!!!\n"
                        "      ERROR_EXTRA_MEM\n");
            break;

#ifdef valera
        case ERROR_LEFT_VALERA:
            fprintf(fp, "!!!!!!!!!!!!ABORT!!!!!!!!!!!!!!!\n"
                        "      ERROR_LEFT_VALERA\n");
            break;

        case ERROR_RIGHT_VALERA:
            fprintf(fp, "!!!!!!!!!!!!ABORT!!!!!!!!!!!!!!!\n"
                        "      ERROR_RIGHT_VALERA\n");
            break;

        case ERROR_LEFT_BUF:
            fprintf(fp, "!!!!!!!!!!!!ABORT!!!!!!!!!!!!!!!\n"
                        "      ERROR_LEFT_BUF\n");
            break;

        case ERROR_RIGHT_BUF:
            fprintf(fp, "!!!!!!!!!!!!ABORT!!!!!!!!!!!!!!!\n"
                        "      ERROR_RIGHT_BUF\n");
#endif

#ifdef haash
        case ERROR_HASH_BUFFER:
            fprintf(fp, "!!!!!!!!!!!!ABORT!!!!!!!!!!!!!!!\n"
                        "       ERROR_HASH_BUFFER\n");
            break;

        case ERROR_HASH_STRUCT:
            fprintf(fp, "!!!!!!!!!!!!ABORT!!!!!!!!!!!!!!!\n"
                        "       ERROR_HASH_STRUCT\n");
            break;

#endif

        default:
            fprintf(fp, "error not founded");
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
    char *data = (char*) ptr;
	long unsigned int hash = 5381;
    for(size_t i = 0; i < size; i++)
    {
		hash = ((hash << 5) + hash) + (long unsigned int) data[i];
    }

	return hash;
}
void VerifyCapacity(Stack* data)
{
    while (data->capacity % 2 != 0)
    {
        data->capacity++;
    }
}
void NullVerify(Stack* data)
{
    if (data == NULL)
    {
        printf("!!ABORT!!\npointer is NULL\n:((((");
        exit(1);
    }
}