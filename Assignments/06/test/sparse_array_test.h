#ifndef CPPPC__A03__SPARSE_ARRAY_TEST_H__INCLUDED
#define CPPPC__A03__SPARSE_ARRAY_TEST_H__INCLUDED

#include <gtest/gtest.h>
#include "TestBase.h"

class SparseArrayTest : public ::testing::Test {

public:

  SparseArrayTest() {
    LOG_MESSAGE("Opening test suite: LazySequenceTest");
  }

  virtual ~SparseArrayTest() {
    LOG_MESSAGE("Closing test suite: LazySequenceTest");
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

};

#endif // CPPPC__A03__SPARSE_ARRAY_TEST_H__INCLUDED
