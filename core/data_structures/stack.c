#include <stdlib.h>
#include "stack.h"

Stack* Stack_new(uint32_t size) {
    Stack* stack;
    stack = (Stack*) malloc(sizeof(Stack));
    if (stack) {
        stack->count = 0;
        stack->size = size;
        stack->data = (void*) malloc(sizeof(void*) * size);
        if (stack->data == NULL) {
            free(stack);
            stack = NULL;
        }
    }
    return stack;
}


void Stack_free(Stack* stack) {
    free(stack->data);
    free(stack);
}


void* Stack_pop(Stack* stack) {
    void* result;
    if (stack->count == 0) {
        return NULL;
    }
    result = stack->data[(stack->count--)];
    return result;
}


void* Stack_push(Stack* stack, void* item) {
    if (stack->count == stack->size) {
        return NULL;
    }
    stack->data[++(stack->count)] = item;
    return item;
}
