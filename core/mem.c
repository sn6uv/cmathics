#include <stdlib.h>
#include <stdio.h>

#include "mem.h"


// TODO use a red-black tree to fix free performance
static struct TrackedExpressions {
    uint32_t count;
    uint32_t size;
    BaseExpression** objects;
} tracked_expressions;


void MemResize(uint32_t size) {
    // uint32_t i;
    // new_objects = (BaseExpression**) malloc(sizeof(BaseExpression*) * size);
    // for (i=0; i<tracked_expressions.count; i++);
    //     new_objects[i] = tracked_expressions.objects[i];
    // free(tracked_expressions.objects);
    // tracked_expressions.objects = new_objects;
    tracked_expressions.objects = realloc(tracked_expressions.objects, size);
    // CHECK_MALLOC(tracked_expressions.objects)
    tracked_expressions.size = size;
    return;
}


void MemInit(void) {
    tracked_expressions.count = 0;
    MemResize(1024);
}


BaseExpression* MemAlloc(uint32_t size) {
    BaseExpression* result;
    if (tracked_expressions.count == tracked_expressions.size) {
        MemResize(tracked_expressions.size * 2);
    }
    result = (BaseExpression*) malloc(size);
    // CHECK_MALLOC(result)
    return result;
}


// XXX O(n) 
void MemFree(BaseExpression* item) {
    uint32_t i;
    for (i=0; i<tracked_expressions.count; i++) {
        if (tracked_expressions.objects[i] == item) {
            free(tracked_expressions.objects[i]);
            tracked_expressions.objects[i] = tracked_expressions.objects[--tracked_expressions.count];
            break;
        }
    }
    if (tracked_expressions.count < tracked_expressions.size / 2) {
        MemResize(tracked_expressions.size / 2);
    }
}

