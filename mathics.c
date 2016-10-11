#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core/misc.h"
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

    Evaluation* evaluation = Evaluation_new(definitions, true);
    BaseExpression* result = evaluate_expression(evaluation, (BaseExpression*) expr);

    buf = FullForm((BaseExpression*) result);
    printf("%s\n", buf);

    printf("height = %i\n", Expression_height((BaseExpression*) expr));
    free(buf);
    free(expr);
    Definitions_free(definitions);
    Evaluation_free(evaluation);
    return 0;
}
