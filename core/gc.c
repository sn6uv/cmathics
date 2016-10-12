#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "integer.h"
#include "real.h"
#include "rational.h"
#include "expression.h"
#include "definitions.h"
#include "string.h"
#include "gc.h"


// decrements the reference by one and frees if unreferenced
void decref_free(BaseExpression* expr) {
    expr->ref--;
    assert(expr->ref >= 0);
    if (expr->ref == 0) {
        free(expr);
    }
}


void BaseExpression_free(BaseExpression* expr) {
    switch (expr->type) {
        case MachineIntegerType:
            MachineInteger_free((MachineInteger*) expr);
            break;
        case BigIntegerType:
            BigInteger_free((BigInteger*) expr);
            break;
        case MachineRealType:
            MachineReal_free((MachineReal*) expr);
            break;
        case BigRealType:
            BigReal_free((BigReal*) expr);
            break;
        case RationalType:
            Rational_free((Rational*) expr);
            break;
        // case ComplexType:
        //     Complex_free((Complex*) expr);
        //     break;
        case ExpressionType:
            Expression_free((Expression*) expr);
            break;
        // case SymbolType:
        //     Symbol_free((Symbol*) expr);
        //     break;
        case StringType:
            String_free((String*) expr);
            break;
        // case RawExpressionType:
        //     RawExpression_free((RawExpression*) expr);
        //     break;
        default:
            assert(false);
    }
}
