#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "mem.h"


// TODO use a red-black tree to fix free performance
static struct TrackedExpressions {
    uint32_t count;
    uint32_t size;
    BaseExpression** objects;
} tracked;


void MemResize(uint32_t size) {
    tracked.objects = realloc(tracked.objects, size);
    tracked.size = size;
    return;
}


void MemInit(void) {
    tracked.count = 0;
    tracked.objects = malloc(1024);
    tracked.size = 1024;
    return;
}


BaseExpression* MemAlloc(uint32_t size) {
    BaseExpression* result;
    if (tracked.count == tracked.size) {
        MemResize(tracked.size * 2);
    }
    result = (BaseExpression*) malloc(size);
    assert(result);
    tracked.objects[tracked.count] = result;
    tracked.count++;
    return result;
}


// XXX O(n) 
void MemFree(BaseExpression* item) {
    uint32_t i;
    int found = 0;
    for (i=0; i<tracked.count; i++) {
        if (tracked.objects[i] == item) {
            free(item);
            tracked.count--;
            tracked.objects[i] = tracked.objects[tracked.count];
            tracked.objects[tracked.count] = NULL;
            found = 1;
            break;
        }
    }
    assert(found);
    if (tracked.count < tracked.size / 2) {
        MemResize(tracked.size / 2);
    }
    return;
}

