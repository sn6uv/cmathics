#include <stdlib.h>
#include <gmpxx.h>
#include <gtest/gtest.h>


extern "C" {
    #include "core/types.h"
    #include "core/integer.h"
}


TEST(MachineInteger, MachineInteger_new) {
    MachineInteger* p;
    p = MachineInteger_new();
    ASSERT_TRUE(p != NULL);
    EXPECT_EQ(p->base.type, MachineIntegerType);
    EXPECT_EQ(p->base.ref, 0);
    EXPECT_EQ(p->value, 0);
    MachineInteger_free(p);
}


TEST(MachineInteger, MachineInteger_set) {
    MachineInteger* p;
    p = MachineInteger_new();
    ASSERT_TRUE(p != NULL);
    MachineInteger_set(p, 2);
    EXPECT_EQ(p->value, 2);
    MachineInteger_set(p, -5);
    EXPECT_EQ(p->value, -5);
    MachineInteger_free(p);
}


TEST(BigInteger, BigInteger_new) {
    BigInteger* p;
    p = BigInteger_new();
    ASSERT_TRUE(p != NULL);
    EXPECT_EQ(p->base.type, BigIntegerType);
    EXPECT_EQ(p->base.ref, 0);
    EXPECT_EQ(mpz_cmp_si(p->value, 0), 0);
    BigInteger_free(p);
}


TEST(BigInteger, BigInteger_set__small) {
    BigInteger* p;
    mpz_t value;
    p = BigInteger_new();
    mpz_init_set_si(value, 5);

    BigInteger_set(p, value);
    EXPECT_EQ(mpz_cmp_si(p->value, 5), 0);

    // ensure independent of original mpz_t
    mpz_set_si(value, 6);
    EXPECT_EQ(mpz_cmp_si(p->value, 5), 0);
    mpz_clear(value);
    EXPECT_EQ(mpz_cmp_si(p->value, 5), 0);
    BigInteger_free(p);
}

TEST(BigInteger, BigInteger_set__big) {
    BigInteger* p;
    mpz_t value;
    const char* hex_value = "f752d912b1bd0ed02b0632469e0bf641ca52f36d0b4cbda9c1051ff2975b515fce7b0c9";
    p = BigInteger_new();
    mpz_init_set_si(value, 41);
    mpz_pow_ui(value, value, 53);  // overflows 64bit int for sure
    ASSERT_STREQ(mpz_get_str(NULL, 16, value), hex_value);
    BigInteger_set(p, value);
    EXPECT_EQ(mpz_cmp(p->value, value), 0);
    mpz_set_si(value, 0);
    ASSERT_STREQ(mpz_get_str(NULL, 16, p->value), hex_value);
    mpz_clear(value);
    ASSERT_STREQ(mpz_get_str(NULL, 16, p->value), hex_value);
    BigInteger_free(p);
}


TEST(Integer, Integer_new_from_mpz__small) {
    Integer* p;
    mpz_t value;
    mpz_init(value);
    mpz_set_si(value, 5);
    p = Integer_new_from_mpz(value);
    ASSERT_TRUE(p != NULL);
    ASSERT_EQ(p->base.type, MachineIntegerType);
    EXPECT_EQ(p->machine.value, 5);
    mpz_clear(value);
    EXPECT_EQ(p->machine.value, 5);
    free(p);
}


TEST(Integer, Integer_new_from_mpz__big) {
    Integer* p;
    mpz_t value;
    mpz_init(value);
    const char* hex_value = "f752d912b1bd0ed02b0632469e0bf641ca52f36d0b4cbda9c1051ff2975b515fce7b0c9";
    mpz_init_set_si(value, 41);
    mpz_pow_ui(value, value, 53);  // overflows 64bit int for sure
    p = Integer_new_from_mpz(value);
    ASSERT_TRUE(p != NULL);
    ASSERT_EQ(p->base.type, BigIntegerType);
    EXPECT_STREQ(mpz_get_str(NULL, 16, p->big.value), hex_value);
    mpz_clear(value);
    EXPECT_STREQ(mpz_get_str(NULL, 16, p->big.value), hex_value);
    free(p);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
