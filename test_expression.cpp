#include <gtest/gtest.h>


extern "C" {
    #include "types/symtable.h"
    #include "types/expression.h"
}


TEST(Symbol, new) {
    Symbol* s = Symbol_new("a");
    ASSERT_TRUE(s != NULL);
    EXPECT_STREQ(s->name, "a");
    Symbol_free(s);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
