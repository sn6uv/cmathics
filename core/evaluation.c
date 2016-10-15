#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "types.h"
#include "definitions.h"
#include "expression.h"
#include "evaluation.h"


Evaluation* Evaluation_new(Definitions* definitions, bool catch_interrupts) {
    Evaluation* result;
    result = (Evaluation*) malloc(sizeof(Evaluation));

    if (result != NULL) {
        result->definitions = definitions;
        result->recursion_depth = 0;
        result->timeout = false;
        result->stopped = false;
        result->catch_interrupts = catch_interrupts;
        result->interrupt = NoInterrupt;
        result->out = NULL;
    }
    return result;
}


// does not free definitions
void Evaluation_free(Evaluation* evaluation) {
    free(evaluation);
}


void send_message(Evaluation* evaluation, Symbol* symbol, char* tag) {
}


BaseExpression* CloneIfSingleton(BaseExpression* expr) {
    assert(expr->ref <= 1);
    return expr;
}

BaseExpression* DoEvaluate(BaseExpression* query_expr);

// returns NULL if nothing changed
BaseExpression* DoEvaluate_Expression(Expression* expr) {
    uint32_t i;
    Symbol* head_symbol;
    uint32_t eval_leaf_start, eval_leaf_stop;
    BaseExpression* child_result;
    BaseExpression* result;

    // Step 1
    // Evaluate the head
    while (true) {
        child_result = DoEvaluate(expr->head);
        if (child_result == NULL) break;
        expr->head = child_result;
    }

    // Step 2
    // Evaluate the leaves from left to right (according to Hold values).

    result = NULL;  // null until something changes

    if (expr->head->type == SymbolType) {
        head_symbol = (Symbol*) expr->head;

        // only one type of Hold attribute can be set at a time
        assert(head_symbol->attributes.is_holdfirst +
               head_symbol->attributes.is_holdrest +
               head_symbol->attributes.is_holdall +
               head_symbol->attributes.is_holdallcomplete <= 1);

        if (head_symbol->attributes.is_holdfirst) {
            eval_leaf_start = 1;
            eval_leaf_stop = expr->argc;
        } else if (head_symbol->attributes.is_holdrest) {
            eval_leaf_start = 0;
            eval_leaf_stop = 1;
        } else if (head_symbol->attributes.is_holdall) {
            // TODO flatten sequences
            eval_leaf_start = 0;
            eval_leaf_stop = 0;
        } else if (head_symbol->attributes.is_holdallcomplete) {
            // no more evaluation is applied
            return NULL;
        } else {
            eval_leaf_start = 0;
            eval_leaf_stop = expr->argc;
        }

        assert(0 <= eval_leaf_start);
        assert(eval_leaf_start <= eval_leaf_stop);
        assert(eval_leaf_stop <= expr->argc);

        // perform the evaluation
        for (i = eval_leaf_start; i < eval_leaf_stop; i++) {
            child_result = DoEvaluate(expr->leaves[i]);
            if (child_result != NULL) {
                expr->leaves[i] = child_result;
                result = (BaseExpression*) expr;  // a leaf changed
            }
        }
    }

    // Step 3
    // Apply UpValues for leaves
    // TODO

    // Step 4
    // Apply SubValues
    if (expr->head->type == ExpressionType) {
        if (((Expression*) expr->head)->head->type == SymbolType) {
            head_symbol = (Symbol*) ((Expression*) expr->head)->head;
            // TODO
        }
    }

    // Step 5
    // Evaluate the head with leaves. (DownValue)
    if (expr->head->type == SymbolType) {
        head_symbol = (Symbol*) expr->head;

        // first try to apply CFunction (if present)
        if (head_symbol->down_code != NULL) {
            child_result = (head_symbol->down_code)(expr);
            if (child_result != NULL) {
                return child_result;
            }
        }

        // if the CFunction is absent or returns NULL then apply downvalues
        // from the list
        // TODO
    }

    return result;
}


BaseExpression* DoEvaluate(BaseExpression* query_expr) {
    BaseExpression* expr;
    BaseExpression* result;

    expr = CloneIfSingleton(query_expr);

    if (expr->type == ExpressionType) {
        result = DoEvaluate_Expression((Expression*) expr);
    }
    return result;
}


BaseExpression* Evaluate(Evaluation* evaluation, BaseExpression* expression) {
    BaseExpression* result;
    // int64_t line_no;

    // TODO $HistoryLength

    // TODO Apply $Pre

    // TODO In[$Line]
    // line_no = get_line_no(evaluation);

    // perform evaluation
    result = DoEvaluate(expression);

    // TODO $Post

    // TODO Out[$Line]
    // line_no = get_line_no(evaluation); // might have changed

    // TODO $PrePrint

    // TODO MessageList and $MessageList

    // TODO out callback

    // Increment $Line
    // set_line_no(evaluation, line_no + 1);

    // TODO clear aborts

    return result;
}
