#ifndef BUILTIN_H
#define BUILTIN_H

#include "types.h"
#include "definitions.h"

Symbol* lookup_builtin_symbol(const char* str, const int len);

Symbol builtin_symbols[];
void init_builtin_symbols();
#endif
