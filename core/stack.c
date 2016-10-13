// A dynamically resizing stack

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "stack.h"


void Stack_resize(Stack* stack, const uint32_t new_size) {
    BaseExpression** new_items;
    uint32_t i;

    stack->size = new_size;
    new_items = (BaseExpression**) malloc(new_size * sizeof(BaseExpression));

    if (new_items == NULL) {
        fprintf(stderr, "Failed to resize stack.\n");
        abort();
    }

    for (i=0; i<stack->count; i++) {
        new_items[i] = stack->items[i];
    }

    free(stack->items);
    stack->items = new_items;
}



void Stack_init(Stack* stack, const uint32_t size) {
    stack->size = size;
    stack->count = 0;
    Stack_resize(stack, size);
}


void Stack_clear(Stack* stack) {
    free(stack->items);
    stack->count = 0;
}


void Stack_shrink(Stack* stack) {
    Stack_resize(stack, stack->size / 2);
}


void Stack_grow(Stack* stack) {
    Stack_resize(stack, stack->size * 2);
}


void Stack_push(Stack* stack, BaseExpression* item) {
    if (stack->count == stack->size) {
        Stack_grow(stack);
    }
    stack->items[stack->count] = item;
    stack->count++;
}


BaseExpression* Stack_pop(Stack* stack) {
    BaseExpression* item;
    assert(stack->count);
    stack->count--;
    item = stack->items[stack->count];
    if (stack->count < 2 * stack->size) {
        Stack_shrink(stack);
    }
    return item;
}
