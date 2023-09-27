#include "verify.h"

int ErrorRate(Stack* data)
{
    int err = 0;
    if (data == NULL)                           err |= ERROR_NULL_DATA;  
    if (data->capacity < 0)                     err |= NEGATIVE_CAPACITY;
    if (data->size < 0)                         err |= NEGATIVE_SIZE;
    if ((data->capacity) < (data->size))        err |= ERROR_ARRAY_EXIT; 

#ifdef valera
    if (*(data->leftValera) != INT_MAX)         err |= ERROR_LEFT_VALERA;
    if (*(data->rightValera) != INT_MAX)        err |= ERROR_RIGHT_VALERA;
#endif

#ifdef haash
                                                err |= data->status;
#endif

    return err;
} 

void Verify(Stack* data)
{
    int errors = ErrorRate(data);
    int value = 1;
    for(int counter = 0; counter < NUM_ERRORS; counter++)
    {
        if (counter != 0)
            value = value * 2;        
        if (errors & value)
            DumpErrors(value);
    }
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
            exit(1);
        case NEGATIVE_CAPACITY:
            fprintf(fp, "!!!!!!!!!!!!ABORT!!!!!!!!!!!!!!!\n"
                        "       NEGATIVE_CAPACITY\n");
            exit(1);
        case NEGATIVE_SIZE:
            fprintf(fp, "!!!!!!!!!!!!ABORT!!!!!!!!!!!!!!!\n"
                        "       NEGATIVE_SIZE\n");
            exit(1);
        case ERROR_ARRAY_EXIT:
            fprintf(fp, "!!!!!!!!!!!!ABORT!!!!!!!!!!!!!!!\n"
                        "      ERROR_ARRAY_EXIT\n");
            exit(1);
        case ERROR_EXTRA_MEM:
            fprintf(fp, "!!!!!!!!!!!!ABORT!!!!!!!!!!!!!!!\n"
                        "      ERROR_EXTRA_MEM\n");
            exit(1);

#ifdef valera
        case ERROR_LEFT_VALERA:
            fprintf(fp, "!!!!!!!!!!!!ABORT!!!!!!!!!!!!!!!\n"
                        "      ERROR_LEFT_VALERA\n");
            exit(1);
        case ERROR_RIGHT_VALERA:
            fprintf(fp, "!!!!!!!!!!!!ABORT!!!!!!!!!!!!!!!\n"
                        "      ERROR_RIGHT_VALERA\n");
            exit(1);
#endif

#ifdef haash
        case ERROR_HASH_MISSMATCH:
            fprintf(fp, "!!!!!!!!!!!!ABORT!!!!!!!!!!!!!!!\n"
                        "       ERROR_HASH_MISSMATCH\n");
            exit(1);
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

long unsigned int HashFunction(void* ptr)
{
    int counter;
    unsigned long hash = 5381;
    while ((counter = *(char*) ptr))
    {
        (char*) ptr++;
        hash = ((hash << 5) + hash) + counter;
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