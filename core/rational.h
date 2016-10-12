#ifndef RATIONAL_H
#define RATIONAL_H

#include "integer.h"


typedef struct {
    BaseExpression base;
    Integer* numer;
    Integer* denom;
} Rational;


Rational* Rational_new(void);
void Rational_free(Rational* q);
void Rational_set(Rational* r, Integer* numer, Integer* denom);
#endif
