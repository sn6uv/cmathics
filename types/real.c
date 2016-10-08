typedef struct {
    uint32_t ref;
    Type type;
    double* value;
} MachineReal;


MachineReal* MachineReal_new(double* value) {
    MachineReal* p = (MachineReal*) malloc(sizeof(MachineReal));
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


