typedef struct {
    uint32_t ref;
    Type type;
    int* value;
} MachineInteger;


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


MachineInteger* MachineInteger_new(int* value) {
    MachineInteger* p = (MachineInteger*) malloc(sizeof(MachineInteger));
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
