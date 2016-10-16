#ifndef INT_H
#define INT_H
#include <gmp.h>
#include <stdint.h>

#include "types.h"


typedef struct {
    BaseExpression base;
    int64_t value;
} MachineInteger;


typedef struct {
    BaseExpression base;
    mpz_t value;
} BigInteger;


typedef union {
    BaseExpression base;
    MachineInteger machine;
    BigInteger big;
} Integer;


MachineInteger* MachineInteger_new(void);
void MachineInteger_init(MachineInteger* p);
void MachineInteger_set(MachineInteger* p, const int64_t value);

BigInteger* BigInteger_new(void);
void BigInteger_init(BigInteger* p);
void BigInteger_set(BigInteger* p, const mpz_t value);

Integer* Integer_from_mpz(const mpz_t value);
#endif
