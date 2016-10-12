#include <stdint.h>
#include <assert.h>
#include <stdbool.h>

#include "types.h"
#include "hash.h"
#include "int.h"
#include "real.h"
#include "rational.h"
#include "string.h"


uint64_t djb2(const char* str) {
    uint64_t result;
    int c;

    result = 5381;
    while ((c = *str++)) {
        result = ((result << 5) + result) + c;
    }
    return result;
}


uint64_t hash_combine(uint64_t seed, const uint64_t x) {
    // see boost::hash_combine
    seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
}


uint64_t hash_pair(const uint64_t x, const uint64_t y) {
    // combines 2 hash values
    uint64_t seed = 0;
    seed = hash_combine(seed, x);
    seed = hash_combine(seed, y);
    return seed;
}


uint64_t Hash_MachineInteger(const MachineInteger* expression) {
    return hash_pair(djb2("MachineInteger"), expression->value);
}


uint64_t Hash_BigInteger(const BigInteger* expression) {
    // TODO
    return 0;
}


uint64_t Hash_MachineReal(const MachineReal* expression) {
    // TODO better hash see CPython _Py_HashDouble
    return hash_pair(djb2("MachineInteger"), (uint64_t) expression->value);
}


uint64_t Hash_BigReal(const BigReal* expression) {
    // TODO
    return 0;
}


uint64_t Hash_Rational(const Rational* expression) {
    // hash ("Rational", numer, denom)
    uint64_t seed = 0;
    seed = hash_combine(seed, djb2("Rational"));
    seed = hash_combine(seed, Hash((BaseExpression*) expression->numer));
    seed = hash_combine(seed, Hash((BaseExpression*) expression->denom));
    return seed;
}


uint64_t Hash_Expression(const Expression* expression) {
    uint64_t result;
    int i;
    result = 0;
    result = hash_combine(result, Hash(expression->head));
    for (i=0; i<expression->argc; i++) {
        result = hash_combine(result, Hash(expression->leaves[i]));
    }
    return result;
}


uint64_t Hash_Symbol(const Symbol* expression) {
    return hash_pair(djb2("Symbol"), djb2(expression->name));
}


uint64_t Hash_String(const String* expression) {
    return hash_pair(djb2("String"), djb2(expression->value));
}


uint64_t Hash(const BaseExpression* expression) {
    uint64_t result;
    switch (expression->type) {
        case MachineIntegerType:
            result = Hash_MachineInteger((MachineInteger*) expression);
            break;
        case BigIntegerType:
            result = Hash_BigInteger((BigInteger*) expression);
            break;
        case MachineRealType:
            result = Hash_MachineReal((MachineReal*) expression);
            break;
        case BigRealType:
            result = Hash_BigReal((BigReal*) expression);
            break;
        case RationalType:
            result = Hash_Rational((Rational*) expression);
            break;
        // case ComplexType:
        //     result = Hash_Complex((Complex*) expression);
        //     break;
        case ExpressionType:
            result = Hash_Expression((Expression*) expression);
            break;
        case SymbolType:
            result = Hash_Symbol((Symbol*) expression);
            break;
        case StringType:
            result = Hash_String((String*) expression);
            break;
        // case RawExpressionType:
        //     result = Hash_RawExpression((RawExpression*) expression);
        //     break;
        default:
            assert(false);
    }
    return result;
}
