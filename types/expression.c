#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "expression.h"


NormalExpression* NormalExpression_new(uint32_t argc) {
    uint32_t hash;
    hash = 0;   // TODO
    NormalExpression* p = (NormalExpression*) malloc(sizeof(NormalExpression) + argc * sizeof(void*));
    if (p) {
        p->base.ref = 0;
        p->base.type = NormalExpressionType;
        p->hash = hash;
        p->argc = argc;
    }
    return p;
}


NormalExpression* NormalExpression_new_head(uint32_t argc, Symbol* head) {
    NormalExpression* result = NormalExpression_new(argc);
    if (result) {
        result->head = head;
    }
    return result;
}


void NormalExpression_free(NormalExpression* p) {
    free(p);
}


Symbol* Symbol_new(const char* s) {
    Symbol* p = (Symbol*) malloc(sizeof(Symbol));
    char *name = (char*) malloc(strlen(s) + 1);
    if (p && name) {
        p->base.ref = 0;
        p->base.type = SymbolType;
        strcpy(name, s);
        p->name = name;
    }
    return p;
}


void Symbol_free(Symbol* p) {
    free(p);
}


// TODO common reference
Symbol* ListSymbol(void) {
    Symbol* s = (Symbol*) malloc(sizeof(Symbol));
    s->base.ref = 0;
    s->base.type = SymbolType;
    s->name = (char*) malloc(5);
    strcpy(s->name, "List");
    return s;
}


NormalExpression* List_new(uint32_t length) {
    NormalExpression* result;
    result = NormalExpression_new(length);
    if (result) {
        result->head = ListSymbol();
    }
    return result;
}
