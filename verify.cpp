#include "verify.h"

int ErrorRate(Stack* data)
{
    int err = 0;
    if (data == NULL)                       err |= ERROR_NULL_DATA;  
    if (data->size < 0)                     err |= ERROR_NEGATIVE_SIZE; 
    if (data->capacity < 0)                 err |= ERROR_NEGATIVE_CAPACITY; //1011010 err = 2 + 8 + 16 + 64 = 90
    if ((data->capacity) < (data->size))    err |= ERROR_ARRAY_EXIT; // выход за массив!
    return err;
}

void Verify(Stack* data)
{
    int errors = ErrorRate(data);
    int value = 1;
    for(int counter = 0; counter < 4; counter++)
    {
        if (counter != 0)
            value = value * 2;        
        if (errors & value)
            DumpErrors(value);
    }
}

void StackDump(Stack* data) //
{
    FILE* fp = fopen("logfile.txt", "w");

    fprintf(fp, "********************************************************************\n"
                "Stack[%p] called %s(%d) from %s\n"
                "{\n"
                "   size = %d;\n"
                "   capacity = %d;\n"
                "   data[%p]\n"                                        //
                "       {\n", data->sequence, __PRETTY_FUNCTION__, __LINE__, __FILE__, data->size, data->capacity, data->sequence);

    
    for (int counter = 0; counter < data->size; counter++)
    {
        fprintf(fp,"       *data[%d] = %d\n", counter, *(data->sequence + counter)); 
    }

    if (data->capacity > data->size)
    {
        for (int counter = data->size; counter < data->capacity; counter++)
        {
            if (*(data->sequence + counter) == 0)
            {
                fprintf(fp, "       *data[%d] = %d\n", counter, *(data->sequence + counter)); 

            }
            else
            {
                fprintf(fp, "       *data[%d] = %d NAN (POIZON)\n", counter, *(data->sequence + counter));
            }
        }
    }

    fprintf(fp,"    }\n"
               "}\n");
    
    fclose(fp);
}

void DumpErrors(int error_num)
{
    FILE* fp = fopen("logfile.txt", "w");

    switch(error_num)
    {
        case ERROR_NULL_DATA:
            fprintf(fp, "ERROR_NULL_DATA");
            exit(1);
        case ERROR_NEGATIVE_SIZE:
            fprintf(fp, "ERROR_NEGATIVE_SIZE");
            exit(1);
        case ERROR_NEGATIVE_CAPACITY:
            fprintf(fp, "ERROR_NEGATIVE_CAPACITY");
            exit(1);
        case ERROR_ARRAY_EXIT:
            fprintf(fp, "ERROR_ARRAY_EXIT");
            exit(1);
        default:
            fprintf(fp, "ERROR NOT FOUNDED");
            break;
    }
    fclose(fp);
}
