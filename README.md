# Introduction to Testing Frameworks
This is a C++ testing framework for writing and running unit tests. The framework provides a set of macros for defining test cases and test assertions. A test case is a set of related tests, and a test assertion is a statement that verifies the test results.

This testing framework only 107 lines.
You can include the testing framework's header file in your program and use the macros provided by the testing framework to write and run tests. This way, you can embed testing code in your program to test it during development.

# Installation
This testing framework does not require installation, just include the header file in your test code.

# Usage
Before writing the test codes in a 'cpp' file, you need to write the 'PURE_TEST_INIT();' macro.


 'pure_report' macro  won't stop the test program, it reports the imformations.
'pure_assert' macro will abort the program when the condition is false. Here is an example.
```
#include "pure_test.hpp"

PURE_TEST_INIT();

void test_add(int i , int j) {
  pure_report((i + j) == 2) << i << ".." << j;
}

void test_assert(int i, int j) {
    pure_assert((i + j) == 2) << "i: "<<i << " j :" << j;
}

int main() {
  pure_test::TestSuite t;
  t.add_test_case("test_add 1+1", []{test_add(1,1);});
  t.add_test_case("test_add 1+2", []{test_add(1,2);});
  t.add_test_case("test add assert", []{test_assert(1,2);});
  t.run();
}
```
output:
```
Running 3 test cases...
Running test case: test_add 1+1...
[PASS] 
Running test case: test_add 1+2...
[FAIL] [test_add][message: 1..2]
Running test case: test add assert...
[assert fail] [tree_test.cc:10] [message: i: 1 j :2]
Abort
```

