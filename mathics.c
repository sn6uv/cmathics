#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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


NormalExpression* NormalExpression_new(uint32_t argc) {
    uint32_t hash;
    hash = 0;   // TODO
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
    // evaluation hold attributes
    unsigned int is_holdfirst: 1;
    unsigned int is_holdrest: 1;
    unsigned int is_holdall: 1;
    unsigned int is_holdallcomplete: 1;
    // evaluation nhold attributes
    unsigned int is_nholdfirst: 1;
    unsigned int is_nholdrest: 1;
    unsigned int is_nholdall: 1;
    // misc attributes
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


NormalExpression* List_new(uint32_t argc);


Symbol* Symbol_new(const char* s) {
    Symbol* p = malloc(sizeof(Symbol));
    char *name = malloc(strlen(s) + 1);
    if (p && name) {
        p->ref = 0;
        p->type = SymbolType;
        strcpy(name, s);
        p->name = name;
        p->own_values = List_new(0);
        p->sub_values = List_new(0);
        p->up_values = List_new(0);
        p->down_values = List_new(0);
        p->n_values = List_new(0);
        p->format_values = List_new(0);
        p->default_values = List_new(0);
        p->messages = List_new(0);
        p->options = List_new(0);
    }
    return p;
}


void Symbol_free(Symbol* p) {
    free(p);
}


NormalExpression* List_new(uint32_t argc) {
    Symbol* head = Symbol_new("List");
    NormalExpression* expr = NormalExpression_new(argc);
    if (head && expr) {
        expr->head = head;
    }
    return expr;
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
