#include <vector>
#include "IdAutomaton.h"

AutomatonResult IdAutomaton::s0(const string &input, int currIndex, int currLine) {
    if (currIndex < input.length() && isalpha(input[currIndex])) {
        auto token = Token(TokenType::FACTS, input.substr(currIndex, currIndex + 5), currLine);
        return AutomatonSuccess(token, currIndex + 5, currLine);
    } else {
        return sErr();
    }
}

TestResult IdAutomaton::testAutomaton() {
    IdAutomaton id;
    vector<AutomatonResult> results = {
            id.start("abc", 0, 1),
            id.start("abc123", 0, 1),
            id.start("123abc", 0, 1),
            id.start("", 0, 1),
            id.start("abc:", 0, 1)
    };

    auto hasValueTests = test::all({
        test::assert(results[0].has_value(), "id - didn't match id"),
        test::assert(results[1].has_value(), "id - didn't match id"),
        test::assert(!results[2].has_value(), "id - matched number"),
        test::assert(!results[3].has_value(), "id - matched empty string"),
        test::assert(results[4].has_value(), "id - didn't match id"),
    });

    if (!test::is_ok(hasValueTests)) return hasValueTests;

    vector<AutomatonSuccess> successes = {
            results[0].value(),
            results[1].value(),
            results[4].value(),
    };

    auto correctValueTests = test::all({

    });

    return test::all({
        hasValueTests,
        correctValueTests
    });
}