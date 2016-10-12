#include <stdbool.h>
#include <string.h>

#include "pattern.h"
#include "expression.h"
#include "definitions.h"
#include "integer.h"
#include "string.h"
#include "real.h"


bool MatchQ_Symbol(const Symbol* pattern, const Symbol* expression) {
    // compare as pointers: symbols are unique
    return pattern == expression;
}


bool MatchQ_MachineInteger(const MachineInteger* pattern, const MachineInteger* expression) {
    return pattern->value == expression->value;
}


bool MatchQ_String(const String* pattern, const String* expression) {
    return strcmp(pattern->value, expression->value) == 0;
}


bool MatchQ_MachineReal(const MachineReal* pattern, const MachineReal* expression) {
    return pattern->value == expression->value;
}


bool MatchQ_Expression_Expression(const Expression* pattern, const Expression* expression) {
    bool result;
    uint32_t i;
    result = false;
    if (pattern->argc == expression->argc) {
        result = MatchQ(pattern->head, expression->head);
        for (i=0; (i<expression->argc) && result; i++) {
            result = result && MatchQ(pattern->leaves[i], expression->leaves[i]);
        }
    }
    return result;
}

bool MatchQ_Expression_Atom(const Expression* pattern, const BaseExpression* expression) {
    bool result;
    Symbol* head;
    char* head_name;

    result = false;
    if (pattern->head->type == SymbolType) {
        head = (Symbol*) pattern->head;
        head_name = head->name;
        if (strcmp(head_name, "System`Blank") == 0) {
            result = true;
        }
        // TODO other types
    }
    return result;
}


// Does expression match the pattern?
bool MatchQ(const BaseExpression* pattern, const BaseExpression* expression) {
    bool result;
    switch (TYPE_PAIR(pattern->type, expression->type)) {
        case TYPE_PAIR(SymbolType, SymbolType):
            result = MatchQ_Symbol((Symbol*) pattern, (Symbol*) expression);
            break;
        case TYPE_PAIR(MachineIntegerType, MachineIntegerType):
            result = MatchQ_MachineInteger((MachineInteger*) pattern, (MachineInteger*) expression);
            break;
        case TYPE_PAIR(StringType, StringType):
            result = MatchQ_String((String*) pattern, (String*) expression);
            break;
        case TYPE_PAIR(ExpressionType, ExpressionType):
            result = MatchQ_Expression_Expression((Expression*) pattern, (Expression*) expression);
            break;
        case TYPE_PAIR(ExpressionType, MachineIntegerType):
        case TYPE_PAIR(ExpressionType, BigIntegerType):
        case TYPE_PAIR(ExpressionType, MachineRealType):
        case TYPE_PAIR(ExpressionType, BigRealType):
        case TYPE_PAIR(ExpressionType, RationalType):
        case TYPE_PAIR(ExpressionType, ComplexType):
        case TYPE_PAIR(ExpressionType, SymbolType):
        case TYPE_PAIR(ExpressionType, StringType):
            result = MatchQ_Expression_Atom((Expression*) pattern, expression);
            break;
        default:
            // TODO throw error
            result = false;
    }
    return result;
}
