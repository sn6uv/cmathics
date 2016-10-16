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
    Rational_clear(&q);
}


TEST(Rational, Rational_set) {
    Rational q;
    Rational_init(&q);
    mpq_t value;

    mpq_init(value);
    mpq_set_str(value, "5/7", 10);

    Rational_set(&q, value);
    EXPECT_EQ(mpq_cmp(q.value, value), 0);
    Rational_clear(&q);
}

TEST(Rational, Rational_numer) {
    Rational q;
    Integer* value;

    Rational_init(&q);
    mpq_set_si(q.value, 5, 7);

    value = Rational_numer(&q);
    EXPECT_EQ(value->base.type, MachineIntegerType);
    EXPECT_EQ(value->machine.value, 5);
    Rational_clear(&q);
}
