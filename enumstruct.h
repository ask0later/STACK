typedef int elem_t;


struct Stack
{
#ifdef valera
    unsigned long long int* leftValera;
#endif
    elem_t* sequence;
    size_t size, capacity;
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
    ERROR_NULL_DATA = 1,
    ERROR_ARRAY_EXIT = 2,
    ERROR_EXTRA_MEM = 4,
#ifdef valera
    ERROR_LEFT_VALERA = 8,
    ERROR_RIGHT_VALERA = 16,
#endif
#ifdef haash
    ERROR_HASH_MISSMATCH = 32
#endif
};


