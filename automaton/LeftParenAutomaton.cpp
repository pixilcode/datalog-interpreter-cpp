#include "LeftParenAutomaton.h"

AutomatonResult LeftParenAutomaton::s0(const string &input, int currIndex, int currLine) {
    if (currIndex < input.length() && input[currIndex] == '(') {
        auto token = Token(TokenType::COLON, input.substr(currIndex, currIndex + 1), currLine);
        return AutomatonSuccess(token, currIndex + 1, currLine);
    } else {
        return sErr();
    }
}

TestResult LeftParenAutomaton::testAutomaton() {
    LeftParenAutomaton leftparen;
    auto resultA = leftparen.start("(", 0, 1);
    auto resultB = leftparen.start("a", 0, 1);
    auto resultC = leftparen.start("", 0, 1);
    auto resultD = leftparen.start("(-", 0, 1);

    auto hasValueTests = test::all({
        test::assert(resultA.has_value(), "leftparen - didn't match leftparen"),
        test::assert(!resultB.has_value(), "leftparen - matched non-leftparen 'a'"),
        test::assert(!resultC.has_value(), "leftparen - matched empty string"),
        test::assert(resultD.has_value(), "leftparen - didn't match leftparen")
    });

    if (!test::is_ok(hasValueTests)) return hasValueTests;

    auto resultAValue = resultA.value();
    auto resultAToken = resultAValue.token;

    auto correctValueTests = test::all({
        test::assert(resultAValue.finalIndex == 1, "leftparen - didn't advance index"),
        test::assert(resultAValue.finalLine == 1, "leftparen - incorrect line number"),
        test::assert(resultAToken.type == TokenType::LEFT_PAREN, "leftparen - incorrect token type"),
        test::assert(resultAToken.lexeme == ":", "leftparen - incorrect lexeme"),
        test::assert(resultAToken.line == 1, "leftparen - incorrect line")
    });

    return test::all({
        hasValueTests,
        correctValueTests
    });
}
