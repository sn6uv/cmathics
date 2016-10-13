#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "definitions.h"
#include "expression.h"
#include "integer.h"
#include "hash.h"


// required for bootstrapping
static Expression* EmptyList;


// initialise a definition entry
void Symbol_init(Symbol* d, const char* name) {
    d->name = (char*) malloc(strlen(name) + 1);
    if (d->name) {
        strcpy(d->name, name);
    }
    d->base.ref = 0;
    d->base.type = SymbolType;
    d->own_values = EmptyList;
    d->sub_values = EmptyList;
    d->up_values = EmptyList;
    d->down_values = EmptyList;
    d->n_values = EmptyList;
    d->format_values = EmptyList;
    d->default_values = EmptyList;
    d->messages = EmptyList;
    d->options = EmptyList;
    return;
}


Definitions* Definitions_new(uint32_t size) {
    Definitions* d;
    uint32_t i;

    if (size < 1)
        return NULL;

    d = (Definitions*) malloc(sizeof(Definitions));
    if (d == NULL)
        return NULL;

    d->table = (Symbol*) malloc(sizeof(Symbol) * size);
    if (d->table == NULL)
        return NULL;

    for (i = 0; i < size; i++)
        d->table[i].name = NULL;

    d->size = size;
    d->count = 0;

    return d;
}


void Definitions_init(Definitions* d, Definitions* system_definitions) {
    uint32_t bin;
    Symbol* list_defn;

    if (system_definitions == NULL) {   // this is the system definitions
        // add the `List` entry
        bin = djb2("List") % (d->size);
        list_defn = &(d->table[bin]);
        assert(list_defn->name == NULL);
        Symbol_init(list_defn, "List");
        d->count++;

        // construct common `List[]` for bootstrapping
        if (EmptyList == NULL) {
            EmptyList = Expression_new(0);
            Expression_init(EmptyList, (BaseExpression*) list_defn, NULL);
        }
        EmptyList->base.ref++;
    }
}


void Definitions_free(Definitions* d) {
    uint32_t i;
    for (i=0; i<d->size; i++) {
        if (d->table[i].name != NULL) {
            free(d->table[i].name);
        }
    }
    free(d->table);
    free(d);
    if (EmptyList != NULL && --EmptyList->base.ref == 0) {
        Expression_free(EmptyList);
        EmptyList = NULL;
    }
}


Symbol* Definitions_lookup(Definitions* d, const char* name) {
    uint32_t bin;
    Symbol* result;

    // linear probing
    bin = djb2(name) % (d->size);

    while (d->table[bin].name != NULL && strcmp(d->table[bin].name, name) != 0) {
        bin = (bin + 1) % (d->size);
    }

    result = &(d->table[bin]);
    if (result->name == NULL) {
        Symbol_init(result, name);
        d->count++;
    }

    if (result->name == NULL) {
        return NULL;
    }
    return result;
}
