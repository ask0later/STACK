#include "stack.h"

int main() 
{
    CleanFile();

    struct Stack stk;
    
    StackCtor(&stk);

    // SetCheckErrors(stk, false);

    STACK_PUSH(6, &stk);
    STACK_PUSH(51, &stk);
    STACK_PUSH(8, &stk);
    stk.size= 50;

    STACK_PUSH(25, &stk);
    


    STACK_PUSH(23, &stk);
    
    STACK_PUSH(2, &stk);
    STACK_PUSH(221, &stk);


    STACK_POP(&stk);


    STACK_POP(&stk);

    STACK_PUSH(231, &stk);


    STACK_PUSH(456, &stk);
    
    STACK_PUSH(564, &stk);
    STACK_PUSH(674, &stk);
    STACK_PUSH(100, &stk);

    StackDtor(&stk);

    return 0;
}