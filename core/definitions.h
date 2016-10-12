#ifndef SYMTABLE_H
#define SYMTABLE_H
#include "types.h"
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
    BaseExpression base;
    char* name;
    Expression* own_values;
    Expression* sub_values;
    Expression* up_values;
    Expression* down_values;
    Expression* n_values;
    Expression* format_values;
    Expression* default_values;
    Expression* messages;
    Expression* options;
    void *subcode;   // XXX
    void *upcode;    // XXX
    void *downcode;  // XXX
    Attributes attributes;
} Symbol;


typedef struct {
    uint32_t size;
    uint32_t count;
    Expression* EmptyList;
    Symbol* table;
} Definitions;


Definitions* Definitions_new(uint32_t size);
void Definitions_free(Definitions* d);
void Definitions_init(Definitions* d, Definitions* system_definitions);
Symbol* Definitions_lookup(Definitions* d, const char* name);
uint32_t Definitions_hash(const char* key, const uint32_t size);    // exposed for testing

int64_t* get_int_value(Definitions* definitions, const char* name);
int64_t* set_int_value(Definitions* definitions, const char* name, int64_t value);
#endif
