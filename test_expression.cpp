#include "types/expression.h"
#include <gtest/gtest.h>


TEST(Symbol, Symbol_new) {
    Symbol* s = Symbol_new("a");
    ASSERT_TRUE(s != NULL);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
