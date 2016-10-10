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


int get_line_no(Evaluation* evaluation) {
    int line_no;
    int* line_nop = get_int_value(evaluation->definitions, "System`$Line");
    if (line_nop == NULL) {
        line_no = 1;
    } else {
        line_no = *line_nop + 1;
    }
    return line_no;
}


void set_line_no(Evaluation* evaluation, int value) {
    set_int_value(evaluation->definitions, "System`$Line", value);
    return;
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
    BaseExpression* result;
    int line_no;

    // TODO $HistoryLength

    // TODO Apply $Pre

    // TODO In[$Line]
    line_no = get_line_no(evaluation);

    // perform evaluation
    if (expression->type == NormalExpressionType) {
        result = evaluate_NormalExpression(evaluation, (NormalExpression*) expression);
    } else {
        result = expression;
    }

    // TODO $Post

    // TODO Out[$Line]
    line_no = get_line_no(evaluation); // might have changed

    // TODO $PrePrint

    // TODO MessageList and $MessageList

    // TODO out callback

    // Increment $Line
    set_line_no(evaluation, line_no + 1);

    // TODO clear aborts

    return result;
}
