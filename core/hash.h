#ifndef HASH_H
#define HASH_H
#include "expression.h"
#include "definitions.h"

uint64_t Hash(const BaseExpression* expression);
uint64_t djb2(const char* str);

uint64_t Hash_Symbol(const Symbol* expression);
uint64_t Hash_Expression(const Expression* expression);
#endif
