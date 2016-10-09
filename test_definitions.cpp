#include <stdlib.h>
#include <gtest/gtest.h>

extern "C" {
    #include "core/definitions.h"
    #include "core/expression.h"
}


TEST(Definitions, new32) {
    Definitions* d = Definitions_new(32);
    ASSERT_TRUE(d != NULL);
    EXPECT_EQ(d->size, 32);
    EXPECT_EQ(d->count, 0);
    Definitions_free(d);
}


TEST(Definitions, new0) {
    Definitions* d = Definitions_new(0);
    EXPECT_TRUE(d == NULL);
}


TEST(Definitions, init) {
    Definitions* d = Definitions_new(32);
    Definitions_init(d, NULL);  // System Definitions
    EXPECT_EQ(d->size, 32);
    EXPECT_EQ(d->count, 1);
    ASSERT_TRUE(d->EmptyList != NULL);
    Definition* l = Definitions_lookup(d, "List");
    ASSERT_TRUE(l != NULL);
    EXPECT_STREQ(l->name, "List");
    EXPECT_EQ(d->EmptyList->head, l);
    Definitions_free(d);
}


TEST(Definitions, lookup) {
    Definitions* d = Definitions_new(32);
    Definition* s = Definitions_lookup(d, "abc");
    ASSERT_TRUE(s != NULL);
    EXPECT_STREQ(s->name, "abc");
    EXPECT_EQ(d->size, 32);
    EXPECT_EQ(d->count, 1);
    Definitions_free(d);
}


TEST(Definitions, lookup_twice) {
    Definitions* d = Definitions_new(32);
    Definition* s1 = Definitions_lookup(d, "abc");
    Definition* s2 = Definitions_lookup(d, "abc");
    ASSERT_TRUE(s1 != NULL);
    ASSERT_TRUE(s2 != NULL);
    EXPECT_EQ(s1, s2);
    EXPECT_EQ(d->size, 32);
    EXPECT_EQ(d->count, 1);
    Definitions_free(d);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
