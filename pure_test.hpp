#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <functional>

// pure_assert is a macro that is used to create an instance of the Assertion class. The Assertion class is used to check a boolean condition and print an error message if // // the condition is false.
// @usage : pure_assert(false) << "condition is false" << false;
#define pure_assert(condition) pure_test::Assertion(condition) << " [" << __FILE__ << ":"<< __LINE__ << "] [message: "
#define pure_report(condition) pure_test::Reporter(condition) << " [" << __func__ << "]" << "[message: "
namespace pure_test {

using Func = std::function<void()>;

class Reporter {
 public:
  Reporter(bool cnd) : cnd_(cnd) {}

  ~Reporter() {
    if (cnd_) {
      std::cout << "\033[32m[PASS] "  << "\033[0m" << std::endl;
      pass_count_++;
    } else {
      std::cout << "\033[31m[FAIL]" << ss_.str() << "]\033[0m"<< std::endl;
      fail_count_++;
    }
  }
  
  template <typename T>
  Reporter& operator<< (const T& value) {
    if (!cnd_) {
      ss_ << value;
    }
    return *this;
  }


  static void print_summary() {
    std::cout << "Summary: " << pass_count_ << " passed, " << fail_count_ << " failed." << std::endl;
  }

  static size_t pass_count_;
  static size_t fail_count_;
public:
  std::stringstream ss_;
  bool cnd_;
};


/// @brief A class for checking boolean conditions and printing error messages if the condition is false.
class Assertion {
 public:
  Assertion(bool condition) : condition_(condition) {}

  template <typename T>
  Assertion& operator<<(const T& value) {
    if (!condition_) {
      message_ << value;
    }
    return *this;
  }

  ~Assertion() {
    if (!condition_) {
      std::cerr << "[assert fail]" << message_.str() << "]" << std::endl;
      std::abort();
    }
  }

 private:
  bool condition_;
  std::stringstream message_;
};

class TestCase {
public:
  std::string name;
  Func func;
};

// Test suite class
class TestSuite {
 public:
  // Add a test case to the suite
  void add_test_case(const std::string& name, Func test_case) {
    test_cases_.push_back({name, std::move(test_case)});
  }

  // Run all test cases in the suite
  void run() {
    std::cout << "Running " << test_cases_.size() << " test cases...\n";
    for (const auto& test_case : test_cases_) {
      std::cout << "Running test case: " << test_case.name << "...\n";
      test_case.func();
    }
    if (Reporter::fail_count_ == 0) std::cout << "All test cases passed!\n";
    else Reporter::print_summary();
  }

 private:
  std::vector<TestCase> test_cases_;
};
}

#define PURE_TEST_INIT() size_t pure_test::Reporter::fail_count_ = 0; size_t pure_test::Reporter::pass_count_ = 0;