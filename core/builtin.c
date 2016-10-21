#include <stdlib.h>
#include <string.h>

#include "builtin.h"

#define TOTAL_KEYWORDS 21
#define MIN_WORD_LENGTH 4
#define MAX_WORD_LENGTH 24
#define MIN_HASH_VALUE 0
#define MAX_HASH_VALUE 20



Symbol builtin_symbols[] = {
    {{0, SymbolType}, "List", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{0, SymbolType}, "Blank", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{0, SymbolType}, "BlankSequence", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{0, SymbolType}, "BlankNullSequence", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{0, SymbolType}, "Pattern", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{0, SymbolType}, "Alternatives", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{0, SymbolType}, "Repeated", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{0, SymbolType}, "RepeatedNull", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{0, SymbolType}, "Except", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{0, SymbolType}, "Longest", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{0, SymbolType}, "Shortest", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{0, SymbolType}, "OptionsPattern", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{0, SymbolType}, "PatternSequence", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{0, SymbolType}, "OrderlessPatternSequence", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{0, SymbolType}, "Verbatim", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{0, SymbolType}, "HoldPattern", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}},
    {{0, SymbolType}, "KeyValuePattern", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{0, SymbolType}, "Condition", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}},
    {{0, SymbolType}, "PatternTest", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{0, SymbolType}, "Optional", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{0, SymbolType}, "Plus", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, {1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
};


void init_builtin_symbols() {
    uint32_t i;
    Symbol* d;
    Expression* EmptyList;

    EmptyList = Expression_new(0);
    Expression_set(EmptyList, (BaseExpression*) &builtin_symbols[0], NULL);

    for (i = MIN_HASH_VALUE; i < MAX_HASH_VALUE; i++) {
        d = &(builtin_symbols[i]);
        d->own_values = EmptyList;
        d->sub_values = EmptyList;
        d->up_values = EmptyList;
        d->down_values = EmptyList;
        d->n_values = EmptyList;
        d->format_values = EmptyList;
        d->default_values = EmptyList;
        d->messages = EmptyList;
        d->options = EmptyList;
    }
}

static unsigned int hash(const char *str, unsigned int len) {
    static unsigned char asso_values[] = {
        21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
        21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
        21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
        21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
        21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
        21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
        21, 21, 21, 21, 21, 10,  0, 14, 21,  9,
        21, 21, 11, 21, 21, 14,  6, 21, 21,  2,
         6, 21,  1, 13, 21, 21, 14, 21, 21, 21,
        21, 21, 21, 21, 21, 21, 21,  1, 21, 21,
        21,  1, 21, 21,  1,  6, 21, 21,  0, 21,
        21,  5,  2,  3,  1,  1,  1,  1, 10, 21,
         9, 21, 21, 21, 21, 21, 21, 21, 21, 21,
        21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
        21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
        21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
        21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
        21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
        21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
        21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
        21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
        21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
        21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
        21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
        21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
        21, 21, 21, 21, 21, 21
    };
    int hval = 0;

    switch (len) {
        default:
            hval += asso_values[(unsigned char)str[9]];
        case 9:
        case 8:
        case 7:
        case 6:
        case 5:
        case 4:
        case 3:
        case 2:
            hval += asso_values[(unsigned char)str[1]];
        case 1:
            hval += asso_values[(unsigned char)str[0]];
            break;
    }
    return hval;
}


Symbol* lookup_builtin_symbol(const char* str, const int len) {
    Symbol *symb;
    int key;

    if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH) {
        key = hash(str, len);
        if (key <= MAX_HASH_VALUE && key >= 0) {
            symb = &(builtin_symbols[key]);

            if (!strcmp(str, symb->name)) {
                return symb;
            }
        }
    }
    return NULL;
}

