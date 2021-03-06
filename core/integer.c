#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "types.h"
#include "integer.h"


MachineInteger* MachineInteger_new(void) {
    MachineInteger* p = (MachineInteger*) malloc(sizeof(MachineInteger));
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
    BigInteger* p = (BigInteger*) malloc(sizeof(BigInteger));
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


// convert mpz to Integer
Integer* Integer_from_mpz(const mpz_t value) {
    MachineInteger* machine_result;
    BigInteger* big_result;

    if (mpz_fits_slong_p(value)) {
        machine_result = MachineInteger_new();
        MachineInteger_set(machine_result, mpz_get_si(value));
        return (Integer*) machine_result;
    } else {
        big_result = BigInteger_new();
        BigInteger_set(big_result, value);
        return (Integer*) big_result;
    }
}
