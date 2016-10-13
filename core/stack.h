#include <stdint.h>
#include "types.h"


typedef struct {
    uint32_t size;
    uint32_t count;
    BaseExpression** items;
} Stack;

void Stack_init(Stack* stack, const uint32_t size);
void Stack_free(Stack* stack);

void Stack_push(Stack* stack, BaseExpression* item);
BaseExpression* Stack_pop(Stack* stack);
