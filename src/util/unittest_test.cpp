
#include <iostream>

#include "unittest.hpp"

TEST(UnitTest, Equality) {
  std::cout << "1:" << 1 << std::endl;
}

int main(int argc, char** argv) {
  return sqlforfiles::unittest::RunAllTests();
}
