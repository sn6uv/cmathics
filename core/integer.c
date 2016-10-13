#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "types.h"
#include "integer.h"


void MachineInteger_init(MachineInteger* p) {
    p->base.ref = 0;
    p->base.type = MachineIntegerType;
    p->value = 0;
}


void MachineInteger_set(MachineInteger* p, const int64_t value) {
    p->value = value;
}


void BigInteger_init(BigInteger* p) {
    p->base.ref = 0;
    p->base.type = BigIntegerType;
    mpz_init(p->value);
}


void BigInteger_set(BigInteger* p, const mpz_t op) {
    mpz_set(p->value, op);
}
