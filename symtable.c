#include "types/symbol.c"

typedef struct {
    uint32_t size;
    uint32_t count;
    Symbol** table;
} Definitions;


Definitions* Definitions_new(uint32_t size) {
    Definitions* d;
    uint32_t i;

    if (size < 1)
        return NULL;
    
    d = (Definitions*) malloc(sizeof(Definitions));
    if (d == NULL)
        return NULL;

    d->table = (Symbol**) malloc(sizeof(Symbol) * size);
    if (d->table == NULL)
        return NULL;

    for (i = 0; i < size; i++)
        d->table[i] = NULL;

    d->size = size;
    d->count = 0;
    return d;
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
    while (c = *key++)
        hash = (hash * 33 + c);

    return (uint32_t) (hash % size);
}


void Definitions_set(Definitions* d, Symbol* s) {
    uint32_t bin;
    Symbol* next;
    
    bin = Definitions_hash(s->name, d->size);
    next = d->table[bin];

    // linear probing to find the position
    while (next != NULL && strcmp(next->name, s->name) != 0) {
        next = d->table[++bin % d->size];
    }

    if (next == NULL) {
        // set
        d->table[bin] = s;
        d->count++;
    } else {
        // update
        // assert(strcmp(next->name, s->name) == 0);
        // TODO ref counting?
        d->table[bin] = s;
    }
}


Symbol* Definitions_get(Definitions* d, const char* key) {
    uint32_t bin;
    Symbol* s;

    bin = Definitions_hash(key, d->size);
    s = d->table[bin];

    while (s != NULL && strcmp(s->name, key) != 0) {
        s = d->table[++bin % d->size];
    }

    return s; // might be NULL
}
