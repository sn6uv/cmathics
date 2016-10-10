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

void send_message(Evaluation* evaluation, Definition* symbol, char* tag) {
}


BaseExpression* evaluate_NormalExpression(Evaluation* evaluation, NormalExpression* expression) {
    // TODO
    return (BaseExpression*) expression;
}


BaseExpression* evaluate_BaseExpression(Evaluation* evaluation, BaseExpression* expression) {
    return expression;
}


BaseExpression* evaluate_expression(Evaluation* evaluation, BaseExpression* expression) {
    int* line_nop;
    int line_no;
    BaseExpression* result;

    // increment $Line
    line_nop = get_int_value(evaluation->definitions, "System`$Line");
    if (line_nop == NULL) {
        line_no = 1;
    } else {
        line_no = *line_nop + 1;
    }
    set_int_value(evaluation->definitions, "System`$Line", line_no);

    // TODO $HistoryLength

    // TODO In[$Line]

    // perform evaluation
    if (expression->type == NormalExpressionType) {
        result = evaluate_NormalExpression(evaluation, (NormalExpression*) expression);
    } else {
        result = expression;
    }

    // TODO Out[$Line]

    // return
    return result;
}

