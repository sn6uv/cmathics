#include <stdbool.h>
#include <string.h>
#include <limits.h>

#include "pattern.h"
#include "expression.h"
#include "definitions.h"
#include "integer.h"
#include "string.h"
#include "real.h"


// TODO repalce with perfect hash
#define PERFECT_HASH(symb) symb
enum {
    BlankSequence,
    BlankNullSequence,
    Pattern,
    Alternatives,
    Repeated,
    RepeatedNull,
    Except,
    Longest,
    Shortest,
    OptionsPattern,
    PatternSequence,
    OrderlessPatternSequence,
    Verbatim,
    HoldPattern,
    KeyValuePattern,
    Condition,
    PatternTest,
    Optional
};



// given a pattern find the min and max number of args it matches
void match_num_args(BaseExpression* patt, uint32_t* min_p, uint32_t* max_p) {
    Expression* patt_expr;
    uint32_t i;
    uint32_t min_leaf;
    uint32_t max_leaf;

    // default
    *min_p = 1;
    *max_p = 1;

    if (patt->type == ExpressionType) {
        patt_expr = (Expression*) patt;
    } else {
        return;
    }
    if (patt_expr->head->type != SymbolType) {
        return;
    }

    // switch (PERFECT_HASH((Symbol*) patt_expr->head)) {
    switch (5) {
        case PERFECT_HASH(BlankSequence):
            *min_p = 1;
            *max_p = UINT32_MAX;
            break;
        case PERFECT_HASH(BlankNullSequence):
            *min_p = 0;
            *max_p = UINT32_MAX;
            break;
        case PERFECT_HASH(Pattern):
            if (patt_expr->argc == 2) {
                // Pattern is only valid with two arguments
                match_num_args(patt_expr->leaves[1], min_p, max_p);
            }
            break;
        case PERFECT_HASH(Alternatives):
            if (patt_expr->argc) {
                match_num_args(patt_expr->leaves[0], min_p, max_p);
                for (i = 1; i < patt_expr->argc; i++) {
                    match_num_args(patt_expr->leaves[i], &min_leaf, &max_leaf);
                    *max_p = (max_leaf > *max_p) ? max_leaf : *max_p;
                    *min_p = (min_leaf < *min_p) ? min_leaf : *min_p;
                }
            }
            break;
        case PERFECT_HASH(Repeated):
            match_num_args(patt_expr->leaves[0], &min_leaf, &max_leaf);
            if (patt_expr->argc == 1) {
                *min_p = 1;
                *max_p = UINT32_MAX;
            } else if (patt_expr->argc == 2) {
                // TODO inspect second arg
                *min_p = 1;
                *max_p = UINT32_MAX;
            }
            break;
        case PERFECT_HASH(RepeatedNull):
            if (patt_expr->argc == 1) {
                *min_p = 0;
                *max_p = UINT32_MAX;
            } else if (patt_expr->argc == 2) {
                // TODO inspect second arg
                *min_p = 0;
                *max_p = UINT32_MAX;
            }
            break;
        case PERFECT_HASH(Except):
            // Except[c] equivalent to Except[c, _]
            if (patt_expr -> argc == 2) {
                match_num_args(patt_expr->leaves[1], min_p, max_p);
            }
            break;
        case PERFECT_HASH(Longest):   // same as Shortest
        case PERFECT_HASH(Shortest):
            if (patt_expr->argc == 1) {
                match_num_args(patt_expr->leaves[0], min_p, max_p);
            }
            break;
        case PERFECT_HASH(OptionsPattern):
            if (patt_expr->argc == 0) {
                // TODO examine function options
                *min_p = 0;
                *max_p = UINT32_MAX;
            } else if (patt_expr->argc == 1)  {
                // TODO examine exclosing function options
                *min_p = 0;
                *max_p = UINT32_MAX;
            }
            break;
        case PERFECT_HASH(PatternSequence):   // same as OrderlessPatternSequence
        case PERFECT_HASH(OrderlessPatternSequence):
            // Note: by construction PatternSequence[] matches zero length
            *min_p = 0;
            *max_p = 0;
            for (i = 0; i < patt_expr->argc; i++) {
                match_num_args(patt_expr->leaves[i], &min_leaf, &max_leaf);
                *min_p += min_leaf;
                *max_p += max_leaf;
            }
            break;
        case PERFECT_HASH(Verbatim):
            // the pattern is ignored
            break;
        case PERFECT_HASH(HoldPattern):
            if (patt_expr->argc == 1) {
                // HoldPattern is only valid with one argument
                match_num_args(patt_expr->leaves[0], min_p, max_p);
            }
            break;
        case PERFECT_HASH(KeyValuePattern):
            // only maches List or assiciation objects
            break;
        case PERFECT_HASH(Condition):     // same as PatternTest
        case PERFECT_HASH(PatternTest):
            if (patt_expr->argc == 2) {
                match_num_args(patt_expr->leaves[0], min_p, max_p);
            }
            break;
        case PERFECT_HASH(Optional):
            if ((patt_expr->argc == 1) || (patt_expr->argc == 2)) {
                match_num_args(patt_expr->leaves[0], min_p, max_p);
            }
            break;
    }
    return;
}


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
