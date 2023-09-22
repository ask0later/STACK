#include "directives.h"
#include "stack.h"

int main()
{
    printf("adas\n");

    struct Stack data;
    printf("asdsada\n");

    StackCtor(&data);

    free(data.sequence);
    // int value = 20;
    // StackPush(value, &data);
    // value = 30;
    // StackPush(value, &data);
    // StackPop(&data);
    // value = 20;
    // StackPush(value, &data);

    //StackDtor(&data);

    return 0;
}