#ifndef EVALUATION_H
#define EVALUATION_H
#include <stdbool.h>

#include "definitions.h"
#include "expression.h"


typedef enum {
    PrintType, MessageType
} OutType;


typedef struct Out{
    OutType type;
    struct Out* next;
} Out;


typedef struct {
    Out base;
    char* text;
} PrintOut;


typedef struct {
    Out base;
    Symbol* symbol;
    char* tag;
    char* text;
} MessageOut;


typedef struct Message {
    Symbol* symbol;
    char* tag;
    struct Message* next;
} Message;


typedef enum {
    NoInterrupt, AbortInterrupt, TimeoutInterrupt, ReturnInterrupt, BreakInterrupt, ContinueInterrupt
} EvaluationInterrupt;


typedef struct {
    Definitions* definitions;
    int64_t recursion_depth;
    bool timeout;
    bool stopped;
    // Output* output;
    bool catch_interrupts;
    EvaluationInterrupt interrupt;
    Out* out;
} Evaluation;


void send_message(Evaluation* evaluation, Symbol* symbol, char* tag);
BaseExpression* Evaluate(Evaluation* evaluation, BaseExpression* expression);

Evaluation* Evaluation_new(Definitions* definitions, bool catch_interrupts);
void Evaluation_free(Evaluation* evaluation);
#endif
