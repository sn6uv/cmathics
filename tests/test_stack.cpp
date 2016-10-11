#include <stdlib.h>
#include <gtest/gtest.h>

extern "C" {
    #include "core/data_structures/stack.h"
}


TEST(Stack, new32) {
    Stack* stack;
    stack = Stack_new(32);
    ASSERT_TRUE(stack != NULL);
    EXPECT_EQ(stack->size, 32);
    EXPECT_EQ(stack->count, 0);
    Stack_free(stack);
}

TEST(Stack, push) {
    Stack* stack;
    int v;
    int* vp;
    int* rp;
    stack = Stack_new(32);
    ASSERT_TRUE(stack != NULL);
    v = 5;
    vp = &v;
    rp = (int*) Stack_push(stack, (void*) vp);
    ASSERT_TRUE(rp != NULL);
    EXPECT_EQ(*rp, 5);
    EXPECT_EQ(rp, vp);
    EXPECT_EQ(stack->count, 1);
    EXPECT_EQ(stack->size, 32);
    Stack_free(stack);
}

TEST(Stack, push_full) {
    Stack* stack;
    int v1, v2;
    int* v1p;
    int* v2p;
    int* r1p;
    int* r2p;
    stack = Stack_new(1);
    ASSERT_TRUE(stack != NULL);
    v1 = 1;
    v1p = &v1;
    v2 = 2;
    v2p = &v2;

    r1p = (int*) Stack_push(stack, (void*) v1p);
    EXPECT_TRUE(r1p != NULL);
    EXPECT_EQ(stack->count, 1);
    
    r2p = (int*) Stack_push(stack, (void*) v2p);
    EXPECT_TRUE(r2p == NULL);
    EXPECT_EQ(stack->count, 1);

    Stack_free(stack);
}


TEST(Stack , pop) {
    Stack* stack;
    int v;
    int* vp;
    int* rp;
    stack = Stack_new(32);
    ASSERT_TRUE(stack != NULL);
    v = 5;
    vp = &v;
    Stack_push(stack, (void*) vp);
    rp = (int*) Stack_pop(stack);
    EXPECT_EQ(rp, vp);
    EXPECT_EQ(*rp, 5);
    EXPECT_EQ(stack->count, 0);
    Stack_free(stack);
}


TEST(Stack , pop_empty) {
    Stack* stack;
    int* rp;
    stack = Stack_new(32);
    ASSERT_TRUE(stack != NULL);
    rp = (int*) Stack_pop(stack);
    EXPECT_TRUE(rp == NULL);
    EXPECT_EQ(stack->count, 0);
    Stack_free(stack);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
