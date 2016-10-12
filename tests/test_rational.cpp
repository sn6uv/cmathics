#include <stdlib.h>
#include <gtest/gtest.h>
#include <gmpxx.h>

extern "C" {
    #include "core/rational.h"
    #include "core/int.h"
}


TEST(Rational, Rational_new) {
    Rational* q;
    q = Rational_new();
    EXPECT_TRUE(q != NULL);
    Rational_free(q);
}

TEST(Rational, Rational_set) {
    Rational* q;
    MachineInteger* numer;
    MachineInteger* denom;
    q = Rational_new();
    numer = MachineInteger_new();
    denom = MachineInteger_new();
    MachineInteger_set(numer, 5);
    MachineInteger_set(denom, 7);

    Rational_set(q, (Integer*) numer, (Integer*) denom);

    EXPECT_EQ(numer->base.ref, 1);
    EXPECT_EQ(denom->base.ref, 1);

    Rational_free(q);
    EXPECT_TRUE(numer == NULL);
    EXPECT_TRUE(denom == NULL);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
