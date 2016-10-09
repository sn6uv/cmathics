#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "types.h"


typedef struct {
    BaseExpression base;
    uint32_t last_evaluated;
    uint32_t hash;
    uint32_t argc;
    BaseExpression* head;
    BaseExpression* leaves[];  // zero length array of pointers
} NormalExpression;


NormalExpression* NormalExpression_new(uint32_t argc);
void NormalExpression_free(NormalExpression* p);
#endif
