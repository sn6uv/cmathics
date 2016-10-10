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
