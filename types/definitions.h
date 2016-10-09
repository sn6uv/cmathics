#ifndef SYMTABLE_H
#define SYMTABLE_H
#include <stdbool.h>
#include "expression.h"


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
    char* name;
    NormalExpression* own_values;
    NormalExpression* sub_values;
    NormalExpression* up_values;
    NormalExpression* down_values;
    NormalExpression* n_values;
    NormalExpression* format_values;
    NormalExpression* default_values;
    NormalExpression* messages;
    NormalExpression* options;
    void *subcode;   // XXX
    void *upcode;    // XXX
    void *downcode;  // XXX
    Attributes attributes;
} Definition;


typedef struct {
    uint32_t size;
    uint32_t count;
    Definition* table;
} Definitions;


Definitions* Definitions_new(uint32_t size);
void Definitions_free(Definitions* d);

Definition* Definitions_lookup(Definitions* d, const char* name);
// Definition Definitions_get(Definitions* d, const char* key);
uint32_t Definitions_hash(const char* key, const uint32_t size);    // exposed for testing

#endif
