#include <vector>
#include "LineCommentAutomaton.h"

AutomatonResult LineCommentAutomaton::s0(const string &input, int currIndex, int currLine) {
    if (currIndex < input.length() && input[currIndex] == '\'') {
        return s1(input, currIndex, currIndex + 1, currLine, currLine);
    } else {
        return sErr();
    }
}

AutomatonResult LineCommentAutomaton::s1(const string &input, int initIndex, int currIndex, int initLine, int currLine) {
    if (currIndex < input.length() && input[currIndex] == '\'') {
        if (currIndex + 1 < input.length() && input[currIndex + 1] == '\'') {
            return s1(input, initIndex, currIndex + 2, initLine, currLine);
        } else {
            auto token = Token(TokenType::STRING, input.substr(initIndex, currIndex + 1), initLine);
            return AutomatonSuccess(token, currIndex + 1, currLine);
        }
    } else if (currIndex < input.length() && input[currIndex] == '\n') {
        return s1(input, initIndex, currIndex + 1, initLine, currLine + 1);
    } else if (currIndex < input.length()) {
        return s1(input, initIndex, currIndex + 1, initLine, currLine);
    } else {
        auto token = Token(TokenType::UNDEFINED, input.substr(initIndex, currIndex), initLine);
        return AutomatonSuccess(token, currIndex, currLine);
    }
}

TestResult LineCommentAutomaton::testAutomaton() {
    LineCommentAutomaton lineComment;
    vector<AutomatonResult> results = {
            lineComment.start("#", 0, 1),
            lineComment.start("# abc", 0, 1),
            lineComment.start("# abc\n", 0, 1),
            lineComment.start("# abc\n new line", 0, 1),
            lineComment.start("", 0, 1),
            lineComment.start("abc", 0, 1),
    };

    auto hasValueTests = test::all({
        test::assert(results[0].has_value(), "line comment - didn't match line comment (0)"),
        test::assert(results[1].has_value(), "line comment - didn't match line comment (1)"),
        test::assert(results[2].has_value(), "line comment - didn't match line comment (2)"),
        test::assert(results[3].has_value(), "line comment - didn't match line comment (3)"),
        test::assert(!results[4].has_value(), "line comment - matched empty string"),
        test::assert(!results[5].has_value(), "line comment - matched non comment"),
    });

    if (!test::is_ok(hasValueTests)) return hasValueTests;

    vector<AutomatonSuccess> successes = {
            results[0].value(),
            results[1].value(),
            results[2].value(),
            results[3].value(),
    };

    auto correctValueTests = test::all({
        test::assert(successes[0].finalIndex == 1, "line comment - didn't advance index (0)"),
        test::assert(successes[0].finalIndex == 5, "line comment - didn't advance index (1)"),
        test::assert(successes[0].finalIndex == 6, "line comment - didn't advance index (2)"),
        test::assert(successes[0].finalIndex == 6, "line comment - didn't advance index (3)"),

        test::assert(successes[0].finalLine == 1, "line comment - advanced line (0)"),
        test::assert(successes[0].finalLine == 1, "line comment - advanced line (0)"),
        test::assert(successes[0].finalLine == 2, "line comment - advanced line (0)"),
        test::assert(successes[0].finalLine == 2, "line comment - advanced line (0)"),

        test::assert(successes[0].token == Token(TokenType::COMMENT, "#", 1), "line comment - token didn't match (0)"),
        test::assert(successes[0].token == Token(TokenType::COMMENT, "# abc", 1), "line 'abc'comment - token didn't match (0)"),
        test::assert(successes[0].token == Token(TokenType::COMMENT, "# abc", 1), "line comment - token didn't match (0)"),
        test::assert(successes[0].token == Token(TokenType::COMMENT, "# abc", 1), "line comment - token didn't match (0)"),
    });

    return test::all({
        hasValueTests,
        correctValueTests
    });
}