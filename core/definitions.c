#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "definitions.h"
#include "expression.h"


// initialise a definition entry
void Definition_init(Definition* d, const char* name, NormalExpression* EmptyList) {
    d->name = (char*) malloc(strlen(name) + 1);
    if (d != NULL) {
        strcpy(d->name, name);
    }
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
        EmptyList->head = list_defn;
    } else {
        EmptyList = system_definitions->EmptyList;
    }

    // assign EmptyList pointer
    d->EmptyList = EmptyList;
}


void Definitions_free(Definitions* d) {
    free(d->table);
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
        bin = (bin + 1) % (d->size);
    }

    result = &(d->table[bin]);
    if (result->name == NULL) {
        Definition_init(result, name, NULL);
        d->count++;
    }

    if (result->name == NULL) {
        return NULL;
    }
    return result;
}
