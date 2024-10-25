#include <gtest/gtest.h>

#include <summer.hpp>

using namespace solution;

TEST(SummerTest, TestSumOf_1_and_2_eq_3) {
    int a = 1, b = 2;

    Summer summer;

    ASSERT_EQ(summer.sum(a, b), 3);
}


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}