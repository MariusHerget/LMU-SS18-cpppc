/* ------------------------------------------------------------------------ *
*                               Assignment 02                               *
* -------------------------------------------------------------------------*/

#include "list_test.h"

#include <solution/list.h>
#include <stdio.h>
#include <gtest/gtest.h>
namespace cpppc {


  TEST_F(ListTest, StandardConcept)
  {
    LOG_MESSAGE("listTest.StandardConcept: new");
    list<int> v1;
    list<int> v2;

    LOG_MESSAGE("listTest.StandardConcept: equals");
    ASSERT_EQ(1, v1 == v2);

    v1.push_front(34);
    v1.push_front(12);

    ASSERT_EQ(12, *(v1.begin()));
    ASSERT_EQ(34, *(++v1.begin()));

    ASSERT_EQ(0, v1 == v2);

    LOG_MESSAGE("listTest.StandardConcept: assign");
    v1 = v2;

    ASSERT_EQ(1, v1 == v2);

    LOG_MESSAGE("listTest.StandardConcept: copy");
    list<int> v3(v1);

    ASSERT_EQ(1, v1 == v3);
  }

  TEST_F(ListTest, listLIFO)
  {
    LOG_MESSAGE("listTest.listLIFO: new");
    list<int> v;

    LOG_MESSAGE("listTest.listLIFO: push_front(...)");
    v.push_front(444);
    v.push_front(333);
    v.push_front(222);
    v.push_front(111);
    ASSERT_EQ(4,   v.size());

    LOG_MESSAGE("listTest.listLIFO: pop_front(...)");
    ASSERT_EQ(111, v.pop_front());
    ASSERT_EQ(222, v.pop_front());
    ASSERT_EQ(333, v.pop_front());
    ASSERT_EQ(444, v.pop_front());
    ASSERT_EQ(0,   v.size());
  }
}
