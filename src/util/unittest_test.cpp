
#include <iostream>
#include <vector>

#include "unittest.hpp"

TEST(UnitTest, Equality) {
  ASSERT_EQ(1, 1);
}

TEST(UnitTest, Inequality) {
  ASSERT_NE(1, 2);
}

TEST(UnitTest, GreaterOrEqual) {
  ASSERT_GE(1, 1);
  ASSERT_GE(2, 1);
}

TEST(UnitTest, GreaterThan) {
  ASSERT_GT(2, 1);
}

TEST(UnitTest, LowerOrEqual) {
  ASSERT_LE(1, 1);
  ASSERT_LE(1, 2);
}

TEST(UnitTest, LowerThan) {
  ASSERT_LT(1, 2);
}

TEST(UnitTest, VectorEquality) {
  std::vector<int> v1 = { 1, 3 };
  std::vector<int> v2 = { 1, 3 };
  ASSERT_EQ(v1, v2);
}

int main(int argc, char** argv) {
  return sqlforfiles::unittest::RunAllTests();
}
