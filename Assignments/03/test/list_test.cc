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
        LOG_MESSAGE("ListTest.StandardConcept: List__new");
        list<int> v1 = list<int>();
        list<int> v2 = list<int>();

        LOG_MESSAGE("ListTest.StandardConcept: List__equals");
        ASSERT_EQ(true, v1 == v2);

        LOG_MESSAGE("ListTest.StandardConcept: push_back");
        v1.push_back(12);
        v1.push_back(34);


        LOG_MESSAGE("ListTest.StandardConcept: push_back");
        ASSERT_EQ(0, v1 == v2);

        LOG_MESSAGE("ListTest.StandardConcept: List__assign");
        v2 = v1;

        ASSERT_EQ(1, v1 == v2);

        LOG_MESSAGE("ListTest.StandardConcept: List__copy");
        list<int> v3 =  list<int>(v1);

        ASSERT_EQ(1, v1 == v3);
}
TEST_F(ListTest, ListConcept)
{
        LOG_MESSAGE("ListTest.ListConcept: List__new");
        list<int> v = list<int>();

        ASSERT_EQ(0,  v.size());
        ASSERT_EQ(1,  v.empty());

        LOG_MESSAGE("ListTest.ListConcept: List__begin, List__end");
        ASSERT_EQ(v.begin(), v.end());
        ASSERT_EQ(v.end(), v.begin() + v.size());

        LOG_MESSAGE("ListTest.ListConcept: List__push_back(56)");
        v.push_back(56);
        LOG_MESSAGE("ListTest.ListConcept: List__push_back(78)");
        v.push_back(78);
        LOG_MESSAGE("ListTest.ListConcept: List__push_back(90)");
        v.push_back(90);

        ASSERT_EQ(v.end(), v.begin() + v.size());

        LOG_MESSAGE("ListTest.ListConcept: List__at");
        ASSERT_EQ(3,  v.size());
        ASSERT_EQ(0,  v.empty());
        ASSERT_EQ(56, v[0]);
        ASSERT_EQ(78, v[1]);
        ASSERT_EQ(90, v[2]);

        for (int i = 0; i < v.size(); i++) {
                LOG_MESSAGE("ListTest.ListConcept: v[%d] : %d",
                            i, v[i]);
        }

        LOG_MESSAGE("ListTest.ListConcept: List__copy");
        list<int> vcopy = list<int>(v);

        LOG_MESSAGE("ListTest.ListConcept: List__begin, List__end");
        cpppc::list<int>::ListIterator viter = v.begin();
        cpppc::list<int>::ListIterator vend  = v.end();

        for (; viter != vend; ++viter) {
                *viter += 100;
        }

        LOG_MESSAGE("ListTest.ListConcept: List__at");
        for (int i = 0; i < vcopy.size(); i++) {
                ASSERT_EQ(v[i], vcopy[i] + 100);
        }

        LOG_MESSAGE("ListTest.ListConcept: List__assign(v_empty) ");
        list<int> v_empty = list<int>();
        v = v_empty;

        ASSERT_EQ(true, v==v_empty);
        ASSERT_EQ(0, v.size());
        ASSERT_EQ(1, v.empty());
}

TEST_F(ListTest, ListFIFO)
{
        LOG_MESSAGE("ListTest.ListFIFO: List__new");
        list<int> v = list<int>();

        LOG_MESSAGE("ListTest.ListFIFO: List__push_back(...)");
        v.push_back(111);
        v.push_back(222);
        v.push_back(333);
        v.push_back(444);
        ASSERT_EQ(4,   v.size());

        LOG_MESSAGE("ListTest.ListFIFO: List__pop_front(...)");
        ASSERT_EQ(444, v.pop_back());
        ASSERT_EQ(333, v.pop_back());
        ASSERT_EQ(222, v.pop_back());
        ASSERT_EQ(111, v.pop_back());
        ASSERT_EQ(0,   v.size());
}
TEST_F(ListTest, ListReverse)
{
        LOG_MESSAGE("ListTest.ListReverse: List__new");
        list<int> v1 = list<int>();
        list<int> v2 = list<int>();

        LOG_MESSAGE("ListTest.ListReverse: List__push_front(...)");
        v1.push_back(444);
        v1.push_back(333);
        v1.push_back(222);
        v1.push_back(111);
        ASSERT_EQ(4,   v1.size());

        v2.push_back(111);
        v2.push_back(222);
        v2.push_back(333);
        v2.push_back(444);
        ASSERT_EQ(4,   v2.size());

        v1.reverse();
        ASSERT_EQ(1,  v1 == v2);
}
}
