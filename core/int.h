#ifndef INT_H
#define INT_H
#include "types.h"


typedef struct {
    BaseExpression base;
    int* value;
} MachineInteger;


typedef struct {
    BaseExpression base;
    void* value;
    double precision;
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

#endif
