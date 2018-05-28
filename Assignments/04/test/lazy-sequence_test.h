#ifndef CPPPC__A03__SPARSE_ARRAY_TEST_H__INCLUDED
#define CPPPC__A03__SPARSE_ARRAY_TEST_H__INCLUDED

#include <gtest/gtest.h>
#include "TestBase.h"

class LazySequenceTest : public ::testing::Test {

public:

  LazySequenceTest() {
    LOG_MESSAGE("Opening test suite: SparseArrayTest");
  }

  virtual ~LazySequenceTest() {
    LOG_MESSAGE("Closing test suite: SparseArrayTest");
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

};

#endif // CPPPC__A03__SPARSE_ARRAY_TEST_H__INCLUDED
