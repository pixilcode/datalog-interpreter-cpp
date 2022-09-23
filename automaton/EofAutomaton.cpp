#include <vector>
#include "EofAutomaton.h"

AutomatonResult EofAutomaton::s0(const string &input, int currIndex, int currLine) {
    if (currIndex >= input.length()) {
        auto token = Token(TokenType::END_OF_FILE, input.substr(currIndex, currIndex), currLine);
        return AutomatonSuccess(token, currIndex, currLine);
    } else {
        return sErr();
    }
}

TestResult EofAutomaton::testAutomaton() {
    EofAutomaton eof;
    vector<AutomatonResult> results = {
            eof.start("", 0, 1),
            eof.start("a", 0, 1),
            eof.start("\n", 0, 1),
    };

    auto hasValueTests = test::all({
        test::assert(results[0].has_value(), "eof - didn't match eof (0)"),
        test::assert(!results[1].has_value(), "eof - matched character (1)"),
        test::assert(!results[2].has_value(), "eof - matched newline (2)"),
    });

    if (!test::is_ok(hasValueTests)) return hasValueTests;

    vector<AutomatonSuccess> successes = {
            results[0].value(),
    };

    auto correctValueTests = test::all({
        test::assert(successes[0].finalIndex == 0, "eof - didn't advance index (0)"),

        test::assert(successes[0].finalLine == 1, "eof - advanced line (0)"),

        test::assert(successes[0].token == Token(TokenType::END_OF_FILE, "", 1), "eof - token didn't match (0)"),
    });

    return test::all({
        hasValueTests,
        correctValueTests
    });
}