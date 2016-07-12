
#include "unittest.hpp"

namespace sqlforfiles {
namespace test {

class Tester {
 private:
  bool _ok;
  const char* _fname;
  int _line;

 public:
  Tester(const char* f, int l) : _ok(true), _fname(f), _line(l) {
  }


};

// #define BINARY_OP(name, op)
//   template <class X, class Y>
//   Tester

}
}
