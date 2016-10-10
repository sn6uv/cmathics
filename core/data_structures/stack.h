#ifndef STACK_H
#define STACK_H
#include <stdint.h>


typedef struct {
    void** data;
    uint32_t count;
    uint32_t size;
} Stack;


Stack* Stack_new(uint32_t size);
void Stack_free(Stack* stack);

void* Stack_pop(Stack* stack);
void* Stack_push(Stack* stack, void* item);
#endif
