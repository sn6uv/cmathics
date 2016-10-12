#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <gmp.h>

#include "rational.h"
#include "gc.h"
#include "int.h"


Rational* Rational_new(void) {
    Rational* q = (Rational*) malloc(sizeof(Rational));
    if (q) {
        q->base.ref = 0;
        q->base.type = RationalType;
        q->numer = NULL;
        q->denom = NULL;
    }
    return q;
}


void Rational_set(Rational* q, Integer* numer, Integer* denom) {
    mpz_t big_r, big_a, big_b;

    // convert to a / b
    switch(TYPE_PAIR(numer->base.type, denom->base.type)) {
        case TYPE_PAIR(MachineIntegerType, MachineIntegerType):
            mpz_init_set_ui(big_a, numer->machine.value);
            mpz_init_set_ui(big_b, denom->machine.value);
            break;
        case TYPE_PAIR(BigIntegerType, MachineIntegerType):
            mpz_init_set(big_a, numer->big.value);
            mpz_init_set_ui(big_b, denom->machine.value);
            break;
        case TYPE_PAIR(MachineIntegerType, BigIntegerType):
            mpz_init_set_ui(big_a, numer->machine.value);
            mpz_init_set(big_b, denom->big.value);
            break;
        case TYPE_PAIR(BigIntegerType, BigIntegerType):
            mpz_init_set(big_a, numer->big.value);
            mpz_init_set(big_b, denom->big.value);
            break;
        default:
            assert(false);
    }

    // r = gcd(a, b)
    mpz_init(big_r);
    mpz_gcd(big_r, big_a, big_b);

    assert(mpz_cmp_ui(big_r, 0));
    assert(mpz_divisible_p(big_a, big_r));
    assert(mpz_divisible_p(big_b, big_r));

    // (a / r) / (b / r)
    mpz_divexact(big_a, big_a, big_r);
    mpz_divexact(big_b, big_b, big_r);

    // assign numer and denom
    q->numer = Integer_new_from_mpz(big_a);
    numer->base.ref++;
    q->denom = Integer_new_from_mpz(big_b);
    denom->base.ref++;
    return;
}


void Rational_free(Rational* q) {
    assert(q != NULL);
    assert(q->base.ref == 0);
    decref_free((BaseExpression*) q->numer);
    decref_free((BaseExpression*) q->denom);
    free(q);
    return;
}
