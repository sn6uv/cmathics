#include <stdbool.h>
#include <string.h>

#include "pattern.h"
#include "expression.h"
#include "definitions.h"
#include "integer.h"
#include "string.h"
#include "real.h"


bool MatchQ_Symbol(Symbol* expr, Symbol* patt) {
    // compare as pointers: symbols are unique
    return expr == patt;
}


bool MatchQ_MachineInteger(MachineInteger* expr, MachineInteger* patt) {
    return expr->value == patt->value;
}


bool MatchQ_String(String* expr, String* patt) {
    return strcmp(expr->value, patt->value) == 0;
}


bool MatchQ_MachineReal(MachineReal* expr, MachineReal* patt) {
    return expr->value == patt->value;
}


bool MatchQ_Expression_Expression(Expression* expr, Expression* patt) {
    bool result;
    uint32_t i;
    result = false;
    if (expr->argc == patt->argc) {
        result = MatchQ(expr->head, patt->head);
        for (i=0; (i<expr->argc) && result; i++) {
            result = result && MatchQ(expr->leaves[i], patt->leaves[i]);
        }
    }
    return result;
}

bool MatchQ_Expression_Atom(BaseExpression* expr, Expression* patt) {
    bool result;
    Symbol* head;
    char* head_name;

    result = false;
    if (patt->head->type == SymbolType) {
        head = (Symbol*) patt->head;
        head_name = head->name;
        if (strcmp(head_name, "System`Blank") == 0) {
            result = true;
        }
        // TODO other types
    }
    return result;
}


// Does expression match the pattern?
bool MatchQ(BaseExpression* expr, BaseExpression* patt) {
    bool result;
    switch (TYPE_PAIR(expr->type, patt->type)) {
        case TYPE_PAIR(SymbolType, SymbolType):
            result = MatchQ_Symbol((Symbol*) expr, (Symbol*) patt);
            break;
        case TYPE_PAIR(MachineIntegerType, MachineIntegerType):
            result = MatchQ_MachineInteger((MachineInteger*) expr, (MachineInteger*) patt);
            break;
        case TYPE_PAIR(StringType, StringType):
            result = MatchQ_String((String*) expr, (String*) patt);
            break;
        case TYPE_PAIR(ExpressionType, ExpressionType):
            result = MatchQ_Expression_Expression((Expression*) expr, (Expression*) patt);
            break;
        case TYPE_PAIR(MachineIntegerType, ExpressionType):
        case TYPE_PAIR(BigIntegerType, ExpressionType):
        case TYPE_PAIR(MachineRealType, ExpressionType):
        case TYPE_PAIR(BigRealType, ExpressionType):
        case TYPE_PAIR(RationalType, ExpressionType):
        case TYPE_PAIR(ComplexType, ExpressionType):
        case TYPE_PAIR(SymbolType, ExpressionType):
        case TYPE_PAIR(StringType, ExpressionType):
            result = MatchQ_Expression_Atom(expr, (Expression*) patt);
            break;
        default:
            // TODO throw error
            result = false;
    }
    return result;
}


// replace expression at base
// Equivalent to Replace[expr, patt] but doesn't search into the expression
// e.g. DoReplace(1 + a, a -> 2) doesn't apply because it doesn't match at root
// returns NULL if no match is found
BaseExpression* DoReplace(BaseExpression* expr, BaseExpression* patt) {
    // TODO
    return NULL;
}
