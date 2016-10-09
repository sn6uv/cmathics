#include <stdlib.h>

#include "types.h"
#include "int.h"


MachineInteger* MachineInteger_new(int* value) {
    MachineInteger* p = (MachineInteger*) malloc(sizeof(MachineInteger));
    if (p) {
        p->base.ref = 0;
        p->base.type = MachineIntegerType;
        p->value = value;
    }
    return p;
}


void MachineInteger_free(MachineInteger* p) {
    free(p);
}
