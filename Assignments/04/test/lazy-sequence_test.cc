
#include "lazy-sequence_test.h"

#include <solution/layz-sequence.h>

#include <gtest/gtest.h>

#include <iostream>
#include <algorithm>
#include <iterator>
#include <array>

// you might want to set this to 1 for debugging
constexpr int NMULT = 1;
// constexpr int NMULT = 100000;

using namespace cpppc;


TEST_F(LazySequenceTest, StandardConcept)
{
        LOG_MESSAGE("LazySequenceTest.StandardConcept: default ctor");
        lazy_sequence<int> sa1 {};
        lazy_sequence<int> sa2 {};

        LOG_MESSAGE("LazySequenceTest. StandardConcept: ==");
        ASSERT_EQ(sa1, sa1);
        ASSERT_EQ(sa2, sa2);

        ASSERT_EQ(0, sa1.size());
        ASSERT_EQ(0, sa2.size());

        sa1 = lazy_sequence<int> {
          100,
          [](int idx) {
            return idx + 100;
          }
        };

        LOG_MESSAGE("LazySequenceTest.StandardConcept: =");
        sa2 = sa1;
        ASSERT_EQ(sa1, sa2);
        ASSERT_EQ(sa2, sa1);
}

TEST_F(LazySequenceTest, SomeTest) {
  lazy_sequence<int> sa1 {};

  sa1 = lazy_sequence<int> {
    100,
    [](int idx) {
      return  idx +100;
    }
  };

  LOG_MESSAGE("LazySequenceTest.SomeTest: size");
  ASSERT_EQ(100, sa1.size());

  LOG_MESSAGE("LazySequenceTest.SomeTest: begin");
  ASSERT_EQ(100, sa1.front());

  LOG_MESSAGE("LazySequenceTest.SomeTest: end");
  ASSERT_EQ(199, sa1.back());


  LOG_MESSAGE("LazySequenceTest.SomeTest: s[i]");
  ASSERT_EQ(100, sa1[0]);
  ASSERT_EQ(101, sa1[1]);
  ASSERT_EQ(102, sa1[2]);
  ASSERT_EQ(103, sa1[3]);
  ASSERT_EQ(104, sa1[4]);

  int count = 0;
  for (auto i : sa1) {
    ASSERT_EQ(i, count +100);
    ++count;
  }
}
