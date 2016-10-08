#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


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
    int* value;
} MachineInteger;


MachineInteger* MachineInteger_new(int* value) {
    MachineInteger* p = malloc(sizeof(MachineInteger));
    if (p) {
        p->ref = 0;
        p->type = MachineIntegerType;
        p->value = value;
    }
    return p;
}


void MachineInteger_free(MachineInteger* p) {
    free(p);
}


typedef struct {
    uint32_t ref;
    Type type;
    double* value;
} MachineReal;


MachineReal* MachineReal_new(double* value) {
    MachineReal* p = malloc(sizeof(MachineReal));
    if (p) {
        p->ref = 0;
        p->type = MachineRealType;
        p->value = value;
    }
    return p;
}


void MachineReal_free(MachineReal* p) {
    free(p);
}


typedef struct {
    uint32_t ref;
    Type type;
    char* value;
    uint32_t length;
} String;


String* String_new(char* value, uint32_t length) {
    String* p = malloc(sizeof(String));
    if (p) {
        p->ref = 0;
        p->type = StringType;
        p->value = value;
        p->length = length;
    }
    return p;
}


void String_free(String* p) {
    free(p);
}


int main() {
    MachineReal* yp;
    MachineInteger* xp;
    String* zp;

    int* z = malloc(sizeof(int));
    double *y = malloc(sizeof(double));
    *z = 5;
    *y = 1.6;
    xp = MachineInteger_new(z);
    yp = MachineReal_new(y);
    zp = String_new("abc", 3);

    printf("value = %f\n", *yp->value);

    free(z);
    free(y);
    MachineInteger_free(xp);
    MachineReal_free(yp);
    String_free(zp);
    return 0;
}
