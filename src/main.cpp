#include "stack.h"

int main() 
{
    CleanFile();
    struct Stack stk;
    StackCtor(&stk);

    StackDtor(&stk);

    return 0;
}