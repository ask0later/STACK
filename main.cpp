#include "stack.h"

#define STACK_PUSH(value, data) StackPush(value, data, __LINE__, __FILE__)
#define STACK_POP(data) StackPop(data, __LINE__, __FILE__)




int main() 
{
    CleanFile();

    struct Stack data;
    
    StackCtor(&data);

    //for (int i = 0; i < 1000; i++) STACK_PUSH(6, &data);

    STACK_PUSH(6, &data);
    STACK_PUSH(51, &data);
    STACK_PUSH(8, &data);
    

    STACK_PUSH(25, &data);
    STACK_PUSH(23, &data);
    STACK_PUSH(2, &data);
    STACK_PUSH(221, &data);

    //data.capacity = 10000;

    STACK_POP(&data);
    STACK_POP(&data);

    STACK_PUSH(231, &data);


    STACK_PUSH(456, &data);
    STACK_PUSH(564, &data);
    STACK_PUSH(674, &data);
    STACK_PUSH(100, &data);


    StackDump(&data, __PRETTY_FUNCTION__, __LINE__, __FILE__);
    StackDtor(&data);

    return 0;
}