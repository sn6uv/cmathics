#include <assert.h>
#include <stdlib.h>
#include "misc.h"

uint32_t Expression_height(BaseExpression* expression) {
    uint32_t result;
    uint32_t leaf_height;
    int i;
    Expression* nexpression;

    assert(expression != NULL);
    switch (expression->type) {
        case ExpressionType:
            nexpression = (Expression*) expression;
            result = Expression_height(nexpression->head);
            for (i=0; i<nexpression->argc; i++) {
                leaf_height = Expression_height(nexpression->leaves[i]);
                if (leaf_height > result) {
                    result = leaf_height;
                }
            }
            result++; // for this level
            break;
        case RawExpressionType:
            // TODO
        default:
            result = 1;
    }
    return result;
}
