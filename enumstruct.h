typedef int elem_t;


struct Stack
{
#ifdef valera
    unsigned long long int* leftValera;
#endif
    elem_t* sequence;
    int size, capacity;
#ifdef valera
    unsigned long long int* rightValera;
#endif 
#ifdef haash
    long unsigned int hash;
    int status;
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
#ifdef valera
    ERROR_LEFT_VALERA = 32,
    ERROR_RIGHT_VALERA = 64,
#endif
#ifdef haash
    ERROR_HASH_MISSMATCH = 128
#endif
};


