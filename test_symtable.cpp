#include <stdlib.h>
#include "symtable.c"
#include <gtest/gtest.h>


TEST(Symbol_Definitions, new32) {
    Definitions* d = Definitions_new(32);
    ASSERT_TRUE(d != NULL);
    EXPECT_EQ(d->size, 32);
    EXPECT_EQ(d->count, 0);
    Definitions_free(d);
}


TEST(Symbol_Definitions, new0) {
    Definitions* d = Definitions_new(0);
    EXPECT_TRUE(d == NULL);
}


TEST(Symbol_Definitions, set) {
    Definitions* d = Definitions_new(32);
    Symbol* s = Symbol_new("abc");
    Definitions_set(d, s);
    EXPECT_EQ(d->size, 32);
    EXPECT_EQ(d->count, 1);
    Definitions_free(d);
}

TEST(Symbol_Definitions, set_no_collision) {
    ASSERT_NE(Definitions_hash("a", 2), Definitions_hash("b", 2));
    Definitions* d = Definitions_new(2);
    Symbol* s1 = Symbol_new("a");
    Symbol* s2 = Symbol_new("b");
    Definitions_set(d, s1);
    Definitions_set(d, s2);
    EXPECT_EQ(d->size, 2);
    EXPECT_EQ(d->count, 2);
    Definitions_free(d);
}


TEST(Symbol_Definitions, set_collision_overwrite) {
    ASSERT_EQ(Definitions_hash("a", 2), Definitions_hash("a", 2));
    Definitions* d = Definitions_new(2);
    Symbol* s1 = Symbol_new("a");
    Symbol* s2 = Symbol_new("a");
    Definitions_set(d, s1);
    Definitions_set(d, s2);
    EXPECT_EQ(d->size, 2);
    EXPECT_EQ(d->count, 1); // same key so overwrite
    Definitions_free(d);
}


TEST(Symbol_Definitions, set_collision_no_overwrite) {
    ASSERT_EQ(Definitions_hash("a", 2), Definitions_hash("c", 2));
    Definitions* d = Definitions_new(2);
    Symbol* s1 = Symbol_new("a");
    Symbol* s2 = Symbol_new("c");
    Definitions_set(d, s1);
    Definitions_set(d, s2);
    EXPECT_EQ(d->size, 2);
    EXPECT_EQ(d->count, 2); // different key so don't overwrite
    Definitions_free(d);
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
    Definitions_free(d);
}


TEST(Symbol_Definitions, get_NULL) {
    Definitions* d = Definitions_new(32);
    Symbol* t = Definitions_get(d, "abc");
    EXPECT_EQ(d->size, 32);
    EXPECT_EQ(d->count, 0);
    ASSERT_TRUE(t == NULL);
    Definitions_free(d);
}


TEST(Symbol_Definitions, get_collision) {
    ASSERT_EQ(Definitions_hash("a", 2), Definitions_hash("c", 2));
    Definitions* d = Definitions_new(2);
    Symbol* s1 = Symbol_new("a");
    Symbol* s2 = Symbol_new("c");
    Definitions_set(d, s1);
    Definitions_set(d, s2);
    Symbol* t1 = Definitions_get(d, "a");
    Symbol* t2 = Definitions_get(d, "c");
    ASSERT_TRUE(t1 != NULL);
    EXPECT_STREQ(t1->name, "a");
    ASSERT_TRUE(t2 != NULL);
    EXPECT_STREQ(t2->name, "c");
    EXPECT_EQ(d->count, 2);
    Definitions_free(d);
}


TEST(Symbol_Definitions, get_collision_NULL) {
    Definitions* d = Definitions_new(2);
    Symbol* s = Symbol_new("a");
    Definitions_set(d, s);
    Symbol* t = Definitions_get(d, "c");
    EXPECT_TRUE(t == NULL);
    EXPECT_EQ(d->count, 1);
    Definitions_free(d);
}


TEST(Symbol_Definitions, set_FULL) {
    Definitions* d = Definitions_new(32);
    for (int i = 0; i < 32; i++) {
        Symbol* s = Symbol_new("abc");
    }
    Definitions_free(d);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
