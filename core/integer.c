#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "types.h"
#include "integer.h"
#include "mem.h"


MachineInteger* MachineInteger_new(void) {
    MachineInteger* p = (MachineInteger*) MemAlloc(sizeof(MachineInteger));
    MachineInteger_init(p);
    return p;
}


void MachineInteger_init(MachineInteger* p) {
    p->base.ref = 0;
    p->base.type = MachineIntegerType;
    p->value = 0;
}


void MachineInteger_set(MachineInteger* p, const int64_t value) {
    p->value = value;
}


BigInteger* BigInteger_new(void) {
    BigInteger* p = (BigInteger*) MemAlloc(sizeof(BigInteger));
    BigInteger_init(p);
    return p;
}


void BigInteger_init(BigInteger* p) {
    p->base.ref = 0;
    p->base.type = BigIntegerType;
    mpz_init(p->value);
}


void BigInteger_set(BigInteger* p, const mpz_t op) {
    mpz_set(p->value, op);
}
