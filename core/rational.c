#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <gmp.h>

#include "rational.h"
#include "integer.h"


void Rational_init(Rational* q) {
    q->base.ref = 0;
    q->base.type = RationalType;
    mpq_init(q->value);
}


void Rational_set(Rational* q, mpq_t value) {
    mpq_set(q->value, value);
}


void Rational_clear(Rational* q) {
    mpq_clear(q->value);
}
