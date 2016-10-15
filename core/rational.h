#ifndef RATIONAL_H
#define RATIONAL_H

#include <gmp.h>

#include "types.h"


typedef struct {
    BaseExpression base;
    mpq_t value;
} Rational;


void Rational_init(Rational* q);
void Rational_set(Rational* r, mpq_t value);
void Rational_clear(Rational* q);
#endif
