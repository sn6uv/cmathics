#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "expression.h"
#include "hash.h"
#include "mem.h"
#include "refcounting.h"


Expression* Expression_new(uint32_t argc) {
    Expression* p = (Expression*) MemAlloc(sizeof(Expression) + argc * sizeof(BaseExpression*));
    Expression_init(p, argc);
    return p;
}


void Expression_init(Expression* p, uint32_t argc) {
    p->base.ref = 0;
    p->base.type = ExpressionType;
    p->argc = argc;
    p->hash = 0;
}


void Expression_set(Expression* expr, BaseExpression* head, BaseExpression** leaves) {
    int32_t i;
    expr->head = head;
    RefInc(head);
    for (i=0; i<expr->argc; i++){
        expr->leaves[i] = leaves[i];
        RefInc(leaves[i]);
    }
    expr->hash = Hash_Expression(expr);
}
