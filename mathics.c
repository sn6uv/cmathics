#include <stdint.h>
#include <stdio.h>


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
} ExpressionHeader;


typedef struct {
    ExpressionHeader head;
    int *value;
} MachineInteger;


MachineInteger MachineInteger_init(int value) {
    MachineInteger result = {{0, MachineIntegerType}, 0};
    result.value = &value;
    return result;
}


typedef struct {
    ExpressionHeader head;
    double *value;
} MachineReal;


MachineReal MachineReal_init(double value) {
    MachineReal result = {{0, MachineRealType}, 0};
    result.value = &value;
    return result;
}


int main() {
    MachineInteger x;
    MachineReal y;
    x = MachineInteger_init(5);
    y = MachineReal_init(1.6);
    printf("value = %i %f\n", *x.value, *y.value);
    return 0;
}
