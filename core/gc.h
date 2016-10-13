#ifndef GC_H
#define GC_H
#include "types.h"

typedef struct _GC_Object {
    BaseExpression* item;
    struct _GC_Object* next;
} GC_Object;


void GC_Init(void);
MachineInteger* GC_Alloc_MachineInteger(int64_t value);

void decref_free(BaseExpression* expr);
#endif
