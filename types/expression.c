#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "expression.h"
#include "symtable.h"


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


// TODO common reference
Symbol* ListSymbol(void) {
    Symbol* s = (Symbol*) malloc(sizeof(Symbol));
    s->base.ref = 0;
    s->base.type = SymbolType;
    s->name = (char*) malloc(5);
    strcpy(s->name, "List");
    s->own_values = NormalExpression_new_head(0, s);    // leaves point to self
    s->own_values = NormalExpression_new_head(0, s);
    s->sub_values = NormalExpression_new_head(0, s);
    s->up_values = NormalExpression_new_head(0, s);
    s->down_values = NormalExpression_new_head(0, s);
    s->n_values = NormalExpression_new_head(0, s);
    s->format_values = NormalExpression_new_head(0, s);
    s->default_values = NormalExpression_new_head(0, s);
    s->messages = NormalExpression_new_head(0, s);
    s->options = NormalExpression_new_head(0, s);
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
