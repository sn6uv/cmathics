#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


NormalExpression* List_new(uint32_t argc) {
    Symbol* head = Symbol_new("List");
    NormalExpression* expr = NormalExpression_new(argc);
    if (head && expr) {
        expr->head = head;
    }
    return expr;
}


/*
int main() {
    MachineReal* yp;
    MachineInteger* xp;
    String* zp;

    int* z = (int*) malloc(sizeof(int));
    double *y = (double*) malloc(sizeof(double));
    *z = 5;
    *y = 1.6;
    xp = MachineInteger_new(z);
    yp = MachineReal_new(y);
    zp = String_new("abc", 3);

    printf("value = %f\n", *yp->value);

    free(z);
    free(y);
    MachineInteger_free(xp);
    MachineReal_free(yp);
    String_free(zp);
    return 0;
}
*/
