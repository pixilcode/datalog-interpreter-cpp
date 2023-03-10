#include "FactsAutomaton.h"

AutomatonResult FactsAutomaton::s0(const string &input, size_t currIndex, int currLine) {
    if (currIndex + 5 <= input.length() && input.substr(currIndex, 5) == "Facts") {
        auto token = Token(TokenType::FACTS, input.substr(currIndex, 5), currLine);
        return AutomatonSuccess(token, currIndex + 5, currLine);
    } else {
        return sErr();
    }
}

TestResult FactsAutomaton::testAutomaton() {
    FactsAutomaton facts;
    auto resultA = facts.start("Facts", 0, 1);
    auto resultB = facts.start("a", 0, 1);
    auto resultC = facts.start("", 0, 1);
    auto resultD = facts.start("Facts abc", 0, 1);

    auto hasValueTests = test::all({
                                           test::assert(resultA.has_value(), "facts - didn't match Facts"),
                                           test::assert(!resultB.has_value(), "facts - matched non-Facts 'a'"),
                                           test::assert(!resultC.has_value(), "facts - matched empty string"),
                                           test::assert(resultD.has_value(), "facts - didn't match Facts"),
                                   });

    if (!test::is_ok(hasValueTests)) return hasValueTests;

    auto resultAValue = resultA.value();
    auto resultAToken = resultAValue.token;

    auto resultDValue = resultD.value();
    auto resultDToken = resultDValue.token;

    auto correctValueTests = test::all({
                                               test::assert(resultAValue.finalIndex == 5,
                                                            "facts - didn't advance index"),
                                               test::assert(resultAValue.finalLine == 1,
                                                            "facts - incorrect line number"),
                                               test::assert(resultAToken.type == TokenType::FACTS,
                                                            "facts - incorrect token type"),
                                               test::assert(resultAToken.lexeme == "Facts", "facts - incorrect lexeme"),
                                               test::assert(resultAToken.line == 1, "facts - incorrect line"),

                                               test::assert(resultDValue.finalIndex == 5,
                                                            "facts - didn't advance index"),
                                               test::assert(resultDValue.finalLine == 1,
                                                            "facts - incorrect line number"),
                                               test::assert(resultDToken.type == TokenType::FACTS,
                                                            "facts - incorrect token type"),
                                               test::assert(resultDToken.lexeme == "Facts", "facts - incorrect lexeme"),
                                               test::assert(resultDToken.line == 1, "facts - incorrect line"),
                                       });

    return test::all({
                             hasValueTests,
                             correctValueTests
                     });
}