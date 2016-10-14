#include <assert.h>
#include <stdint.h>

#include "mem.h"
#include "types.h"
#include "rational.h"
#include "refcounting.h"


// increment reference count
void RefInc(BaseExpression* p) {
    p->ref++;
}

// decrement reference count and free if object becomes unreferenced
void RefDec(BaseExpression* p) {
    Expression* expr;
    Rational* rat;
    uint32_t i;

    p->ref--;
    if (p->ref == 0) {
        switch(p->type) {
            case ExpressionType:
                expr = (Expression*) p;
                RefDec(expr->head);
                for (i=0; i<expr->argc; i++) {
                    RefDec(expr->leaves[i]);
                }
                break;
            case RationalType:
                rat = (Rational*) p;
                RefDec((BaseExpression*) rat->numer);
                RefDec((BaseExpression*) rat->denom);
                break;
            case SymbolType:
                // TODO ownvalues etc.
                break;
            default:
                break;
        }
        MemFree(p);
    }
}
