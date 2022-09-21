#include <vector>
#include "IdAutomaton.h"

AutomatonResult IdAutomaton::s0(const string &input, int currIndex, int currLine) {
    if (currIndex < input.length() && isalpha(input[currIndex])) {
        return s1(input, currIndex, currIndex + 1, currLine);
    } else {
        return sErr();
    }
}

AutomatonResult IdAutomaton::s1(const std::string &input, int initIndex, int currIndex, int currLine) {
    if (currIndex < input.length() && isalnum(input[currIndex])) {
        return s1(input, initIndex, currIndex + 1, currLine);
    } else {
        auto token = Token(TokenType::ID, input.substr(initIndex, currIndex), currLine);
        return AutomatonSuccess(token, currIndex, currLine);
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
        test::assert(successes[0].finalIndex == 3, "id - didn't advance index (0)"),
        test::assert(successes[1].finalIndex == 6, "id - didn't advance index (1)"),
        test::assert(successes[2].finalIndex == 3, "id - didn't advance index (2)"),
        test::assert(successes[0].finalLine == 1, "id - advanced line (0)"),
        test::assert(successes[1].finalLine == 1, "id - advanced line (1)"),
        test::assert(successes[2].finalLine == 1, "id - advanced line (2)"),
        test::assert(successes[0].token == Token(TokenType::ID, "abc", 1), "id - token didn't match (0)"),
    });

    return test::all({
        hasValueTests,
        correctValueTests
    });
}