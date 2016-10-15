#include <stdlib.h>
#include <gtest/gtest.h>
#include <mpfr.h>

extern "C" {
    #include "core/types.h"
    #include "core/real.h"
    #include "core/integer.h"
}


TEST(MachineReal, MachineReal_init) {
    MachineReal p;
    MachineReal_init(&p);
    EXPECT_EQ(p.base.type, MachineRealType);
    EXPECT_EQ(p.base.ref, 0);
    EXPECT_EQ(p.value, 0.0);
}


TEST(MachineReal, MachineReal_set) {
    MachineReal p;
    MachineReal_init(&p);
    MachineReal_set(&p, 1.5);
    EXPECT_EQ(p.value, 1.5);
}


TEST(MachineReal, MachineReal_from_d) {
    MachineReal* p = MachineReal_from_d(1.5);
    EXPECT_EQ(p->base.type, MachineRealType);
    EXPECT_EQ(p->base.ref, 0);
    EXPECT_EQ(p->value, 1.5);
}

TEST(BigReal, BigReal_init) {
    BigReal p;
    BigReal_init(&p, 123.5);
    EXPECT_EQ(p.base.type, BigRealType);
    EXPECT_EQ(p.base.ref, 0);
    ASSERT_TRUE(p.value != NULL);
    EXPECT_EQ(mpfr_cmp_d(p.value, 0.0), 0);
    EXPECT_EQ(p.prec, 123.5);
    EXPECT_EQ(mpfr_get_prec(p.value), 411);
    EXPECT_TRUE(mpfr_nan_p(p.value) != 0);
}


TEST(BigReal, BigReal_set) {
    BigReal p;
    BigReal_init(&p, 30.0);
    BigReal_set_d(&p, 1.5);
    EXPECT_EQ(mpfr_get_d(p.value, MPFR_RNDN), 1.5);
}


TEST(PrecisionOf, MachineReal) {
    MachineReal p;
    double prec;
    int32_t ret_code;
    MachineReal_init(&p);
    MachineReal_set(&p, 1.5);
    ret_code = PrecisionOf((BaseExpression*) &p, &prec);
    EXPECT_EQ(ret_code, 1);
    EXPECT_EQ(prec, 0.0);
}


TEST(PrecisionOf, BigReal) {
    BigReal p;
    double prec;
    int32_t ret_code;
    BigReal_init(&p, 30.0);
    BigReal_set_d(&p, 1.5);
    ret_code = PrecisionOf((BaseExpression*) &p, &prec);
    EXPECT_EQ(ret_code, 2);
    EXPECT_EQ(prec, 30.0);
}


TEST(PrecisionOf, MachineInteger) {
    MachineInteger p;
    double prec;
    int32_t ret_code;
    MachineInteger_init(&p);
    MachineInteger_set(&p, 5);
    ret_code = PrecisionOf((BaseExpression*) &p, &prec);
    EXPECT_EQ(ret_code, 0);
}


TEST(PrecisionOf, BigInteger) {
    BigInteger p;
    double prec;
    int32_t ret_code;
    mpz_t value;

    mpz_init_set_si(value, 5);

    BigInteger_init(&p);
    BigInteger_set(&p, value);

    ret_code = PrecisionOf((BaseExpression*) &p, &prec);
    EXPECT_EQ(ret_code, 0);

    mpz_clear(value);
}


// TODO
TEST(PrecisionOf, Rational) {
}


// TODO
TEST(PrecisionOf, Complex) {
}


// TODO
TEST(PrecisionOf, Expression) {
}


// TODO
TEST(PrecisionOf, Symbol) {
}


// TODO
TEST(PrecisionOf, String) {
}


// TODO
TEST(PrecisionOf, RawExpression) {
}
