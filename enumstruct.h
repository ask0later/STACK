typedef int elem_t;


struct Stack
{
#ifdef valera
    unsigned long long int leftValera;
#endif
    elem_t* sequence;
    int size;
    int capacity;
#ifdef valera
    unsigned long long int rightValera;
#endif 
#ifdef haash
    long unsigned int hash_buf;
    long unsigned int hash_struct;

    int status_buf;
    int status_struct;
#endif
}; 

enum Error
{
    NO_ERROR = 0,
    NEGATIVE_CAPACITY = 1,
    NEGATIVE_SIZE = 2,
    ERROR_NULL_DATA = 4,
    ERROR_ARRAY_EXIT = 8,
    ERROR_EXTRA_MEM = 16,
    ERROR_MEMORY = 32,
#ifdef valera
    ERROR_LEFT_VALERA = 64,
    ERROR_RIGHT_VALERA = 128,
    ERROR_LEFT_BUF = 256,
    ERROR_RIGHT_BUF = 512,
#endif
#ifdef haash
    ERROR_HASH_STRUCT = 1024,
    ERROR_HASH_BUFFER = 2048
#endif
};


