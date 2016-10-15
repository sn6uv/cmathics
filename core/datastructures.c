#include <stdlib.h>
#include <assert.h>

#include "core/datastructures.h"


void List_new(List* l, uint32_t size) {
    l->count = 0;
    l->size = size;
    l->objects = malloc(sizeof(BaseExpression*) * size);
}


void List_resize(List* l, uint32_t new_size) {
    l->objects = realloc(l->objects, sizeof(BaseExpression*) * new_size);
    l->size = new_size;
}


void List_append(List* l, BaseExpression* object) {
    if (l->count == l->size) {
        List_resize(l, l->size << 1);
    }
    l->objects[l->count] = object;
    l->count++;
}


BaseExpression* List_pop(List* l) {
    if (l->count) {
        l->count--;
        if (l->count < l->size >> 2) {
            // halve size if less than 25% full
            List_resize(l, l->size >> 1);
        }
        return l->objects[l->count];
    } else {
        return NULL;
    }
}


void List_free(List* l) {
    free(l->objects);
}
