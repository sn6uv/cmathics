#ifndef MEM_H
#define MEM_H

#include <stdint.h>
#include "expression.h"

void MemInit(void);
BaseExpression* MemAlloc(uint32_t size);
void MemFree(BaseExpression* item);
#endif
