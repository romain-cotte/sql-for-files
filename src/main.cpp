#include <iostream>
#include <cstdlib>
#include <cstring>

#include "driver.hpp"

void print_usage() {
  std::cout << "  Usage: file-query [command]" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "  Options:" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "    -o  pipe to std::cin" << std::endl;
  std::cout << "    -h, --help     output usage information" << std::endl;
  std::cout << "    -v, --version  output the version number" << std::endl;
}


int main(const int argc, const char **argv) {
  if (argc != 2 ||
      std::strncmp(argv[1], "-h", 2) == 0 ||
      std::strncmp(argv[1], "--help", 2) == 0) {
    print_usage();
    return EXIT_FAILURE;
  }

  sqlforfiles::Driver driver;
  /** example for piping input from terminal, i.e., using cat **/
  if (std::strncmp(argv[1], "-o", 2) == 0 ||
      std::strncmp(argv[1], "--output", 2) == 0) {
    driver.parse(std::cin);
  } else {
    driver.parse(argv[1]);
  }

  return EXIT_SUCCESS;
}
