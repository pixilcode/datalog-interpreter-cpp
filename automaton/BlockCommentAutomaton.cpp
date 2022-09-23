#include <vector>
#include "BlockCommentAutomaton.h"

AutomatonResult BlockCommentAutomaton::s0(const string &input, size_t currIndex, int currLine) {
    if (
            currIndex + 1 < input.length() &&
            input[currIndex] == '#' &&
            input[currIndex + 1] == '|'
    ) {
        return s1(input, currIndex, currIndex + 2, currLine, currLine);
    } else {
        return sErr();
    }
}

AutomatonResult BlockCommentAutomaton::s1(const string &input, int initIndex, size_t currIndex, int initLine, int currLine) {
    if (
            currIndex + 1 < input.length() &&
            input[currIndex] == '|' &&
            input[currIndex + 1] == '#'
    ) {
        auto token = Token(TokenType::COMMENT, input.substr(initIndex, currIndex + 2), initLine);
        return AutomatonSuccess(token, currIndex + 2, currLine);
    } else if(currIndex < input.length()) {
        int nextLine = (input[currIndex] == '\n') ? currLine + 1 : currLine;
        return s1(input, initIndex, currIndex + 1, initLine, nextLine);
    } else {
        auto token = Token(TokenType::UNDEFINED, input.substr(initIndex, currIndex), initLine);
        return AutomatonSuccess(token, currIndex, currLine);
    }
}

TestResult BlockCommentAutomaton::testAutomaton() {
    BlockCommentAutomaton blockComment;
    vector<AutomatonResult> results = {
            blockComment.start("#||#", 0, 1),
            blockComment.start("#|a|#", 0, 1),
            blockComment.start("#|a|b|#", 0, 1),
            blockComment.start("#|a#b|#", 0, 1),
            blockComment.start("#|a\nb|#", 0, 1),
            blockComment.start("#|a", 0, 1),
            blockComment.start("#|a\nb", 0, 1),
            blockComment.start("", 0, 1),
            blockComment.start("#", 0, 1),
            blockComment.start("#a", 0, 1),
            blockComment.start("abc", 0, 1),
    };

    auto hasValueTests = test::all({
        test::assert(results[0].has_value(), "block comment - didn't match block comment (0)"),
        test::assert(results[1].has_value(), "block comment - didn't match block comment (1)"),
        test::assert(results[2].has_value(), "block comment - didn't match block comment (2)"),
        test::assert(results[3].has_value(), "block comment - didn't match block comment (3)"),
        test::assert(results[4].has_value(), "block comment - didn't match block comment (4)"),
        test::assert(results[5].has_value(), "block comment - didn't match unclosed block comment (5)"),
        test::assert(results[6].has_value(), "block comment - didn't match unclosed block comment (6)"),
        test::assert(!results[7].has_value(), "block comment - matched empty string"),
        test::assert(!results[8].has_value(), "block comment - matched line comment (8)"),
        test::assert(!results[9].has_value(), "block comment - matched line comment (9)"),
        test::assert(!results[10].has_value(), "block comment - matched identifier"),
    });

    if (!test::is_ok(hasValueTests)) return hasValueTests;

    vector<AutomatonSuccess> successes = {
            results[0].value(),
            results[1].value(),
            results[2].value(),
            results[3].value(),
            results[4].value(),
            results[5].value(),
            results[6].value(),
    };

    auto correctValueTests = test::all({
        test::assert(successes[0].finalIndex == 4, "block comment - didn't advance index (0)"),
        test::assert(successes[1].finalIndex == 5, "block comment - didn't advance index (1)"),
        test::assert(successes[2].finalIndex == 7, "block comment - didn't advance index (2)"),
        test::assert(successes[3].finalIndex == 7, "block comment - didn't advance index (3)"),
        test::assert(successes[4].finalIndex == 7, "block comment - didn't advance index (4)"),
        test::assert(successes[5].finalIndex == 3, "block comment - didn't advance index (5)"),
        test::assert(successes[6].finalIndex == 5, "block comment - didn't advance index (6)"),

        test::assert(successes[0].finalLine == 1, "block comment - advanced line (0)"),
        test::assert(successes[1].finalLine == 1, "block comment - advanced line (1)"),
        test::assert(successes[2].finalLine == 1, "block comment - advanced line (2)"),
        test::assert(successes[3].finalLine == 1, "block comment - advanced line (3)"),
        test::assert(successes[4].finalLine == 2, "block comment - advanced line (4)"),
        test::assert(successes[5].finalLine == 1, "block comment - advanced line (5)"),
        test::assert(successes[6].finalLine == 2, "block comment - advanced line (6)"),

        test::assert(successes[0].token == Token(TokenType::COMMENT, "#||#", 1), "block comment - token didn't match (0)"),
        test::assert(successes[1].token == Token(TokenType::COMMENT, "#|a|#", 1), "line comment - token didn't match (1)"),
        test::assert(successes[2].token == Token(TokenType::COMMENT, "#|a|b|#", 1), "block comment - token didn't match (2)"),
        test::assert(successes[3].token == Token(TokenType::COMMENT, "#|a#b|#", 1), "block comment - token didn't match (3)"),
        test::assert(successes[4].token == Token(TokenType::COMMENT, "#|a\nb|#", 1), "block comment - token didn't match (4)"),
        test::assert(successes[5].token == Token(TokenType::UNDEFINED, "#|a", 1), "block comment - token didn't match (5)"),
        test::assert(successes[6].token == Token(TokenType::UNDEFINED, "#|a\nb", 1), "block comment - token didn't match (6)"),
    });

    return test::all({
        hasValueTests,
        correctValueTests
    });
}