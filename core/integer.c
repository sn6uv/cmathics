#include <stdlib.h>
#include <assert.h>

#include "types.h"
#include "integer.h"


MachineInteger* MachineInteger_new(void) {
    MachineInteger* p = (MachineInteger*) malloc(sizeof(MachineInteger));
    if (p) {
        p->base.ref = 0;
        p->base.type = MachineIntegerType;
        p->value = 0;
    }
    return p;
}


void MachineInteger_set(MachineInteger* p, const int64_t value) {
    assert(p != NULL);
    assert(p->base.ref == 0);
    p->value = value;
}


void MachineInteger_free(MachineInteger* p) {
    assert(p != NULL);
    assert(p->base.ref == 0);
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


void BigInteger_set(BigInteger* p, const mpz_t op) {
    mpz_set(p->value, op);
}


void BigInteger_free(BigInteger* p) {
    mpz_clear(p->value);
    free(p);
}


Integer* Integer_new_from_mpz(const mpz_t op) {
    MachineInteger* m;
    BigInteger* b;
    Integer* result;

    if (mpz_fits_slong_p(op) != 0) {
        m = MachineInteger_new();
        if (m) {
            MachineInteger_set(m, mpz_get_si(op));
        }
        result = (Integer*) m;
    } else {
        b = BigInteger_new();
        if (b) {
            BigInteger_set(b, op);
        }
        result = (Integer*) b;
    }
    return result;
}
