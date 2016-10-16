#ifndef PATTERN_H
#define PATTERN_H

#include "types.h"

bool MatchQ(BaseExpression* expr, BaseExpression* patt);
BaseExpression* DoReplace(BaseExpression* expr, BaseExpression* patt);
#endif
