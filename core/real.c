#include <stdlib.h>

#include "types.h"
#include "real.h"


MachineReal* MachineReal_new(void) {
    MachineReal* p = (MachineReal*) malloc(sizeof(MachineReal));
    if (p) {
        p->base.ref = 0;
        p->base.type = MachineRealType;
    }
    return p;
}


void MachineReal_set(MachineReal* p, double value) {
    *p->value = value;
    return;
}


void MachineReal_free(MachineReal* p) {
    free(p);
    return;
}


BigReal* BigReal_new(mpfr_prec_t prec) {
    BigReal* p = (BigReal*) malloc(sizeof(BigReal));
    if (p) {
        p->base.ref = 0;
        p->base.type = BigRealType;
        mpfr_init2(p->value, prec);
    }
    return p;
}

void BigReal_set_d(BigReal* p, double value) {
    mpfr_set_d(p->value, value, MPFR_RNDN);
    return;
}


void BigReal_free(BigReal* p) {
    mpfr_clear(p->value);
    free(p);
    return;
}
