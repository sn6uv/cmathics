#ifndef STRING_H
#define STRING_H
#include "types.h"


typedef struct {
    BaseExpression base;
    uint64_t length;
    char value[];
} String;


String* String_new(const uint64_t length);
void String_init(String* s, const uint64_t length);
void String_set(String* s, const char* value);
void String_free(String* p);
#endif
