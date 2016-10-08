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
    void* value;
    double precision;
} BigInteger;


typedef union {
    MachineInteger machine;
    BigInteger big;
} Integer;


typedef struct {
    uint32_t ref;
    Type type;
    Integer* numer;
    Integer* denom;
} Rational;


// typedef struct {
//     uint32_t ref;
//     Type type;
//     char *name;
// } Symbol;


typedef struct {
    uint32_t ref;
    Type type;
    uint32_t last_evaluated;
    uint32_t hash;
    uint32_t argc;
    void* head;
    void* leaves[];  // zero length array of pointers
} NormalExpression;


NormalExpression* NormalExpression_new(uint32_t hash, uint32_t argc) {
    NormalExpression* p = malloc(sizeof(NormalExpression) + argc * sizeof(void*));
    if (p) {
        p->ref = 0;
        p->type = NormalExpressionType;
        p->hash = hash;
        p->argc = argc;
    }
    return p;
}

void NormalExpression_free(NormalExpression* p) {
    free(p);
}


typedef enum {
    None,
    First,
    Rest,
    All
} __attribute__((packed)) HoldAttribute;


typedef struct {
    // pattern matching attributes
    unsigned int is_orderless: 1;
    unsigned int is_flat: 1;
    unsigned int is_oneidentity: 1;
    unsigned int is_listable: 1;
    // calculus attributes
    unsigned int is_constant: 1;
    unsigned int is_numericfunction: 1;
    // rw attributes
    unsigned int is_protected: 1;
    unsigned int is_locked: 1;
    unsigned int is_readprotected: 1;
    // evaluation attributes
    HoldAttribute hold;
    HoldAttribute nhold;
    // misc attributes
    unsigned int is_holdallcomplete: 1;
    unsigned int is_sequencehold: 1;
    unsigned int is_temporary: 1;
    unsigned int is_stub: 1;
} Attributes;


typedef struct {
    uint32_t ref;
    Type type;
    char* name;
    NormalExpression* own_values;
    NormalExpression* sub_values;
    NormalExpression* up_values;
    NormalExpression* down_values;
    NormalExpression* n_values;
    NormalExpression* format_values;
    NormalExpression* default_values;
    NormalExpression* messages;
    NormalExpression* options;
    void *subcode;   // XXX
    void *upcode;    // XXX
    void *downcode;  // XXX
    Attributes attributes;
} Symbol;


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
