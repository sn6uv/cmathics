#include <stdlib.h>

#include "types.h"
#include "real.h"


void MachineReal_init(MachineReal* p) {
    p->base.ref = 0;
    p->base.type = MachineRealType;
    return;
}


void MachineReal_set(MachineReal* p, const double value) {
    *p->value = value;
    return;
}


void BigReal_init(BigReal* p, const mpfr_prec_t prec) {
    p->base.ref = 0;
    p->base.type = BigRealType;
    mpfr_init2(p->value, prec);
    return;
}


void BigReal_set(BigReal* p, const double value) {
    mpfr_set_d(p->value, value, MPFR_RNDN);
    return;
}


void BigReal_clear(BigReal* p) {
    mpfr_clear(p->value);
    return;
}
