#include <stdint.h>
#include <stdbool.h>

#include "types.h"
#include "integer.h"
#include "arithmetic.h"


BaseExpression* Eval_Plus(Expression* expr) {
    uint32_t i;
    bool all_mi;
    MachineInteger* mi_result;
    int64_t mi_value;

    // Plus[] -> 0
    if (expr->argc == 0) {
        mi_result = MachineInteger_new();
        MachineInteger_set(mi_result, 0);
        return (BaseExpression*) mi_result;
    }

    // Plus[a_] -> a
    if (expr->argc == 1) {
        return expr->leaves[0];
    }

    // Plus[a__MachineInteger]
    all_mi = true;
    for (i=0; i<expr->argc; i++) {
        if (expr->leaves[i]->type != MachineIntegerType) {
            all_mi = false;
            break;
        }
    }

    if (all_mi) {
        mi_value = 0;
        for (i=0; i<expr->argc; i++) {
            mi_value += ((MachineInteger*) expr->leaves[i])->value;
        }
        mi_result = MachineInteger_new();
        MachineInteger_set(mi_result, mi_value);
        return (BaseExpression*) mi_result;
    }

    // TODO
    return (BaseExpression*) expr;
}
