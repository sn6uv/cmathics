#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.c"


/*
/ HoldAll is equivalent to HoldFirst and HoldRest. We could save a couple of
/ bits here but it's not worth it because of packing.
*/


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
    // NormalExpression* own_values;
    // NormalExpression* sub_values;
    // NormalExpression* up_values;
    // NormalExpression* down_values;
    // NormalExpression* n_values;
    // NormalExpression* format_values;
    // NormalExpression* default_values;
    // NormalExpression* messages;
    // NormalExpression* options;
    void *subcode;   // XXX
    void *upcode;    // XXX
    void *downcode;  // XXX
    Attributes attributes;
} Symbol;


// FIXME need to bootstrap Symbol("List")
// NormalExpression* List_new(uint32_t argc);


Symbol* Symbol_new(const char* s) {
    Symbol* p = (Symbol*) malloc(sizeof(Symbol));
    char *name = (char*) malloc(strlen(s) + 1);
    if (p && name) {
        p->ref = 0;
        p->type = SymbolType;
        strcpy(name, s);
        p->name = name;
        /*
        p->own_values = List_new(0);
        p->sub_values = List_new(0);
        p->up_values = List_new(0);
        p->down_values = List_new(0);
        p->n_values = List_new(0);
        p->format_values = List_new(0);
        p->default_values = List_new(0);
        p->messages = List_new(0);
        p->options = List_new(0);
        */
    }
    return p;
}


void Symbol_free(Symbol* p) {
    free(p);
}
