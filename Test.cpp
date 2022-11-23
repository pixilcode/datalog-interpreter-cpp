#include "Test.h"

namespace test {
    TestResult ok() {
        return {monostate()};
    }

    TestResult error(const string &message) {
        return {message};
    }

    bool is_ok(const TestResult &result) {
        return holds_alternative<Ok>(result);
    }

    string get_error_message(const TestResult &result) {
        return get<Error>(result);
    }

    TestResult assert(bool condition, const string &errorMessage) {
        return (condition) ?
               ok() :
               error(errorMessage);
    }

    TestResult all(const list<TestResult> &results) {
        for (auto result: results)
            if (!is_ok(result)) return result;
        return ok();
    }
}