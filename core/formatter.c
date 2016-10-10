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
    uint32_t result_size;
    uint32_t i, j;

    result = NULL;

    leaf_results = malloc(sizeof(char*) * expr->argc);
    if (leaf_results == NULL) {
        return NULL;
    }

    result_size = 2 * (expr->argc); // "[" + ", " * (argc - 1) + "]"


    // format head
    head_result = FullForm((BaseExpression*) expr->head);
    if (head_result == NULL) {
        return NULL;
    }
    result_size += strlen(head_result);

    // format leaves
    for (i=0; i<expr->argc; i++) {
        leaf_result = FullForm((BaseExpression*) expr->leaves[i]);
        if (leaf_result == NULL) {
            break;
        }
        result_size += strlen(leaf_result);
        leaf_results[i] = leaf_result;
    }

    if (i == expr->argc) {
        // FIXME rescanning buffers makes this O(n^2)
        result = malloc(result_size + 1);
        if (result) {
            strcpy(result, head_result);
            strcat(result, "[");

            for (i=0; i<expr->argc; i++) {
                strcat(result, leaf_results[i]);
                if (i < expr->argc - 1) {
                    strcat(result, ", ");
                }
            }
            strcat(result, "]");
            assert (i == expr->argc);
        }
    }

    // cleanup
    free(head_result);
    for (j=0; j < i; j++) {
        free(leaf_results[j]);
    }
    free(leaf_results);

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
