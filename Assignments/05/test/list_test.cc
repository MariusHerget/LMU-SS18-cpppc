/* ------------------------------------------------------------------------ *
*                               Assignment 02                               *
* -------------------------------------------------------------------------*/

#include "list_test.h"

#include <solution/list.h>
#include <stdio.h>
#include <gtest/gtest.h>
namespace cpppc {
TEST_F(ListTest, MoveSemantics)
{
        LOG_MESSAGE("listTest.MoveSemantics: new");
        list<int> v1;
        list<int> v2;
        list<int> v3;

        v1.push_front(34);
        v1.push_front(12);

        LOG_MESSAGE("listTest.MoveSemantics: assign");
        v2 = v1;

        LOG_MESSAGE("listTest.MoveSemantics: equals");
        ASSERT_EQ(1, v1 == v2);

        ASSERT_EQ(2, v1.size());
        //ASSERT_EQ(1, v1 == v2);

        LOG_MESSAGE("listTest.MoveSemantics: move assignment operator");

        v3 = std::move(v1);

        ASSERT_EQ(2, v3.size());
        ASSERT_EQ(0, v1.size());

        ASSERT_EQ(12, v3.front());
        v3.pop_front();
        ASSERT_EQ(34, v3.front());

        LOG_MESSAGE("listTest.MoveSemantics: move constructor");

        auto v4 = list<int>(std::move(v2));

        ASSERT_EQ(2, v4.size());
        ASSERT_EQ(0, v2.size());

        ASSERT_EQ(12, v4.front());
        v4.pop_front(); //error
        ASSERT_EQ(34, v4.front());
}
}
