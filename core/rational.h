#ifndef RATIONAL_H
#define RATIONAL_H

#include "integer.h"


typedef struct {
    BaseExpression base;
    Integer* numer;
    Integer* denom;
} Rational;


void Rational_init(Rational* q);
void Rational_set(Rational* r, Integer* numer, Integer* denom);
#endif
