#include "CommaAutomaton.h"

AutomatonResult CommaAutomaton::s0(const string &input, int currIndex, int currLine) {
    if (currIndex < input.length() && input[currIndex] == ',') {
        auto token = Token(TokenType::COMMA, input.substr(currIndex, 1), currLine);
        return AutomatonSuccess(token, currIndex + 1, currLine);
    } else {
        return sErr();
    }
}

TestResult CommaAutomaton::testAutomaton() {
    CommaAutomaton comma;
    auto resultA = comma.start(",", 0, 1);
    auto resultB = comma.start("a", 0, 1);
    auto resultC = comma.start("", 0, 1);
    auto resultD = comma.start(", - abc", 0, 1);

    auto hasValueTests = test::all({
        test::assert(resultA.has_value(), "comma - didn't match comma"),
        test::assert(!resultB.has_value(), "comma - matched non-comma 'a'"),
        test::assert(!resultC.has_value(), "comma - matched empty string"),
        test::assert(resultD.has_value(), "comma - didn't match comma"),
    });

    if (!test::is_ok(hasValueTests)) return hasValueTests;

    auto resultAValue = resultA.value();
    auto resultAToken = resultAValue.token;

    auto resultDValue = resultD.value();
    auto resultDToken = resultDValue.token;

    auto correctValueTests = test::all({
        test::assert(resultAValue.finalIndex == 1, "comma - didn't advance index"),
        test::assert(resultAValue.finalLine == 1, "comma - incorrect line number"),
        test::assert(resultAToken.type == TokenType::COMMA, "comma - incorrect token type"),
        test::assert(resultAToken.lexeme == ",", "comma - incorrect lexeme"),
        test::assert(resultAToken.line == 1, "comma - incorrect line"),

        test::assert(resultDValue.finalIndex == 1, "comma - didn't advance index (3)"),
        test::assert(resultDValue.finalLine == 1, "comma - incorrect line number (3)"),
        test::assert(resultDToken.type == TokenType::COMMA, "comma - incorrect token type (3)"),
        test::assert(resultDToken.lexeme == ",", "comma - incorrect lexeme (3)"),
        test::assert(resultDToken.line == 1, "comma - incorrect line (3)"),
    });

    return test::all({
        hasValueTests,
        correctValueTests
    });
}
