#ifndef SYMTABLE_H
#define SYMTABLE_H
#include <stdbool.h>
#include "expression.h"


typedef struct {
    uint32_t size;
    uint32_t count;
    Symbol** table;
} Definitions;


Definitions* Definitions_new(uint32_t size);
void Definitions_free(Definitions* d);
Symbol* Definitions_lookup(Definitions* d, const char* name);
Symbol* Definitions_get(Definitions* d, const char* key);
bool Definitions_set(Definitions* d, Symbol* s);
uint32_t Definitions_hash(const char* key, const uint32_t size);
#endif
