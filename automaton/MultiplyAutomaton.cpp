#include "MultiplyAutomaton.h"

AutomatonResult MultiplyAutomaton::s0(const string &input, int currIndex, int currLine) {
    if (currIndex < input.length() && input[currIndex] == '*') {
        auto token = Token(TokenType::MULTIPLY, input.substr(currIndex, 1), currLine);
        return AutomatonSuccess(token, currIndex + 1, currLine);
    } else {
        return sErr();
    }
}

TestResult MultiplyAutomaton::testAutomaton() {
    MultiplyAutomaton multiply;
    auto resultA = multiply.start("*", 0, 1);
    auto resultB = multiply.start("a", 0, 1);
    auto resultC = multiply.start("", 0, 1);
    auto resultD = multiply.start("* - abc", 0, 1);

    auto hasValueTests = test::all({
        test::assert(resultA.has_value(), "multiply - didn't match multiply"),
        test::assert(!resultB.has_value(), "multiply - matched non-multiply 'a'"),
        test::assert(!resultC.has_value(), "multiply - matched empty string"),
        test::assert(resultD.has_value(), "multiply - didn't match multiply"),
    });

    if (!test::is_ok(hasValueTests)) return hasValueTests;

    auto resultAValue = resultA.value();
    auto resultAToken = resultAValue.token;

    auto resultDValue = resultD.value();
    auto resultDToken = resultDValue.token;

    auto correctValueTests = test::all({
        test::assert(resultAValue.finalIndex == 1, "multiply - didn't advance index"),
        test::assert(resultAValue.finalLine == 1, "multiply - incorrect line number"),
        test::assert(resultAToken.type == TokenType::MULTIPLY, "multiply - incorrect token type"),
        test::assert(resultAToken.lexeme == "*", "multiply - incorrect lexeme"),
        test::assert(resultAToken.line == 1, "multiply - incorrect line"),

        test::assert(resultDValue.finalIndex == 1, "multiply - didn't advance index (3)"),
        test::assert(resultDValue.finalLine == 1, "multiply - incorrect line number (3)"),
        test::assert(resultDToken.type == TokenType::MULTIPLY, "multiply - incorrect token type (3)"),
        test::assert(resultDToken.lexeme == "*", "multiply - incorrect lexeme (3)"),
        test::assert(resultDToken.line == 1, "multiply - incorrect line (3)"),
    });

    return test::all({
        hasValueTests,
        correctValueTests
    });
}
