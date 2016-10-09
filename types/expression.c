#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "expression.h"


NormalExpression* NormalExpression_new(uint32_t argc) {
    uint32_t hash;
    hash = 0;   // TODO
    NormalExpression* p = (NormalExpression*) malloc(sizeof(NormalExpression) + argc * sizeof(void*));
    if (p) {
        p->base.ref = 0;
        p->base.type = NormalExpressionType;
        p->hash = hash;
        p->argc = argc;
    }
    return p;
}


void NormalExpression_free(NormalExpression* p) {
    free(p);
}
