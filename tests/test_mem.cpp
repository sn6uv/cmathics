// #include <stdlib.h>
#include <gtest/gtest.h>


extern "C" {
    #include "core/expression.h"
    #include "core/mem.h"
    #include "core/definitions.h"
    #include "core/types.h"
}


TEST(Mem, MemInit) {
    MemInit();
}


TEST(Mem, MemAllocFree) {
    BaseExpression* p = MemAlloc(5);
    EXPECT_TRUE(p != NULL);
    MemFree(p);
}


TEST(Mem, Symbol) {
    Symbol* p = (Symbol*) MemAlloc(sizeof(Symbol));
    ASSERT_TRUE(p != NULL);
    p->base.ref = 0;
    p->base.type = SymbolType;
    MemFree((BaseExpression*) p);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
