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
    Definition* symbol;
    char* tag;
    char* text;
} MessageOut;


typedef struct Message {
    Definition* symbol;
    char* tag;
    struct Message* next;
} Message;


typedef enum {
    NoInterrupt, AbortInterrupt, TimeoutInterrupt, ReturnInterrupt, BreakInterrupt, ContinueInterrupt
} EvaluationInterrupt;


typedef struct {
    Definitions* definitions;
    uint32_t recursion_depth;
    bool timeout;
    bool stopped;
    // Output* output;
    bool catch_interrupts;
    EvaluationInterrupt* interrupt;
    Out* out;
} Evaluation;


void send_message(Evaluation* evaluation, Definition* symbol, char* tag);
BaseExpression* evaluate_expression(Evaluation* evaluation, BaseExpression* expression);

Evaluation* Evaluation_new(Definitions* definitions, bool catch_interrupts);
#endif
