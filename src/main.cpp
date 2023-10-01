#include "stack.h"

int main() 
{
    CleanFile();
    struct Stack stk;
    StackCtor(&stk);
    STACK_PUSH(30, &stk);
    //stk.size = 30;
    STACK_PUSH(50, &stk);
    STACK_PUSH(60, &stk);
    STACK_PUSH(70, &stk);
    STACK_PUSH(80, &stk);

    StackDtor(&stk);

    return 0;
}