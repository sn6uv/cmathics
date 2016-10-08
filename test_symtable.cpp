#include <stdlib.h>
#include "symtable.c"
#include <gtest/gtest.h>


TEST(Symbol_Definitions, new32) {
    Definitions* d = Definitions_new(32);
    ASSERT_TRUE(d != NULL);
    EXPECT_EQ(d->size, 32);
    EXPECT_EQ(d->count, 0);
}


TEST(Symbol_Definitions, new0) {
    Definitions* d = Definitions_new(0);
    ASSERT_TRUE(d == NULL);
}


TEST(Symbol_Definitions, set) {
    Definitions* d = Definitions_new(32);
    Symbol* s = Symbol_new("abc");
    Definitions_set(d, s);
    EXPECT_EQ(d->size, 32);
    EXPECT_EQ(d->count, 1);
}


TEST(Symbol_Definitions, get) {
    Definitions* d = Definitions_new(32);
    Symbol* s = Symbol_new("abc");
    Definitions_set(d, s);
    Symbol* t = Definitions_get(d, "abc");
    EXPECT_EQ(d->size, 32);
    EXPECT_EQ(d->count, 1);
    ASSERT_TRUE(t != NULL);
    EXPECT_EQ(t->type, SymbolType);
    EXPECT_STREQ(t->name, "abc");
}


TEST(Symbol_Definitions, get_NULL) {
    Definitions* d = Definitions_new(32);
    Symbol* t = Definitions_get(d, "abc");
    EXPECT_EQ(d->size, 32);
    EXPECT_EQ(d->count, 0);
    ASSERT_TRUE(t == NULL);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
