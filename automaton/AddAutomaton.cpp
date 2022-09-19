#include "AddAutomaton.h"

AutomatonResult AddAutomaton::s0(const string &input, int currIndex, int currLine) {
    if (currIndex < input.length() && input[currIndex] == '+') {
        auto token = Token(TokenType::COLON, input.substr(currIndex, currIndex + 1), currLine);
        return AutomatonSuccess(token, currIndex + 1, currLine);
    } else {
        return sErr();
    }
}

TestResult AddAutomaton::testAutomaton() {
    AddAutomaton add;
    auto resultA = add.start("+", 0, 1);
    auto resultB = add.start("a", 0, 1);
    auto resultC = add.start("", 0, 1);
    auto resultD = add.start("+-", 0, 1);

    auto hasValueTests = test::all({
        test::assert(resultA.has_value(), "add - didn't match add"),
        test::assert(!resultB.has_value(), "add - matched non-add 'a'"),
        test::assert(!resultC.has_value(), "add - matched empty string"),
        test::assert(resultD.has_value(), "add - didn't match add")
    });

    if (!test::is_ok(hasValueTests)) return hasValueTests;

    auto resultAValue = resultA.value();
    auto resultAToken = resultAValue.token;

    auto correctValueTests = test::all({
        test::assert(resultAValue.finalIndex == 1, "add - didn't advance index"),
        test::assert(resultAValue.finalLine == 1, "add - incorrect line number"),
        test::assert(resultAToken.type == TokenType::ADD, "add - incorrect token type"),
        test::assert(resultAToken.lexeme == ":", "add - incorrect lexeme"),
        test::assert(resultAToken.line == 1, "add - incorrect line")
    });

    return test::all({
        hasValueTests,
        correctValueTests
    });
}
