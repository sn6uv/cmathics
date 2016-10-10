#ifndef INT_H
#define INT_H
#include <gmp.h>
#include "types.h"


typedef struct {
    BaseExpression base;
    int value;
} MachineInteger;


typedef struct {
    BaseExpression base;
    mpz_t value;
} BigInteger;


typedef union {
    MachineInteger machine;
    BigInteger big;
} Integer;


typedef struct {
    BaseExpression base;
    Integer* numer;
    Integer* denom;
} Rational;


MachineInteger* MachineInteger_new(void);
void MachineInteger_set(MachineInteger* p, int value);
void MachineInteger_free(MachineInteger* p);
#endif
