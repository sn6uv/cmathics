#include "types.h"


typedef struct {
    BaseExpression base;
    char* value;
    uint32_t length;
} String;
