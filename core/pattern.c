#include <stdbool.h>
#include <string.h>

#include "pattern.h"
#include "expression.h"
#include "definitions.h"
#include "int.h"
#include "string.h"
#include "real.h"

#define TYPE_PAIR(X, Y) ((int) X) << 4 | (int) Y


bool MatchQ_Symbol(const Definition* pattern, const Definition* expression) {
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


bool MatchQ_Expression_Expression(const NormalExpression* pattern, const NormalExpression* expression) {
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

bool MatchQ_Expression_Atom(const NormalExpression* pattern, const BaseExpression* expression) {
    bool result;
    Definition* head;
    char* head_name;

    result = false;
    if (pattern->head->type == SymbolType) {
        head = (Definition*) pattern->head;
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
            result = MatchQ_Symbol((Definition*) pattern, (Definition*) expression);
            break;
        case TYPE_PAIR(MachineIntegerType, MachineIntegerType):
            result = MatchQ_MachineInteger((MachineInteger*) pattern, (MachineInteger*) expression);
            break;
        case TYPE_PAIR(StringType, StringType):
            result = MatchQ_String((String*) pattern, (String*) expression);
            break;
        case TYPE_PAIR(NormalExpressionType, NormalExpressionType):
            result = MatchQ_Expression_Expression((NormalExpression*) pattern, (NormalExpression*) expression);
            break;
        case TYPE_PAIR(NormalExpressionType, MachineIntegerType):
        case TYPE_PAIR(NormalExpressionType, BigIntegerType):
        case TYPE_PAIR(NormalExpressionType, MachineRealType):
        case TYPE_PAIR(NormalExpressionType, BigRealType):
        case TYPE_PAIR(NormalExpressionType, RationalType):
        case TYPE_PAIR(NormalExpressionType, ComplexType):
        case TYPE_PAIR(NormalExpressionType, SymbolType):
        case TYPE_PAIR(NormalExpressionType, StringType):
            result = MatchQ_Expression_Atom((NormalExpression*) pattern, expression);
            break;
        default:
            // TODO throw error
            result = false;
    }
    return result;
}
