typedef struct {
    uint32_t ref;
    Type type;
    char* value;
    uint32_t length;
} String;


String* String_new(char* value, uint32_t length) {
    String* p = (String*) malloc(sizeof(String));
    if (p) {
        p->ref = 0;
        p->type = StringType;
        p->value = value;
        p->length = length;
    }
    return p;
}


void String_free(String* p) {
    free(p);
}
