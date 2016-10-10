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


MachineReal* MachineReal_new(void);
void MachineReal_set(MachineReal* p, double value);
void MachineReal_free(MachineReal* p);

BigReal* BigReal_new(mpfr_prec_t prec);
void BigReal_set_d(BigReal* p, double value);
void BigReal_free(BigReal* p);
#endif
