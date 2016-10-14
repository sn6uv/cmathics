#include <stdlib.h>
#include <gtest/gtest.h>
#include <gmpxx.h>

extern "C" {
    #include "core/types.h"
    #include "core/integer.h"
    #include "core/rational.h"
}


TEST(Rational, Rational_init) {
    Rational q;
    Rational_init(&q);
    EXPECT_EQ(q.base.type, RationalType);
    EXPECT_EQ(q.base.ref, 0);
    EXPECT_TRUE(q.numer == NULL);
    EXPECT_TRUE(q.denom == NULL);
}

TEST(Rational, Rational_set) {
    Rational* q;
    q = (Rational*) malloc(sizeof(Rational));
    MachineInteger numer;
    MachineInteger denom;
    Rational_init(q);
    MachineInteger_init(&numer);
    MachineInteger_init(&denom);
    MachineInteger_set(&numer, 5);
    MachineInteger_set(&denom, 7);

    Rational_set(q, (Integer*) &numer, (Integer*) &denom);

    EXPECT_EQ(numer.base.ref, 1);
    EXPECT_EQ(denom.base.ref, 1);
}
