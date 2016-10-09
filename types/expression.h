#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "types.h"


typedef struct {
    BaseExpression base;
    char* name;
} Symbol;


typedef struct NormalExpression {
    BaseExpression base;
    uint32_t last_evaluated;
    uint32_t hash;
    uint32_t argc;
    Symbol* head;
    struct NormalExpression* leaves[];  // zero length array of pointers
} NormalExpression;

Symbol* Symbol_new(const char* name);
void Symbol_free(Symbol* p);

NormalExpression* NormalExpression_new(uint32_t argc);
void NormalExpression_free(NormalExpression* p);
#endif
