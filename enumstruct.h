enum Error
{
    NO_ERROR = 0,
    ERROR_NULL_DATA = 1,
    ERROR_NEGATIVE_SIZE = 2,
    ERROR_NEGATIVE_CAPACITY = 4,
    ERROR_ARRAY_EXIT = 8,
#ifdef valera
    ERROR_LEFT_VALERA = 16,
    ERROR_RIGHT_VALERA = 32,
#endif
#ifdef haash
    ERROR_HASH_MISSMATCH = 64
#endif
};


struct Stack
{
#ifdef valera
    unsigned long long int* leftValera;
#endif
    int* sequence;
    size_t size, capacity;
#ifdef valera
    unsigned long long int* rightValera;
#endif 
#ifdef haash
    int hash;
    int status = 0;
#endif
}; 
