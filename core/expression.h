#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "types.h"


typedef struct {
    BaseExpression base;
    uint64_t hash;
    uint32_t last_evaluated;
    uint32_t argc;
    BaseExpression* head;
    BaseExpression* leaves[];  // zero length array of pointers
} Expression;


Expression* Expression_new(uint32_t argc);
void Expression_init(Expression* expr, BaseExpression* head, BaseExpression** leaves);
void Expression_free(Expression* p);
#endif
