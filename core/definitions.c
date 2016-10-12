#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "definitions.h"
#include "expression.h"
#include "int.h"
#include "hash.h"


// initialise a definition entry
void Symbol_init(Symbol* d, const char* name, Expression* EmptyList) {
    d->name = (char*) malloc(strlen(name) + 1);
    if (d != NULL) {
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
    Expression* EmptyList;

    if (system_definitions == NULL) {   // this is the system definitions
        // add the `List` entry
        bin = djb2("List") % (d->size);
        list_defn = &(d->table[bin]);
        assert(list_defn->name == NULL);
        Symbol_init(list_defn, "List", NULL);
        d->count++;

        // construct common `List[]` for bootstrapping
        EmptyList = Expression_new(0);
        Expression_init(EmptyList, (BaseExpression*) list_defn, NULL);
    } else {
        EmptyList = system_definitions->EmptyList;
    }

    // assign EmptyList pointer
    d->EmptyList = EmptyList;
}


void Definitions_free(Definitions* d) {
    uint32_t i;
    for (i=0; i<d->size; i++) {
        if (d->table[i].name != NULL) {
            free(d->table[i].name);
        }
    }
    free(d->table);
    if (d->EmptyList != NULL) {
        free(d->EmptyList);
    }
    free(d);
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
        Symbol_init(result, name, d->EmptyList);
        d->count++;
    }

    if (result->name == NULL) {
        return NULL;
    }
    return result;
}


int64_t* get_int_value(Definitions* definitions, const char* name) {
    Symbol* definition;
    Expression* values;
    BaseExpression* value;
    MachineInteger* int_value;

    definition = Definitions_lookup(definitions, name);
    if (definition == NULL) {
        return NULL;
    }

    values = definition->own_values;
    if (values == NULL) {
        return NULL;
    }

    if (values->argc < 1) {
        return NULL;
    }

    // take first own value
    value = values->leaves[0];
    if (value->type != MachineIntegerType) {
        return NULL;
    }

    int_value = (MachineInteger*) value;
    return &(int_value->value);
}


void insert_rule(Expression* rules, BaseExpression* rule) {
    // TODO
    return;
}


int64_t* set_int_value(Definitions* definitions, const char* name, int64_t value) {
    Symbol* definition;
    MachineInteger* result;

    definition = Definitions_lookup(definitions, name);
    if (definition == NULL) {
        return NULL;
    }

    result = MachineInteger_new();
    if (result == NULL) {
        return NULL;
    }

    MachineInteger_set(result, value);

    insert_rule(definition->own_values, (BaseExpression*) result);

    if (definition->own_values->argc < 1) {
        return NULL;
    }

    return &(result->value);
}
