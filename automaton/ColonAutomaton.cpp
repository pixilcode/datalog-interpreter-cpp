#include "ColonAutomaton.h"

AutomatonResult ColonAutomaton::s0(const string &input, size_t currIndex, int currLine) {
    if (currIndex < input.length() && input[currIndex] == ':') {
        auto token = Token(TokenType::COLON, input.substr(currIndex, 1), currLine);
        return AutomatonSuccess(token, currIndex + 1, currLine);
    } else {
        return sErr();
    }
}

TestResult ColonAutomaton::testAutomaton() {
    ColonAutomaton colon;
    auto resultA = colon.start(":", 0, 1);
    auto resultB = colon.start("a", 0, 1);
    auto resultC = colon.start("", 0, 1);
    auto resultD = colon.start(": - abc", 0, 1);

    auto hasValueTests = test::all({
        test::assert(resultA.has_value(), "colon - didn't match colon"),
        test::assert(!resultB.has_value(), "colon - matched non-colon 'a'"),
        test::assert(!resultC.has_value(), "colon - matched empty string"),
        test::assert(resultD.has_value(), "colon - didn't match colon"),
    });

    if (!test::is_ok(hasValueTests)) return hasValueTests;

    auto resultAValue = resultA.value();
    auto resultAToken = resultAValue.token;

    auto resultDValue = resultD.value();
    auto resultDToken = resultDValue.token;

    auto correctValueTests = test::all({
        test::assert(resultAValue.finalIndex == 1, "colon - didn't advance index"),
        test::assert(resultAValue.finalLine == 1, "colon - incorrect line number"),
        test::assert(resultAToken.type == TokenType::COLON, "colon - incorrect token type"),
        test::assert(resultAToken.lexeme == ":", "colon - incorrect lexeme"),
        test::assert(resultAToken.line == 1, "colon - incorrect line"),

        test::assert(resultDValue.finalIndex == 1, "colon - didn't advance index (3)"),
        test::assert(resultDValue.finalLine == 1, "colon - incorrect line number (3)"),
        test::assert(resultDToken.type == TokenType::COLON, "colon - incorrect token type (3)"),
        test::assert(resultDToken.lexeme == ":", "colon - incorrect lexeme (3)"),
        test::assert(resultDToken.line == 1, "colon - incorrect line (3)"),
    });

    return test::all({
        hasValueTests,
        correctValueTests
    });
}
