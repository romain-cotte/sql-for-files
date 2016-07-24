#pragma once

#include <string>
#include <vector>
#include <sstream>

namespace sqlforfiles {

class Vec {
public:

  template <class T>
  static std::vector<T> selector(const std::vector<T> &vector,
                                 const std::vector<int> &select) {
    std::vector<T> result;
    int s = vector.size();

    std::vector<int>::const_iterator it;
    for (it = select.begin(); it != select.end(); ++it) {
      if (*it == -1) {
        result.insert(result.end(), vector.begin(), vector.end());
        continue;
      }
      if (*it > s) {
        std::cout << "Index out of bound, ignored it:" << *it << ">" << s << std::endl;
        continue;
        // throw "index out of bound";
      }
      result.push_back(vector.at(*it));
    }

    return result;
  }

  static void output(std::ostream& out,
                     const std::vector<std::string> &vector,
                     const char delimiter) {
    std::vector<std::string>::const_iterator it;
    for (it = vector.begin(); it != vector.end(); ++it) {
      if (it == vector.begin()) {
        out << *it;
      } else {
        out <<  delimiter << *it;
      }
    }
    out << std::endl;
  }
};

}
