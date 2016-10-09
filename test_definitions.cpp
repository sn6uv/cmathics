#include <stdlib.h>
#include <gtest/gtest.h>

extern "C" {
    #include "types/definitions.h"
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


TEST(Definitions, lookup) {
    Definitions* d = Definitions_new(32);
    Definition* s = Definitions_lookup(d, "abc");
    ASSERT_TRUE(s != NULL);
    EXPECT_STREQ(s->name, "abc");
    EXPECT_EQ(d->size, 32);
    EXPECT_EQ(d->count, 1);
    Definitions_free(d);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
