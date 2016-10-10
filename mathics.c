#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core/expression.h"
#include "core/definitions.h"
#include "core/formatter.h"
#include "core/evaluation.h"


int main() {
    char* buf;
    Definitions* definitions = Definitions_new(64);
    Definitions_init(definitions, NULL);  // System Definitions

    NormalExpression* expr = NormalExpression_new(2);
    expr->head = (BaseExpression*) Definitions_lookup(definitions, "Plus");
    expr->leaves[0] = (BaseExpression*) Definitions_lookup(definitions, "a");
    expr->leaves[1] = (BaseExpression*) Definitions_lookup(definitions, "b");

    // printf("%i\n", definitions->count);
    // printf("%s\n", FullForm((BaseExpression*) Definitions_lookup(definitions, "a")));

    // buf = FullForm((BaseExpression*) expr);
    // printf("%s\n", buf);

    Evaluation* evaluation = Evaluation_new(definitions, true);
    BaseExpression* result = evaluate_expression(evaluation, (BaseExpression*) expr);

    buf = FullForm((BaseExpression*) result);
    printf("%s\n", buf);

    free(buf);
    free(expr);
    Definitions_free(definitions);
    return 0;
}
