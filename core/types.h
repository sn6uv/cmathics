#ifndef TYPES_H
#define TYPES_H
#include <stdint.h>


typedef enum {
    MachineIntegerType,
    BigIntegerType,
    MachineRealType,
    BigRealType,
    RationalType,
    ComplexType,
    NormalExpressionType,
    SymbolType,
    StringType,
    RawExpressionType
} Type;


typedef struct {
    uint32_t ref;
    Type type;
} BaseExpression;
#endif
