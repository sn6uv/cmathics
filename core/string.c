#include <stdlib.h>

#include "types.h"
#include "string.h"


String* String_new(char* value, uint32_t length) {
    String* p = (String*) malloc(sizeof(String));
    if (p) {
        p->base.ref = 0;
        p->base.type = StringType;
        p->value = value;
        p->length = length;
    }
    return p;
}


void String_free(String* p) {
    free(p);
}
