struct Symbol_;
struct NormalExpression_;

typedef struct NormalExpression_ {
    uint32_t ref;
    Type type;
    uint32_t last_evaluated;
    uint32_t hash;
    uint32_t argc;
    Symbol_* head;
    NormalExpression_* leaves[];  // zero length array of pointers
} NormalExpression;


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


typedef struct Symbol_ {
    uint32_t ref;
    Type type;
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
} Symbol;


Symbol* Symbol_new(const char* s);
void Symbol_free(Symbol* p);

NormalExpression* List_new(uint32_t length);
