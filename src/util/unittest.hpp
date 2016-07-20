
#pragma once

#include <string>
#include <vector>
#include <sstream>
namespace sqlforfiles {
namespace unittest {

bool _b;

/**
 * Construct a single test, named "TEST_NAME" within the test case "CASE_NAME".
 *
 * Usage:
 *
 * TEST(MyModuleTests, TestThatFooFailsOnErrors) {
 *     ASSERT_EQUALS(error_success, foo(invalidValue));
 * }
 */
#define TEST(CASE_NAME, TEST_NAME)                                                      \
  class _TEST_TYPE_NAME(CASE_NAME, TEST_NAME) : public ::sqlforfiles::unittest::Test {  \
  public:                                                                               \
    void _run();                                                                        \
    static void _runIt() {                                                              \
      _TEST_TYPE_NAME(CASE_NAME, TEST_NAME) t;                                          \
      t._run();                                                                         \
    }                                                                                   \
  };                                                                                    \
  bool __##CASE_NAME__##TEST_NAME = ::sqlforfiles::unittest::RegisterTest(              \
    #CASE_NAME, #TEST_NAME, &_TEST_TYPE_NAME(CASE_NAME, TEST_NAME)::_runIt              \
  );                                                                                    \
  void _TEST_TYPE_NAME(CASE_NAME, TEST_NAME)::_run()

#define _TEST_TYPE_NAME(CASE_NAME, TEST_NAME) UnitTest__##CASE_NAME##__##TEST_NAME


/**
 * Base type for unit test fixtures.  Also, the default fixture type used
 * by the TEST() macro.
 */
class Test {

public:
  Test();
  virtual ~Test();

  void run();
  static std::vector<Test*> *tests;
  std::string _suiteName;
  std::string _caseName;
  void (*_func)();

};

std::vector<Test*> *Test::tests = nullptr;

Test::Test() {}
Test::~Test() {}

void Test::run() {
  std::cout << "Run :" << std::endl;
  // _func();
}


std::vector<Test>* tests;

// In C++ the only difference between a class and a struct is that members and
// base classes are private by default in classes, whereas they are public by
// default in structs. So structs can have constructors, and the syntax is the
// same as for classes.

bool RegisterTest(const std::string &suiteName, const std::string &caseName, void (*func)()) {
  if (tests == NULL) {
    tests = new std::vector<Test>;
  }
  Test t;
  t._suiteName = suiteName;
  t._caseName = caseName;
  t._func = func;

  // TODO: Remove this, and run from RunAllTests()
  t._func();

  tests->push_back(t);
  return true;
}

// An instance of Tester is allocated to hold temporary state during
// the execution of an assertion.
class Tester {
 private:
  bool ok_;
  const char* fname_;
  int line_;
  std::stringstream ss_;

 public:
  Tester(const char* f, int l)
      : ok_(true), fname_(f), line_(l) {
  }

  ~Tester() {
    if (!ok_) {
      fprintf(stderr, "%s:%d:%s\n", fname_, line_, ss_.str().c_str());
      exit(1);
    }
  }

  Tester& Is(bool b, const char* msg) {
    if (!b) {
      ss_ << " Assertion failure " << msg;
      ok_ = false;
    }
    return *this;
  }

#define BINARY_OP(name,op)                              \
  template <class X, class Y>                           \
  Tester& name(const X& x, const Y& y) {                \
    if (! (x op y)) {                                   \
      ss_ << " failed: " << x << (" " #op " ") << y;    \
      ok_ = false;                                      \
    }                                                   \
    return *this;                                       \
  }

  BINARY_OP(IsEq, ==)
  BINARY_OP(IsNe, !=)
  BINARY_OP(IsGe, >=)
  BINARY_OP(IsGt, >)
  BINARY_OP(IsLe, <=)
  BINARY_OP(IsLt, <)
#undef BINARY_OP

  // Attach the specified value to the error message if an error has occurred
  template <class V>
  Tester& operator<<(const V& value) {
    if (!ok_) {
      ss_ << " " << value;
    }
    return *this;
  }
};

#define ASSERT_TRUE(c) ::sqlforfiles::unittest::Tester(__FILE__, __LINE__).Is((c), #c)
#define ASSERT_EQ(a,b) ::sqlforfiles::unittest::Tester(__FILE__, __LINE__).IsEq((a),(b))
#define ASSERT_NE(a,b) ::sqlforfiles::unittest::Tester(__FILE__, __LINE__).IsNe((a),(b))
#define ASSERT_GE(a,b) ::sqlforfiles::unittest::Tester(__FILE__, __LINE__).IsGe((a),(b))
#define ASSERT_GT(a,b) ::sqlforfiles::unittest::Tester(__FILE__, __LINE__).IsGt((a),(b))
#define ASSERT_LE(a,b) ::sqlforfiles::unittest::Tester(__FILE__, __LINE__).IsLe((a),(b))
#define ASSERT_LT(a,b) ::sqlforfiles::unittest::Tester(__FILE__, __LINE__).IsLt((a),(b))

int RunAllTests() {
  std::cout << "Starting unit tests:" << std::endl;
  // std::cout << "Test" << Test::tests->size() << std::endl;
  // std::vector<Test>::iterator it;
  // for (it = tests->begin(); it != Test::tests->end(); ++it) {
  //   (*it)->run();
  // }
  return 0;
}

/**
 * opeartor << for vector
 */
template <class T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
  out << "[";
  size_t last = v.size() - 1;
  for(size_t i = 0; i < v.size(); ++i) {
    out << v[i];
    if (i != last) {
      out << ", ";
    }
  }
  out << "]";
  return out;
}


}
}
