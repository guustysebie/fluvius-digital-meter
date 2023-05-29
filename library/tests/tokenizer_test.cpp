//
// Created by guust on 5/28/23.
//
#include <gtest/gtest.h>
#include <dsmr/parser.h>
TEST(MultiplyTests, TestIntegerOne_One)
{
int expected = 1;
int actual = 1;
ASSERT_EQ(expected, actual);
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}