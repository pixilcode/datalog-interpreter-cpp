#ifndef PROJECT_1_TEST_H
#define PROJECT_1_TEST_H

#include <variant>
#include <string>
#include <list>

using namespace std;

typedef monostate Ok;
typedef string Error;
typedef variant<Ok, Error> TestResult;

namespace test {
    TestResult ok();
    TestResult error(const string& message);
    bool is_ok(const TestResult& result);
    string get_error_message(const TestResult& result);
    TestResult assert(bool condition, const string& errorMessage);
    TestResult all(const list<TestResult>& results);
}

#endif //PROJECT_1_TEST_H
