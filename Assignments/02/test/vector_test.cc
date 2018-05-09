/* ------------------------------------------------------------------------ *
*                               Assignment 02                               *
* -------------------------------------------------------------------------*/

#include "vector_test.h"

#include <solution/vector.h>
#include <stdio.h>
#include <gtest/gtest.h>
namespace cpppc {

TEST_F(VectorTest, StandardConcept)
{
        LOG_MESSAGE("VectorTest.StandardConcept: vector__new");
        Vector<int> v1 = Vector<int>("v1", 0, 0);
        Vector<int> v2 = Vector<int>("v2", 0, 0);

        LOG_MESSAGE("VectorTest.StandardConcept: vector__equals");
        ASSERT_EQ(true, v1 == v2);

        LOG_MESSAGE("VectorTest.StandardConcept: push_back");
        v1.push_back(12);
        v1.push_back(34);


        LOG_MESSAGE("VectorTest.StandardConcept: push_back");
        ASSERT_EQ(0, v1 == v2);

        LOG_MESSAGE("VectorTest.StandardConcept: vector__assign");
        v2 = v1;

        ASSERT_EQ(1, v1 == v2);

        LOG_MESSAGE("VectorTest.StandardConcept: vector__copy");
        Vector<int> v3 =  Vector<int>(v1);

        ASSERT_EQ(1, v1 == v3);
}
TEST_F(VectorTest, VectorConcept)
{
        LOG_MESSAGE("VectorTest.VectorConcept: vector__new");
        Vector<int> v = Vector<int>("v1", 0, 0);

        ASSERT_EQ(0,  v.size());
        ASSERT_EQ(1,  v.empty());

        LOG_MESSAGE("VectorTest.VectorConcept: vector__begin, vector__end");
        ASSERT_EQ(v.begin(), v.end());
        ASSERT_EQ(v.end(), v.begin() + v.size());

        LOG_MESSAGE("VectorTest.VectorConcept: vector__push_back(56)");
        v.push_back(56);
        LOG_MESSAGE("VectorTest.VectorConcept: vector__push_back(78)");
        v.push_back(78);
        LOG_MESSAGE("VectorTest.VectorConcept: vector__push_back(90)");
        v.push_back(90);

        ASSERT_EQ(v.end(), v.begin() + v.size());

        LOG_MESSAGE("VectorTest.VectorConcept: vector__at");
        ASSERT_EQ(3,  v.size());
        ASSERT_EQ(0,  v.empty());
        ASSERT_EQ(56, v[0]);
        ASSERT_EQ(78, v[1]);
        ASSERT_EQ(90, v[2]);

        for (int i = 0; i < v.size(); i++) {
                LOG_MESSAGE("VectorTest.VectorConcept: v[%d] : %d",
                            i, v[i]);
        }

        LOG_MESSAGE("VectorTest.VectorConcept: vector__copy");
        Vector<int> vcopy = Vector<int>(v);

        LOG_MESSAGE("VectorTest.VectorConcept: vector__begin, vector__end");
        cpppc::Vector<int>::VectorIterator viter = v.begin();
        cpppc::Vector<int>::VectorIterator vend  = v.end();

        for (; viter != vend; ++viter) {
                *viter += 100;
        }

        LOG_MESSAGE("VectorTest.VectorConcept: vector__at");
        for (int i = 0; i < vcopy.size(); i++) {
                ASSERT_EQ(v[i], vcopy[i] + 100);
        }

        LOG_MESSAGE("VectorTest.VectorConcept: vector__assign(v_empty) ");
        Vector<int> v_empty = Vector<int>("v_empty", 0, 0);
        v = v_empty;

        ASSERT_EQ(true, v==v_empty);
        ASSERT_EQ(0, v.size());
        ASSERT_EQ(1, v.empty());
}

TEST_F(VectorTest, VectorFIFO)
{
        LOG_MESSAGE("VectorTest.VectorFIFO: vector__new");
        Vector<int> v = Vector<int>("v", 0, 0);

        LOG_MESSAGE("VectorTest.VectorFIFO: vector__push_back(...)");
        v.push_back(111);
        v.push_back(222);
        v.push_back(333);
        v.push_back(444);
        ASSERT_EQ(4,   v.size());

        LOG_MESSAGE("VectorTest.VectorFIFO: vector__pop_front(...)");
        ASSERT_EQ(444, v.pop_back());
        ASSERT_EQ(333, v.pop_back());
        ASSERT_EQ(222, v.pop_back());
        ASSERT_EQ(111, v.pop_back());
        ASSERT_EQ(0,   v.size());
}
TEST_F(VectorTest, VectorReverse)
{
        LOG_MESSAGE("VectorTest.VectorReverse: vector__new");
        Vector<int> v1 = Vector<int>("v1", 0, 0);
        Vector<int> v2 = Vector<int>("v2", 0, 0);

        LOG_MESSAGE("VectorTest.VectorReverse: vector__push_front(...)");
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
