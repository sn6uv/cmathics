#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
    NormalExpression* p = (NormalExpression*) malloc(sizeof(NormalExpression) + argc * sizeof(void*));
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
