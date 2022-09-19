#include "SchemesAutomaton.h"

AutomatonResult SchemesAutomaton::s0(const string &input, int currIndex, int currLine) {
    if (currIndex < input.length() && input[currIndex] == ':') {
        auto token = Token(TokenType::COLON, input.substr(currIndex, currIndex + 1), currLine);
        return AutomatonSuccess(token, currIndex + 1, currLine);
    } else {
        return sErr();
    }
}

TestResult SchemesAutomaton::testAutomaton() {
    SchemesAutomaton schemes;
    auto resultA = schemes.start("schemes", 0, 1);
    auto resultB = schemes.start("a", 0, 1);
    auto resultC = schemes.start("", 0, 1);
    auto resultD = schemes.start("schemes:", 0, 1);

    auto hasValueTests = test::all({
        test::assert(resultA.has_value(), "schemes - didn't match schemes"),
        test::assert(!resultB.has_value(), "schemes - matched non-schemes 'a'"),
        test::assert(!resultC.has_value(), "schemes - matched empty string"),
        test::assert(resultD.has_value(), "schemes - didn't match schemes")
    });

    if (!test::is_ok(hasValueTests)) return hasValueTests;

    auto resultAValue = resultA.value();
    auto resultAToken = resultAValue.token;

    auto correctValueTests = test::all({
        test::assert(resultAValue.finalIndex == 7, "schemes - didn't advance index"),
        test::assert(resultAValue.finalLine == 1, "schemes - incorrect line number"),
        test::assert(resultAToken.type == TokenType::SCHEMES, "schemes - incorrect token type"),
        test::assert(resultAToken.lexeme == ":", "schemes - incorrect lexeme"),
        test::assert(resultAToken.line == 1, "schemes - incorrect line")
    });

    return test::all({
        hasValueTests,
        correctValueTests
    });
}