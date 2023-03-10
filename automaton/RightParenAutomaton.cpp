#include "RightParenAutomaton.h"

AutomatonResult RightParenAutomaton::s0(const string &input, size_t currIndex, int currLine) {
    if (currIndex < input.length() && input[currIndex] == ')') {
        auto token = Token(TokenType::RIGHT_PAREN, input.substr(currIndex, 1), currLine);
        return AutomatonSuccess(token, currIndex + 1, currLine);
    } else {
        return sErr();
    }
}

TestResult RightParenAutomaton::testAutomaton() {
    RightParenAutomaton rightparen;
    auto resultA = rightparen.start(")", 0, 1);
    auto resultB = rightparen.start("a", 0, 1);
    auto resultC = rightparen.start("", 0, 1);
    auto resultD = rightparen.start(") - abc", 0, 1);

    auto hasValueTests = test::all({
                                           test::assert(resultA.has_value(), "rightparen - didn't match rightparen"),
                                           test::assert(!resultB.has_value(),
                                                        "rightparen - matched non-rightparen 'a'"),
                                           test::assert(!resultC.has_value(), "rightparen - matched empty string"),
                                           test::assert(resultD.has_value(), "rightparen - didn't match rightparen"),
                                   });

    if (!test::is_ok(hasValueTests)) return hasValueTests;

    auto resultAValue = resultA.value();
    auto resultAToken = resultAValue.token;

    auto resultDValue = resultD.value();
    auto resultDToken = resultDValue.token;

    auto correctValueTests = test::all({
                                               test::assert(resultAValue.finalIndex == 1,
                                                            "rightparen - didn't advance index"),
                                               test::assert(resultAValue.finalLine == 1,
                                                            "rightparen - incorrect line number"),
                                               test::assert(resultAToken.type == TokenType::RIGHT_PAREN,
                                                            "rightparen - incorrect token type"),
                                               test::assert(resultAToken.lexeme == ")",
                                                            "rightparen - incorrect lexeme"),
                                               test::assert(resultAToken.line == 1, "rightparen - incorrect line"),

                                               test::assert(resultDValue.finalIndex == 1,
                                                            "rightparen - didn't advance index (3)"),
                                               test::assert(resultDValue.finalLine == 1,
                                                            "rightparen - incorrect line number (3)"),
                                               test::assert(resultDToken.type == TokenType::RIGHT_PAREN,
                                                            "rightparen - incorrect token type (3)"),
                                               test::assert(resultDToken.lexeme == ")",
                                                            "rightparen - incorrect lexeme (3)"),
                                               test::assert(resultDToken.line == 1, "rightparen - incorrect line (3)"),
                                       });

    return test::all({
                             hasValueTests,
                             correctValueTests
                     });
}
