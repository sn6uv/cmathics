#include <stdlib.h>
#include <assert.h>

#include "types.h"
#include "int.h"


MachineInteger* MachineInteger_new(void) {
    MachineInteger* p = (MachineInteger*) malloc(sizeof(MachineInteger));
    if (p) {
        p->base.ref = 0;
        p->base.type = MachineIntegerType;
        p->value = 0;
    }
    return p;
}


void MachineInteger_set(MachineInteger* p, int value) {
    assert(p != NULL);
    p->value = value;
}


void MachineInteger_free(MachineInteger* p) {
    free(p);
}


BigInteger* BigInteger_new(void) {
    BigInteger* p = (BigInteger*) malloc(sizeof(BigInteger));
    if (p) {
        p->base.ref = 0;
        p->base.type = BigIntegerType;
        mpz_init(p->value);
    }
    return p;
}


void BigInteger_set_ui(BigInteger* p, unsigned long int op) {
    mpz_set_ui(p->value, op);
}

void BigInteger_set_si(BigInteger* p, signed long int op) {
    mpz_set_si(p->value, op);
}


void BigInteger_free(BigInteger* p) {
    mpz_clear(p->value);
    free(p);
}
