#include "QuestionMarkAutomaton.h"

AutomatonResult QuestionMarkAutomaton::s0(const string &input, int currIndex, int currLine) {
    if (currIndex < input.length() && input[currIndex] == '?') {
        auto token = Token(TokenType::COLON, input.substr(currIndex, currIndex + 1), currLine);
        return AutomatonSuccess(token, currIndex + 1, currLine);
    } else {
        return sErr();
    }
}

TestResult QuestionMarkAutomaton::testAutomaton() {
    QuestionMarkAutomaton questionmark;
    auto resultA = questionmark.start("?", 0, 1);
    auto resultB = questionmark.start("a", 0, 1);
    auto resultC = questionmark.start("", 0, 1);
    auto resultD = questionmark.start("?-", 0, 1);

    auto hasValueTests = test::all({
        test::assert(resultA.has_value(), "questionmark - didn't match questionmark"),
        test::assert(!resultB.has_value(), "questionmark - matched non-questionmark 'a'"),
        test::assert(!resultC.has_value(), "questionmark - matched empty string"),
        test::assert(resultD.has_value(), "questionmark - didn't match questionmark")
    });

    if (!test::is_ok(hasValueTests)) return hasValueTests;

    auto resultAValue = resultA.value();
    auto resultAToken = resultAValue.token;

    auto correctValueTests = test::all({
        test::assert(resultAValue.finalIndex == 1, "questionmark - didn't advance index"),
        test::assert(resultAValue.finalLine == 1, "questionmark - incorrect line number"),
        test::assert(resultAToken.type == TokenType::Q_MARK, "questionmark - incorrect token type"),
        test::assert(resultAToken.lexeme == ":", "questionmark - incorrect lexeme"),
        test::assert(resultAToken.line == 1, "questionmark - incorrect line")
    });

    return test::all({
        hasValueTests,
        correctValueTests
    });
}
