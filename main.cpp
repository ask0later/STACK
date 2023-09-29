#include "stack.h"

#define STACK_PUSH(value, data) StackPush(value, data, __LINE__, __FILE__)
#define STACK_POP(data) StackPop(data, __LINE__, __FILE__)

#define STACKCTOR(data) StackCtor(data, __LINE__, __FILE__)
#define STACKDTOR(data) StackDtor(data)



int main() 
{
    CleanFile();

    struct Stack data;
    
    STACKCTOR(&data);

    STACK_PUSH(6, &data);
    STACK_PUSH(51, &data);
    STACK_PUSH(8, &data);
    

    STACK_PUSH(25, &data);
    STACK_PUSH(23, &data);
    STACK_PUSH(2, &data);
    STACK_PUSH(221, &data);

    data.size = 5;

    STACK_POP(&data);
    STACK_POP(&data);
    STACK_PUSH(231, &data);

    STACK_PUSH(456, &data);
    STACK_PUSH(564, &data);
    STACK_PUSH(674, &data);
    STACK_PUSH(100, &data);


    StackDump(&data, __PRETTY_FUNCTION__, __LINE__, __FILE__);
    STACKDTOR(&data);

    return 0;
}