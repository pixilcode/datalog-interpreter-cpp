#include "RulesAutomaton.h"

AutomatonResult RulesAutomaton::s0(const string &input, size_t currIndex, int currLine) {
    if (currIndex + 5 <= input.length() && input.substr(currIndex, 5) == "Rules") {
        auto token = Token(TokenType::RULES, input.substr(currIndex, 5), currLine);
        return AutomatonSuccess(token, currIndex + 5, currLine);
    } else {
        return sErr();
    }
}

TestResult RulesAutomaton::testAutomaton() {
    RulesAutomaton rules;
    auto resultA = rules.start("Rules", 0, 1);
    auto resultB = rules.start("a", 0, 1);
    auto resultC = rules.start("", 0, 1);
    auto resultD = rules.start("Rules abc", 0, 1);

    auto hasValueTests = test::all({
        test::assert(resultA.has_value(), "rules - didn't match Rules"),
        test::assert(!resultB.has_value(), "rules - matched non-Rules 'a'"),
        test::assert(!resultC.has_value(), "rules - matched empty string"),
        test::assert(resultD.has_value(), "rules - didn't match Rules"),
    });

    if (!test::is_ok(hasValueTests)) return hasValueTests;

    auto resultAValue = resultA.value();
    auto resultAToken = resultAValue.token;

    auto resultDValue = resultD.value();
    auto resultDToken = resultDValue.token;

    auto correctValueTests = test::all({
        test::assert(resultAValue.finalIndex == 5, "rules - didn't advance index"),
        test::assert(resultAValue.finalLine == 1, "rules - incorrect line number"),
        test::assert(resultAToken.type == TokenType::RULES, "rules - incorrect token type"),
        test::assert(resultAToken.lexeme == "Rules", "rules - incorrect lexeme"),
        test::assert(resultAToken.line == 1, "rules - incorrect line"),

        test::assert(resultDValue.finalIndex == 5, "rules - didn't advance index"),
        test::assert(resultDValue.finalLine == 1, "rules - incorrect line number"),
        test::assert(resultDToken.type == TokenType::RULES, "rules - incorrect token type"),
        test::assert(resultDToken.lexeme == "Rules", "rules - incorrect lexeme"),
        test::assert(resultDToken.line == 1, "rules - incorrect line"),
    });

    return test::all({
        hasValueTests,
        correctValueTests
    });
}