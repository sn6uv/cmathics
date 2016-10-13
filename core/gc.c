#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "integer.h"
#include "real.h"
#include "rational.h"
#include "expression.h"
#include "definitions.h"
#include "string.h"
#include "gc.h"


#define NSMALLNEGINTS 10
#define NSMALLPOSINTS 1014
static MachineInteger small_ints[NSMALLNEGINTS + NSMALLPOSINTS];


// initialise the GC
void GC_Init(void) {
    // init small ints
    int64_t i;
    for (i=0; i<(NSMALLNEGINTS + NSMALLPOSINTS); i++) {
        MachineInteger_init(&small_ints[i]);
        MachineInteger_set(&small_ints[i], i - NSMALLNEGINTS);
    }

    // TODO expression cache?
    return;
}
// 
// 
// MachineInteger* GC_Alloc_MachineInteger(int64_t value) {
//     MachineInteger* result;
//     if (value >= -NSMALLNEGINTS && value < NSMALLPOSINTS) {
//         // initialised in GC_Init
//         result = &small_ints[value + NSMALLNEGINTS];
//     } else {
//         result = Mathics_malloc(sizeof(MachineInteger));
//         MachineInteger_set(result, value);
//     }
//     return result;
// }
// 
// 
// void GC_Free_MachineInteger(MachineInteger* p) {
//     if (p->value >= -NSMALLNEGINTS && p->value < NSMALLPOSINTS) {
//         // do nothing
//     } else {
//         free(p);
//     }
//     return;
// }
