
#include "sparse_array_test.h"

#include <../04/solution/sparse_array.h>

#include <gtest/gtest.h>

#include <iostream>
#include <algorithm>
#include <iterator>
#include <array>

// you might want to set this to 1 for debugging
constexpr int NMULT = 10;
// constexpr int NMULT = 100000;

using namespace cpppc;
TEST_F(SparseArrayTest, MoveSemantics)
{

        constexpr int N = 50 * NMULT;
        sparse_array<int, N> sa1;

        ASSERT_EQ(false, sa1.empty());

        sa1[10] = 12;
        sa1[100] = 23;

        LOG_MESSAGE("SparseArrayTest.MoveSemantics: Move constructor");
        auto sa2 = sparse_array<int, N>(std::move(sa1));
        ASSERT_EQ(0, sa1[10]);
        ASSERT_EQ(0, sa1[100]);
        ASSERT_EQ(12, sa2[10]);
        ASSERT_EQ(23, sa2[100]);


        LOG_MESSAGE("SparseArrayTest.MoveSemantics: Move assignment");
        sparse_array<int, N> sa3;
        sa3 = std::move(sa2);
        ASSERT_EQ(0, sa2[10]);
        ASSERT_EQ(0, sa2[100]);
        ASSERT_EQ(12, sa3[10]);
        ASSERT_EQ(23, sa3[100]);

}
