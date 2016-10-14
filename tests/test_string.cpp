#include <stdlib.h>
#include <gtest/gtest.h>


extern "C" {
    #include "core/types.h"
    #include "core/string.h"
}


TEST(String, String_new) {
    String* p;
    p = String_new(2);
    EXPECT_TRUE(p != NULL);
    String_free(p);
}


TEST(String, String_init) {
    String p;
    String_init(&p, 5);
    EXPECT_EQ(p.base.type, StringType);
    EXPECT_EQ(p.base.ref, 0);
    EXPECT_EQ(p.length, 5);
}


TEST(String, String_set) {
    String p;
    String_init(&p, 5);
    String_set(&p, "abcde");
    EXPECT_STREQ(p.value, "abcde");
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
