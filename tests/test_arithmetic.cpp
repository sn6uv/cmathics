#include <stdlib.h>
#include <gmpxx.h>
#include <gtest/gtest.h>


extern "C" {
    #include "core/types.h"
    #include "core/integer.h"
    #include "core/arithmetic.h"
    #include "core/definitions.h"
}


TEST(Arithmetic, Plus) {
    // initialize arguments
    MachineInteger a;
    MachineInteger b;
    MachineInteger* c;
    MachineInteger_init(&a);
    MachineInteger_init(&b);
    MachineInteger_set(&a, 1);
    MachineInteger_set(&b, 2);

    // get plus head
    Definitions* definitions = Definitions_new(64);
    Definitions_init(definitions, NULL);  // System Definitions
    Expression* plus_expr = Expression_new(2);
    BaseExpression* plus_head = (BaseExpression*) Definitions_lookup(definitions, "Plus");

    // construct expression
    plus_expr = Expression_new(2);
    BaseExpression* leaves[2];
    leaves[0] = (BaseExpression*) &a;
    leaves[1] = (BaseExpression*) &b;
    Expression_set(plus_expr, plus_head, leaves);

    BaseExpression* result_expr = Eval_Plus(plus_expr);
    ASSERT_EQ(result_expr->type, MachineIntegerType);
    c = (MachineInteger*) result_expr;
    EXPECT_EQ(c->value, 3);
}


