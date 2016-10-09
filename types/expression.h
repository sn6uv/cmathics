#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "types.h"


struct __Symbol;
struct __NormalExpression;


struct __NormalExpression {
    BaseExpression base;
    uint32_t last_evaluated;
    uint32_t hash;
    uint32_t argc;
    struct __Symbol* head;
    struct __NormalExpression* leaves[];  // zero length array of pointers
};


struct __Attributes {
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
};


struct __Symbol {
    BaseExpression base;
    char* name;
    struct __NormalExpression* own_values;
    struct __NormalExpression* sub_values;
    struct __NormalExpression* up_values;
    struct __NormalExpression* down_values;
    struct __NormalExpression* n_values;
    struct __NormalExpression* format_values;
    struct __NormalExpression* default_values;
    struct __NormalExpression* messages;
    struct __NormalExpression* options;
    void *subcode;   // XXX
    void *upcode;    // XXX
    void *downcode;  // XXX
    struct __Attributes attributes;
};


typedef struct __Symbol Symbol;
typedef struct __NormalExpression NormalExpression;


Symbol* Symbol_new(const char* s);
void Symbol_free(Symbol* p);

NormalExpression* List_new(uint32_t length);
#endif
