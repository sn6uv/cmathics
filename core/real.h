#ifndef REAL_H
#define REAL_H
#include <mpfr.h>
#include <stdint.h>

#include "types.h"


typedef struct {
    BaseExpression base;
    double value;
} MachineReal;


typedef struct {
    BaseExpression base;
    mpfr_t value;
    double prec;
} BigReal;


void MachineReal_init(MachineReal* p);
void MachineReal_set(MachineReal* p, const double value);
MachineReal* MachineReal_from_d(const double value);


void BigReal_init(BigReal* p, const double prec);
void BigReal_set_d(BigReal* p, const double value);
void BigReal_clear(BigReal* p);

int32_t PrecisionOf(BaseExpression*, double* result);
#endif
