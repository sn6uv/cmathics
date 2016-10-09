#include "types.h"
#include "real.h"


MachineReal* MachineReal_new(double* value) {
    MachineReal* p = (MachineReal*) malloc(sizeof(MachineReal));
    if (p) {
        p->base.ref = 0;
        p->base.type = MachineRealType;
        p->value = value;
    }
    return p;
}


void MachineReal_free(MachineReal* p) {
    free(p);
}


