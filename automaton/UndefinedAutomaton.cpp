#include <vector>
#include "UndefinedAutomaton.h"

AutomatonResult UndefinedAutomaton::s0(const string &input, int currIndex, int currLine) {
    if (currIndex < input.length()) {
        auto token = Token(TokenType::UNDEFINED, input.substr(currIndex, currIndex + 1), currLine);
        return AutomatonSuccess(token, currIndex + 1, currLine);
    } else {
        return sErr();
    }
}

TestResult UndefinedAutomaton::testAutomaton() {
    UndefinedAutomaton undefined;
    vector<AutomatonResult> results = {
            undefined.start("'", 0, 1),
            undefined.start("$", 0, 1),
            undefined.start("abc", 0, 1),
            undefined.start("'abc'", 0, 1),
    };

    auto hasValueTests = test::all({
        test::assert(results[0].has_value(), "undefined - didn't match undefined (0)"),
        test::assert(results[1].has_value(), "undefined - didn't match undefined (1)"),
        test::assert(results[2].has_value(), "undefined - didn't match undefined (2)"),
        test::assert(results[3].has_value(), "undefined - didn't match undefined (3)"),
    });

    if (!test::is_ok(hasValueTests)) return hasValueTests;

    vector<AutomatonSuccess> successes = {
            results[0].value(),
            results[1].value(),
            results[2].value(),
            results[3].value(),
    };

    auto correctValueTests = test::all({
        test::assert(successes[0].finalIndex == 1, "undefined - didn't advance index (0)"),
        test::assert(successes[1].finalIndex == 1, "undefined - didn't advance index (1)"),
        test::assert(successes[2].finalIndex == 1, "undefined - didn't advance index (2)"),
        test::assert(successes[3].finalIndex == 1, "undefined - didn't advance index (3)"),

        test::assert(successes[0].finalLine == 1, "undefined - advanced line (0)"),
        test::assert(successes[1].finalLine == 1, "undefined - advanced line (1)"),
        test::assert(successes[2].finalLine == 1, "undefined - advanced line (2)"),
        test::assert(successes[3].finalLine == 1, "undefined - advanced line (3)"),

        test::assert(successes[0].token == Token(TokenType::UNDEFINED, "'", 1), "undefined - token didn't match (0)"),
        test::assert(successes[1].token == Token(TokenType::UNDEFINED, "$", 1), "undefined - token didn't match (1)"),
        test::assert(successes[2].token == Token(TokenType::UNDEFINED, "a", 1), "undefined - token didn't match (2)"),
        test::assert(successes[3].token == Token(TokenType::UNDEFINED, "'", 1), "undefined - token didn't match (3)"),
    });

    return test::all({
        hasValueTests,
        correctValueTests
    });
}