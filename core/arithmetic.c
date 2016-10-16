#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

#include "types.h"
#include "integer.h"
#include "arithmetic.h"
#include "real.h"
#include "rational.h"


// sums all integers in an expression
Integer* add_Integers(Expression* expr) {
    uint32_t i;
    int64_t machine_leaf;
    Type type;
    mpz_t result;
    Integer* return_value;

    // XXX right now the entire computation is done with GMP. This is slower
    // than using machine precision arithmetic but simpler because we don't
    // need to handle overflow. Could be optimised.

    mpz_init(result);

    for (i=0; i<expr->argc; i++) {
        type = expr->leaves[i]->type;
        if (type == MachineIntegerType) {
            machine_leaf = ((MachineInteger*) expr->leaves[i])->value;
            if (machine_leaf >= 0) {
                mpz_add_ui(result, result, (uint64_t) machine_leaf);
            } else {
                mpz_add_ui(result, result, (uint64_t) -machine_leaf);
            }
        } else if (type == BigIntegerType) {
            mpz_add(result, result, ((BigInteger*) expr->leaves[i])->value);
        }
    }

    return_value = mpz_to_Integer(result);
    mpz_clear(result);
    return return_value;
}


BaseExpression* add_MachineInexact(Expression* expr) {
    Type type;
    uint32_t i;
    BaseExpression** symbolics;
    uint32_t symbolic_count;
    double sum;
    BaseExpression* leaf;
    Expression* plus_result;
    BaseExpression* result;

    // create an array to store all the symbolic arguments which can't be evaluated.
    symbolic_count = 0;
    symbolics = malloc(sizeof(BaseExpression*) * expr->argc);

    sum = 0.0;
    for (i = 0; i < expr->argc; i++) {
        leaf = expr->leaves[i];
        type = leaf->type;
        switch(type) {
            case MachineIntegerType:
                sum += (double) (((MachineInteger*) leaf)->value);
                break;
            case BigIntegerType:
                sum += mpz_get_d(((BigInteger*) leaf)->value);
                break;
            case MachineRealType:
                sum += ((MachineReal*) leaf)->value;
                break;
            case BigRealType:
                sum += mpfr_get_d(((BigReal*) leaf)->value, MPFR_RNDN);
                break;
            case RationalType:
                sum += mpq_get_d(((Rational*) leaf)->value);
                break;
            case ComplexType:
                assert(false);
                break;
            case ExpressionType:
            case SymbolType:
            case StringType:
            case RawExpressionType:
                symbolics[symbolic_count++] = leaf;
                break;
        }
    }

    // at least one non-symbolic
    assert(symbolic_count != expr->argc);

    if (symbolic_count == expr->argc - 1) {
        // one non-symbolic: nothing to do
         result = NULL;
    } else if (symbolic_count) {
        // at least one symbolic
        symbolics[symbolic_count++] = (BaseExpression*) MachineReal_from_d(sum);
        plus_result = Expression_new(symbolic_count);
        Expression_set(plus_result, expr->head, symbolics);
    } else {
        // no symbolics
        result = (BaseExpression*) MachineReal_from_d(sum);
    }

    free(symbolics);
    return result;
}


BaseExpression* _Plus(Expression* expr) {
    uint32_t i;
    Type type;
    MachineInteger* machine_result;
    Integer* integer_result;

    // Plus[] -> 0
    if (expr->argc == 0) {
        machine_result = MachineInteger_new();
        MachineInteger_set(machine_result, 0);
        return (BaseExpression*) machine_result;
    }

    // Plus[a_] -> a
    if (expr->argc == 1) {
        return expr->leaves[0];
    }

    // bit field to determine which types are present
    uint16_t types_seen = 0;
    for (i=0; i<expr->argc; i++) {
        type = expr->leaves[i]->type;
        types_seen = types_seen & (1 << type);
    }

    const uint16_t int_mask = (1 << BigIntegerType) & (1 << MachineIntegerType);

    // expression contains a Real
    if (types_seen & (1 << MachineRealType)) {
        return (BaseExpression*) add_MachineInexact(expr);
    }

    // expression is all Integers
    if ((types_seen & int_mask) == types_seen) {
        return (BaseExpression*) add_Integers(expr);
    }

    // expression contains an Integer
    if (types_seen & int_mask) {
        integer_result = add_Integers(expr);
        // FIXME return Plus[symbolics__, integer_result]
        return (BaseExpression*) integer_result;
    }

    // TODO rational and complex

    // expression is symbolic
    return NULL;
}
