#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "definitions.h"
#include "expression.h"
#include "int.h"


// initialise a definition entry
void Definition_init(Definition* d, const char* name, NormalExpression* EmptyList) {
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

    d->table = (Definition*) malloc(sizeof(Definition) * size);
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
    Definition* list_defn;
    NormalExpression* EmptyList;

    if (system_definitions == NULL) {   // this is the system definitions
        // add the `List` entry
        bin = Definitions_hash("List", d->size);
        list_defn = &(d->table[bin]);
        assert(list_defn->name == NULL);
        Definition_init(list_defn, "List", NULL);
        d->count++;

        // construct common `List[]` for bootstrapping
        EmptyList = NormalExpression_new(0);
        EmptyList->head = (BaseExpression*) list_defn;
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


// djb2
uint32_t Definitions_hash(const char* key, const uint32_t size) {
    uint64_t hash;
    uint32_t c;

    hash = 5381;
    while ((c = (uint32_t) *key++) != 0)
        hash = (hash * 33 + c);

    return (uint32_t) (hash % size);
}


Definition* Definitions_lookup(Definitions* d, const char* name) {
    uint32_t bin;
    Definition* result;
    
    // linear probing
    bin = Definitions_hash(name, d->size);

    while (d->table[bin].name != NULL && strcmp(d->table[bin].name, name) != 0) {
        printf("%s\n", d->table[bin].name);
        bin = (bin + 1) % (d->size);
    }

    result = &(d->table[bin]);
    if (result->name == NULL) {
        Definition_init(result, name, d->EmptyList);
        d->count++;
    }

    if (result->name == NULL) {
        return NULL;
    }
    return result;
}


int* get_int_value(Definitions* definitions, const char* name) {
    Definition* definition;
    NormalExpression* values;
    BaseExpression* value;

    definition = Definitions_lookup(definitions, name);
    if (definition == NULL) {
        return NULL;
    }

    values = definition->own_values;
    assert(values != NULL);

    if (values->argc < 1) {
        return NULL;
    }

    // take first own value
    value = values->leaves[0];
    if (value->type != MachineIntegerType) {
        return NULL;
    }

    return ((MachineInteger*) value)->value;
}


NormalExpression* insert_rule(NormalExpression* rules, BaseExpression* rule) {
    // TODO
    return NULL;
}


int* set_int_value(Definitions* definitions, const char* name, int value) {
    int* valuep;
    Definition* definition;
    MachineInteger* result;

    definition = Definitions_lookup(definitions, name);
    if (definition == NULL) {
        return NULL;
    }

    valuep = malloc(sizeof(int));
    if (valuep == NULL) {
        return NULL;
    }
    *valuep = value;

    result = MachineInteger_new(valuep);
    definition->own_values = insert_rule(definition->own_values, (BaseExpression*) result);

    // assert(definition->own_values->argc > 0);

    return result->value;
}
