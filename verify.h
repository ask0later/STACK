#ifndef VERIFY_H
#define VERIFY_H

#include "directives.h"

int StackVerify(Stack* data);

void DumpErrors(int error_num);
void Verify(Stack* data);
int ErrorRate(Stack* data);



void StackDump(Stack* data);
//

#endif