#ifndef REAL_H
#define REAL_H
#include <mpfr.h>

#include "types.h"


typedef struct {
    BaseExpression base;
    double* value;
} MachineReal;


typedef struct {
    BaseExpression base;
    mpfr_t value;
} BigReal;


void MachineReal_init(MachineReal* p);
void MachineReal_set(MachineReal* p, const double value);


void BigReal_init(BigReal* p, const mpfr_prec_t prec);
void BigReal_set(BigReal* p, const double value);
void BigReal_clear(BigReal* p);
#endif
