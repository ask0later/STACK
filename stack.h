#ifndef STACK_H
#define STACK_H

#include "directives.h"

const size_t MIN_CAPACITY = 30;

void StackCtor(Stack* data);
void StackDtor(Stack* data);

void StackPush(int value, Stack* data);
void StackPop(Stack* data);

void ReCalloc(int more_or_less, Stack* data);


void Verify(Stack* data);
void StackDump(Stack* data);

#endif