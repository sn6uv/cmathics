#include <stdbool.h>

#include "pattern.h"
#include "expression.h"
#include "definitions.h"
#include "int.h"


bool MatchQ_Symbol(Definition* pattern, BaseExpression* expression) {
    if (expression->type == SymbolType) {
        // compare as pointers: symbols are unique
        return pattern == (Definition*) expression;
    }
    return false;
}


bool MatchQ_MachineInteger(MachineInteger* pattern, BaseExpression* expression) {
    MachineInteger* value;
    if (expression->type == MachineIntegerType) {
        value = (MachineInteger*) expression;
        return pattern->value == value->value;
    }
    // TODO BigInteger?
    return false;
}


// Does expression match the pattern?
bool MatchQ(BaseExpression* pattern, BaseExpression* expression) {
    bool result;
    switch (pattern->type) {
        case SymbolType:
            result = MatchQ_Symbol((Definition*) pattern, expression);
            break;
        case MachineIntegerType:
            result = MatchQ_MachineInteger((MachineInteger*) pattern, expression);
            break;
        default:
            // TODO throw error
            result = false;
    }
    return result;
}
