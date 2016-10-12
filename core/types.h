#ifndef TYPES_H
#define TYPES_H
#include <stdint.h>


#define TYPE_PAIR(X, Y) ((int) X) << 4 | (int) Y


typedef enum {
    MachineIntegerType,
    BigIntegerType,
    MachineRealType,
    BigRealType,
    RationalType,
    ComplexType,
    ExpressionType,
    SymbolType,
    StringType,
    RawExpressionType
} Type;


typedef struct {
    uint32_t ref;
    Type type;
} BaseExpression;
#endif
