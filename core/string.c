#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "types.h"
#include "string.h"


String* String_new(const uint64_t length) {
    String* p = (String*) malloc(sizeof(String) + length + 1);
    String_init(p, length);
    return p;
}


void String_init(String* p, const uint64_t length) {
    p->base.ref = 0;
    p->base.type = StringType;
    p->length = length;
    return;
}

void String_set(String* s, const char* value) {
    assert(strlen(value) == s->length);
    // also copy \0. not strictly required the length is known but it's handy.
    memcpy(s->value, value, s->length + 1);
    return;
}


void String_free(String* p) {
    free(p);
}
