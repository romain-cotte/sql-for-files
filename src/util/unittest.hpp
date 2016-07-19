
#pragma once

#include <string>
#include <vector>

namespace sqlforfiles {
namespace unittest {

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
  private:                                                                              \
    virtual void _doTest();                                                             \
                                                                                        \
    static const RegistrationAgent<_TEST_TYPE_NAME(CASE_NAME, TEST_NAME)> _agent;       \
  };                                                                                    \
  const ::sqlforfiles::unittest::Test::RegistrationAgent<_TEST_TYPE_NAME(CASE_NAME, TEST_NAME)> \
    _TEST_TYPE_NAME(CASE_NAME, TEST_NAME)::_agent(#CASE_NAME, #TEST_NAME);              \
  void _TEST_TYPE_NAME(CASE_NAME, TEST_NAME)::_doTest()


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

protected:
  /**
   * Registration agent for adding tests to suites, used by TEST macro.
   */
  template <typename T>
  class RegistrationAgent {

  public:
    RegistrationAgent(const std::string& suiteName, const std::string& testName);
    std::string getSuiteName() const;
    std::string getTestName() const;

  private:
    const std::string _suiteName;
    const std::string _testName;
  };


private:
  /**
   * Called on the test object before running the test.
   */
  // virtual void setUp();

  /**
   * Called on the test object after running the test.
   */
  // virtual void tearDown();

  /**
   * The test itself.
   */
  virtual void _doTest();

};


Test::Test() {}
Test::~Test() {}

void Test::run() {
  std::cout << "Run :" << std::endl;

  _doTest();
}


std::vector<Test*> *Test::tests = nullptr;

template <typename T>
Test::RegistrationAgent<T>::RegistrationAgent(const std::string& suiteName,
                                              const std::string& testName,
                                              void (*func)())
  : _suiteName(suiteName), _testName(testName) {
    if (tests == nullptr) {
      tests = new std::vector<Test*>;
    }
    T* t;

    tests->push_back(t);

    // Suite::getSuite(suiteName)->add<T>(testName);
}


template <typename T>
std::string Test::RegistrationAgent<T>::getSuiteName() const {
  return _suiteName;
}

template <typename T>
std::string Test::RegistrationAgent<T>::getTestName() const {
  return _testName;
}



// extern int RunAllTests();
int RunAllTests() {
  // Test::tests = nullptr;
  std::cout << "Test" << Test::tests->size() << std::endl;
  std::vector<Test*>::iterator it;
  for (it = Test::tests->begin(); it != Test::tests->end(); ++it) {
    // std::cout << *it << std::endl;
    (*it)->run();
  }
  return 0;
}


}
}
