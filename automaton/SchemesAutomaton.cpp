#include "SchemesAutomaton.h"

AutomatonResult SchemesAutomaton::s0(const string &input, size_t currIndex, int currLine) {
    if (currIndex + 7 <= input.length() && input.substr(currIndex, 7) == "Schemes") {
        auto token = Token(TokenType::SCHEMES, input.substr(currIndex, 7), currLine);
        return AutomatonSuccess(token, currIndex + 7, currLine);
    } else {
        return sErr();
    }
}

TestResult SchemesAutomaton::testAutomaton() {
    SchemesAutomaton schemes;
    auto resultA = schemes.start("Schemes", 0, 1);
    auto resultB = schemes.start("a", 0, 1);
    auto resultC = schemes.start("", 0, 1);
    auto resultD = schemes.start("Schemes abc", 0, 1);

    auto hasValueTests = test::all({
                                           test::assert(resultA.has_value(), "schemes - didn't match Schemes"),
                                           test::assert(!resultB.has_value(), "schemes - matched non-Schemes 'a'"),
                                           test::assert(!resultC.has_value(), "schemes - matched empty string"),
                                           test::assert(resultD.has_value(), "schemes - didn't match Schemes"),
                                   });

    if (!test::is_ok(hasValueTests)) return hasValueTests;

    auto resultAValue = resultA.value();
    auto resultAToken = resultAValue.token;

    auto resultDValue = resultD.value();
    auto resultDToken = resultDValue.token;

    auto correctValueTests = test::all({
                                               test::assert(resultAValue.finalIndex == 7,
                                                            "schemes - didn't advance index"),
                                               test::assert(resultAValue.finalLine == 1,
                                                            "schemes - incorrect line number"),
                                               test::assert(resultAToken.type == TokenType::SCHEMES,
                                                            "schemes - incorrect token type"),
                                               test::assert(resultAToken.lexeme == "Schemes",
                                                            "schemes - incorrect lexeme"),
                                               test::assert(resultAToken.line == 1, "schemes - incorrect line"),

                                               test::assert(resultDValue.finalIndex == 7,
                                                            "schemes - didn't advance index"),
                                               test::assert(resultDValue.finalLine == 1,
                                                            "schemes - incorrect line number"),
                                               test::assert(resultDToken.type == TokenType::SCHEMES,
                                                            "schemes - incorrect token type"),
                                               test::assert(resultDToken.lexeme == "Schemes",
                                                            "schemes - incorrect lexeme"),
                                               test::assert(resultDToken.line == 1, "schemes - incorrect line"),
                                       });

    return test::all({
                             hasValueTests,
                             correctValueTests
                     });
}