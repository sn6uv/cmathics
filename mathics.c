#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <gmp.h>

#include "core/misc.h"
#include "core/expression.h"
#include "core/definitions.h"
#include "core/formatter.h"
#include "core/evaluation.h"
#include "core/pattern.h"
#include "core/integer.h"
#include "core/rational.h"
#include "core/arithmetic.h"


int main() {
    char* buf;
    Symbol* plus_symbol;
    Definitions* definitions = Definitions_new(64);
    Definitions_init(definitions, NULL);  // System Definitions

    Expression* expr = Expression_new(2);
    plus_symbol = Definitions_lookup(definitions, "Plus");

    BaseExpression* head = (BaseExpression*) plus_symbol;
    BaseExpression* la = (BaseExpression*) Definitions_lookup(definitions, "a");
    BaseExpression* lb = (BaseExpression*) Definitions_lookup(definitions, "b");
    BaseExpression* leaves[2];
    leaves[0] = la;
    leaves[1] = lb;
    Expression_set(expr, head, leaves);

    Evaluation* evaluation = Evaluation_new(definitions, true);
    plus_symbol->down_code = _Plus;

    buf = FullForm((BaseExpression*) expr);
    printf("%s\n", buf);

    printf("evaluating...\n");
    BaseExpression* result = Evaluate(evaluation, (BaseExpression*) expr);
    printf("done\n");

    buf = FullForm((BaseExpression*) result);
    printf("%s\n", buf);

    // printf("height = %li\n", Expression_height((BaseExpression*) expr));
    // printf("hash = %lu\n", expr->hash);

    free(buf);
    free(expr);
    Definitions_free(definitions);
    Evaluation_free(evaluation);


    return 0;
}
