
#include <iostream>
#include <vector>

#include "unittest.hpp"
#include "vec.hpp"

namespace sqlforfiles {

TEST(VecTest, Selector) {
  std::cout << "Vec::selector" << std::endl;
  std::vector<int> v = { 1, 2, 3, 4, 5, 6 };
  std::vector<int> s = { 0, 3 };
  std::vector<int> result = Vec::selector(v, s);
  std::vector<int> expectedResult = { 1, 4 };

  ASSERT_EQ(result, expectedResult);

  s = {};
  result = Vec::selector(v, s);
  expectedResult = {};
  ASSERT_EQ(result, expectedResult);

  s = { 1, 5 };
  result = Vec::selector(v, s);
  expectedResult = { 2, 6 };
  ASSERT_EQ(result, expectedResult);

  s = { 5, 2 };
  result = Vec::selector(v, s);
  expectedResult = { 6, 3 };
  ASSERT_EQ(result, expectedResult);

  s = { -1, 2 };
  result = Vec::selector(v, s);
  expectedResult = { 1, 2, 3, 4, 5, 6, 3 };
  ASSERT_EQ(result, expectedResult);

  s = { -1 };
  result = Vec::selector(v, s);
  expectedResult = { 1, 2, 3, 4, 5, 6 };
  ASSERT_EQ(result, expectedResult);

}

TEST(VecTest, Output) {
  std::cout << "Vec::output" << std::endl;
  std::stringstream out;
  std::vector<std::string> v = { "1", "2" };
  std::string buff;
  std::string expectedString = "1;2";
  Vec::output(out, v, ';');
  out >> buff;
  ASSERT_EQ(buff, expectedString);

  expectedString = "1|2";
  Vec::output(out, v, '|');
  out >> buff;
  ASSERT_EQ(buff, expectedString);

}

}

int main(int argc, char** argv) {
  return sqlforfiles::unittest::RunAllTests();
}
