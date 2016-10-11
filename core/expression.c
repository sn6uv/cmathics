#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "expression.h"


Expression* Expression_new(uint32_t argc) {
    uint32_t hash;
    hash = 0;   // TODO
    Expression* p = (Expression*) malloc(sizeof(Expression) + argc * sizeof(void*));
    if (p) {
        p->base.ref = 0;
        p->base.type = ExpressionType;
        p->hash = hash;
        p->argc = argc;
    }
    return p;
}


void Expression_free(Expression* p) {
    free(p);
}
