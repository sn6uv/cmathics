#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <gmp.h>

#include "rational.h"


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


// copies denominator to a new Integer
Integer* Rational_numer(const Rational* q) {
    return Integer_from_mpz(mpq_numref(q->value));
}


// copies numerator to a new Integer
Integer* Rational_denom(const Rational* q) {
    return Integer_from_mpz(mpq_denref(q->value));
}
