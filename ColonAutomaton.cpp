#include "ColonAutomaton.h"

AutomatonResult ColonAutomaton::s0(const string &input, int currIndex, int currLine) {
    if (input[currIndex] == ':') {
        auto token = Token(TokenType::COLON, input.substr(currIndex, currIndex + 1), currLine);
        return AutomatonSuccess(token, currIndex + 1, currLine);
    } else {
        return sErr();
    }
}

TestResult ColonAutomaton::testAutomaton() {
    ColonAutomaton colon;
    auto resultA = colon.start(":", 0, 1);
    auto resultB = colon.start("a", 0, 1);



    return test::all({
        test::assert(resultA.has_value(), "colon - didn't match colon"),
        test::assert(!resultA.has_value(), "colon - matched non-colon")
    });
}