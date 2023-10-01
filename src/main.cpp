#include "stack.h"

int main() 
{
    CleanFile();
    struct Stack *stk;
    CREATE_STACK(&stk);
    //stk.capacity = 20;
    STACK_PUSH(30, stk);
    STACK_PUSH(50, stk);
    STACK_PUSH(60, stk);
    STACK_PUSH(70, stk);
    STACK_PUSH(80, stk);

    DeleteStack(&stk);

    return 0;
}