#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "types.h"
#include "string.h"


String* String_new(const uint64_t length) {
    String* p = (String*) malloc(sizeof(String));
    if (p) {
        p->base.ref = 0;
        p->base.type = StringType;
        p->length = length;

        p->value = (char*) malloc(length);
        if (p->value == NULL) {
            free(p);
            p = NULL;
        }
    }
    return p;
}

void String_set(String* s, const char* value) {
    assert(strlen(value) == s->length);
    memcpy(s->value, value, s->length + 1);
    return;
}


void String_free(String* p) {
    free(p);
}
