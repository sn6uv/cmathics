#include <gtest/gtest.h>


extern "C" {
    #include "types/expression.h"
}


TEST(Symbol_test, new) {
    char name[] = "List";
    Symbol* symb = Symbol_new(name);
    EXPECT_EQ(strlen(symb->name), 4);
    for (int i=0; i<5; i++)
        EXPECT_EQ(symb->name[i], name[i]);
    Symbol_free(symb);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
