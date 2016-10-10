#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "types.h"
#include "expression.h"
#include "definitions.h"
#include "int.h"
#include "formatter.h"


char* FullForm_Symbol(Definition* expr) {
    char* result = malloc(strlen(expr->name) + 1);
    if (result) {
        strcpy(result, expr->name);
    }
    return result;
}


char* FullForm_MachineInteger(MachineInteger* expr) {
    char* result = malloc(snprintf(NULL, 0, "%i", *expr->value) + 1);
    if (result) {
        sprintf(result, "%i", *expr->value);
    }
    return result;
}


char* FullForm_NormalExpression(NormalExpression* expr) {
    char* head_result;
    char* leaf_result;
    char** leaf_results;
    char* result;
    uint32_t* leaf_sizes;
    uint32_t head_size, result_size;
    uint32_t i, j;

    result = NULL;

    leaf_results = malloc(sizeof(char*) * expr->argc);
    leaf_sizes = malloc(sizeof(uint32_t) * expr->argc);
    if (leaf_results == NULL || leaf_sizes == NULL) {
        return NULL;
    }

    // format head
    head_result = FullForm((BaseExpression*) expr->head);
    if (head_result == NULL) {
        return NULL;
    }
    head_size = strlen(head_result);

    // HEAD + "[" + ", " * (argc - 1) + "]"
    result_size = head_size + 2 * (expr->argc);

    // format leaves
    for (i=0; i<expr->argc; i++) {
        leaf_result = FullForm((BaseExpression*) expr->leaves[i]);
        if (leaf_result == NULL) {
            break;
        }
        leaf_results[i] = leaf_result;
        leaf_sizes[i] = strlen(leaf_result);
        result_size += leaf_sizes[i];
    }

    // construct result
    if (i == expr->argc) {
        result = malloc(result_size + 1);
        if (result) {
            memcpy(result, head_result, head_size);
            j = head_size; // position in result
            memcpy(result + j, "[", 1);
            j++;

            for (i=0; i<expr->argc; i++) {
                memcpy(result + j, leaf_results[i], leaf_sizes[i]);
                j += leaf_sizes[i];
                if (i < expr->argc - 1) {
                    memcpy(result + j, ", ", 2);
                    j+=2;
                }
            }
            memcpy(result + j, "]", 2);    // also copy \0
            j+=2;

            assert(i == expr->argc);
            assert(j == result_size + 1);
        }
    }

    // cleanup
    free(head_result);
    for (j=0; j < i; j++) {
        free(leaf_results[j]);
    }
    free(leaf_results);
    free(leaf_sizes);

    return result;
}


char* FullForm(BaseExpression* expr) {
    char* result;

    switch (expr->type) {
        case SymbolType:
            result = FullForm_Symbol((Definition*) expr);
            break;
        case MachineIntegerType:
            result = FullForm_MachineInteger((MachineInteger*) expr);
            break;
        case NormalExpressionType:
            result = FullForm_NormalExpression((NormalExpression*) expr);
            break;
        default:
            result = NULL;
    }
    return result;
}
