#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core/expression.h"
#include "core/definitions.h"


int main() {
    Definitions* definitions = Definitions_new(64);
    Definitions_init(definitions, NULL);  // System Definitions
    NormalExpression* expr = NormalExpression_new(2);
    expr->head = Definitions_lookup(definitions, "Plus");
    expr->leaves[0] = (BaseExpression*) Definitions_lookup(definitions, "a");
    expr->leaves[1] = (BaseExpression*) Definitions_lookup(definitions, "b");
    printf("%i\n", definitions->count);
    return 0;
}
