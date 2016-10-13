#include <stdbool.h>
#include <stdlib.h>

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


BaseExpression* Evaluate_Expression(Evaluation* evaluation, Expression* expression) {
    // TODO
    return (BaseExpression*) expression;
}


BaseExpression* Evaluate_BaseExpression(Evaluation* evaluation, BaseExpression* expression) {
    return expression;
}


BaseExpression* Evaluate(Evaluation* evaluation, BaseExpression* expression) {
    BaseExpression* result;
    // int64_t line_no;

    // TODO $HistoryLength

    // TODO Apply $Pre

    // TODO In[$Line]
    // line_no = get_line_no(evaluation);

    // perform evaluation
    if (expression->type == ExpressionType) {
        result = Evaluate_Expression(evaluation, (Expression*) expression);
    } else {
        result = expression;
    }

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
