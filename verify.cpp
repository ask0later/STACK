#include "verify.h"
#include <climits>

int ErrorRate(Stack* data)
{
    int err = 0;
    if (data == NULL)                        err |= ERROR_NULL_DATA;  
    if (data->size < 0)                      err |= ERROR_NEGATIVE_SIZE; 
    if (data->capacity < 0)                  err |= ERROR_NEGATIVE_CAPACITY;
    if ((data->capacity) < (data->size))     err |= ERROR_ARRAY_EXIT; 
#ifdef valera
    if (*(data->leftValera) != INT_MAX)      err |= ERROR_LEFT_VALERA;
    if (*(data->rightValera) != INT_MAX)     err |= ERROR_RIGHT_VALERA;
#endif
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

void StackDump(Stack* data, const char* func, const int line, const char* file)
{
    FILE* fp = fopen("logfile.txt", "a");

    fprintf(fp, "____________________________________________________________________________\n"
                "Stack[%p] called %s(%d) from %s\n"
                "{\n"
                "   size = %d;\n"
                "   capacity = %d;\n"
                "   data[%p]\n"                                        //
                "       {\n", data->sequence, func, line, file, data->size, data->capacity, data->sequence);

    
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
    FILE* fp = fopen("logfile.txt", "a");

    switch(error_num)
    {
        case ERROR_NULL_DATA:
            fprintf(fp, "ERROR_NULL_DATA");
            abort();
        case ERROR_NEGATIVE_SIZE:
            fprintf(fp, "ERROR_NEGATIVE_SIZE");
            abort();
        case ERROR_NEGATIVE_CAPACITY:
            fprintf(fp, "ERROR_NEGATIVE_CAPACITY");
            abort();
        case ERROR_ARRAY_EXIT:
            fprintf(fp, "ERROR_ARRAY_EXIT");
            abort();
// #ifdef valera
//         case ERROR_LEFT_VALERA:
//             fprintf(fp, "ERROR_LEFT_VALERA");
//         case ERROR_RIGHT_VALERA:
//             fprintf(fp, "ERROR_RIGHT_VALERA");
// #endif
        default:
            fprintf(fp, "ERROR NOT FOUNDED");
            break;
    }
    fclose(fp);
}


void CleanFile()
{
    FILE* fp = fopen("logfile.txt", "w");
    fclose(fp);
}