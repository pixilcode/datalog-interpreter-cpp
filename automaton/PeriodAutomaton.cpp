#include "PeriodAutomaton.h"

AutomatonResult PeriodAutomaton::s0(const string &input, int currIndex, int currLine) {
    if (currIndex < input.length() && input[currIndex] == '.') {
        auto token = Token(TokenType::PERIOD, input.substr(currIndex, currIndex + 1), currLine);
        return AutomatonSuccess(token, currIndex + 1, currLine);
    } else {
        return sErr();
    }
}

TestResult PeriodAutomaton::testAutomaton() {
    PeriodAutomaton period;
    auto resultA = period.start(".", 0, 1);
    auto resultB = period.start("a", 0, 1);
    auto resultC = period.start("", 0, 1);
    auto resultD = period.start(".-", 0, 1);

    auto hasValueTests = test::all({
        test::assert(resultA.has_value(), "period - didn't match period"),
        test::assert(!resultB.has_value(), "period - matched non-period 'a'"),
        test::assert(!resultC.has_value(), "period - matched empty string"),
        test::assert(resultD.has_value(), "period - didn't match period")
    });

    if (!test::is_ok(hasValueTests)) return hasValueTests;

    auto resultAValue = resultA.value();
    auto resultAToken = resultAValue.token;

    auto correctValueTests = test::all({
        test::assert(resultAValue.finalIndex == 1, "period - didn't advance index"),
        test::assert(resultAValue.finalLine == 1, "period - incorrect line number"),
        test::assert(resultAToken.type == TokenType::PERIOD, "period - incorrect token type"),
        test::assert(resultAToken.lexeme == ".", "period - incorrect lexeme"),
        test::assert(resultAToken.line == 1, "period - incorrect line")
    });

    return test::all({
        hasValueTests,
        correctValueTests
    });
}
