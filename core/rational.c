#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <gmp.h>

#include "rational.h"
#include "integer.h"


void Rational_init(Rational* q) {
    q->base.ref = 0;
    q->base.type = RationalType;
    q->numer = NULL;
    q->denom = NULL;
}


void Rational_set(Rational* q, Integer* numer, Integer* denom) {
    q->numer = numer;
    q->denom = denom;
    numer->base.ref++;
    denom->base.ref++;
}


void Rational_normalise(Rational* q) {
    mpz_t big_r, big_a, big_b;

    Integer* numer = q->numer;
    Integer* denom = q->denom;

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
    // FIXME // q->numer = Integer_new_from_mpz(big_a);
    // FIXME // q->denom = Integer_new_from_mpz(big_b);

    // TODO update refs
    return;
}
