#ifndef STRING_H
#define STRING_H
#include "types.h"


typedef struct {
    BaseExpression base;
    char* value;
    uint32_t length;
} String;
#endif
