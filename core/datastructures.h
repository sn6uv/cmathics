#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H
#include "types.h"


typedef struct{
    uint32_t count;
    uint32_t size;
    BaseExpression** objects;
} List;


void List_new(List* l, uint32_t size);
void List_append(List* l, BaseExpression* object);
BaseExpression* List_pop(List* l);
void List_free(List* l);
#endif
