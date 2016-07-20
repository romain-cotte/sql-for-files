#pragma once

#include <string>
#include <vector>
#include <sstream>
namespace sqlforfiles {

class Vec {
public:
  template <class T>
  static std::vector<T> selector(std::vector<T> vector,
                                 std::vector<int> select) {
    std::vector<T> result;
    int s = vector.size();

    std::vector<int>::iterator it;
    for (it = select.begin(); it != select.end(); ++it) {
      if (*it > s) {
        throw "index out of bound";
      }
      result.push_back(vector.at(*it));
    }

    return result;
  }

};

}
