#include <vector>
#include "StringAutomaton.h"

AutomatonResult StringAutomaton::s0(const string &input, int currIndex, int currLine) {
    if (currIndex < input.length() && isalpha(input[currIndex])) {
        return s1(input, currIndex, currIndex + 1, currLine);
    } else {
        return sErr();
    }
}

AutomatonResult StringAutomaton::s1(const std::string &input, int initIndex, int currIndex, int currLine) {
    if (currIndex < input.length() && isalnum(input[currIndex])) {
        return s1(input, initIndex, currIndex + 1, currLine);
    } else {
        auto token = Token(TokenType::ID, input.substr(initIndex, currIndex), currLine);
        return AutomatonSuccess(token, currIndex, currLine);
    }
}

TestResult StringAutomaton::testAutomaton() {
    StringAutomaton string_;
    vector<AutomatonResult> results = {
            string_.start("'abc'", 0, 1),
            string_.start("'abc\n123'", 0, 1),
            string_.start("'can''t'", 0, 1),
            string_.start("''", 0, 1),
            string_.start("'abc':", 0, 1),
            string_.start("'abc", 0, 1),
            string_.start("'abc' 'def'", 0, 1),
            string_.start("", 0, 1),
    };

    auto hasValueTests = test::all({
        test::assert(results[0].has_value(), "string - didn't match string"),
        test::assert(results[1].has_value(), "string - didn't match string with newline"),
        test::assert(results[2].has_value(), "string - didn't match string with apostrophe"),
        test::assert(results[3].has_value(), "string - didn't match empty string"),
        test::assert(results[4].has_value(), "string - didn't match string with following colon"),
        test::assert(results[5].has_value(), "string - didn't match incomplete string"),
        test::assert(results[6].has_value(), "string - didn't match string with following whitespace"),
        test::assert(!results[7].has_value(), "string - matched end of file"),
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
        test::assert(successes[0].finalIndex == 5, "string - didn't advance index (0)"),
        test::assert(successes[1].finalIndex == 9, "string - didn't advance index (1)"),
        test::assert(successes[2].finalIndex == 8, "string - didn't advance index (2)"),
        test::assert(successes[3].finalIndex == 2, "string - didn't advance index (3)"),
        test::assert(successes[4].finalIndex == 5, "string - didn't advance index (4)"),
        test::assert(successes[5].finalIndex == 4, "string - didn't advance index (5)"),
        test::assert(successes[6].finalIndex == 5, "string - didn't advance index (5)"),

        test::assert(successes[0].finalLine == 1, "string - advanced line (0)"),
        test::assert(successes[1].finalLine == 2, "string - didn't advance line (1)"),
        test::assert(successes[2].finalLine == 1, "string - advanced line (2)"),
        test::assert(successes[3].finalLine == 1, "string - advanced line (3)"),
        test::assert(successes[4].finalLine == 1, "string - advanced line (4)"),
        test::assert(successes[5].finalLine == 1, "string - advanced line (5)"),
        test::assert(successes[6].finalLine == 1, "string - advanced line (6)"),

        test::assert(successes[0].token == Token(TokenType::ID, "'abc'", 1), "string - token didn't match (0)"),
        test::assert(successes[1].token == Token(TokenType::ID, "'abc\n123'", 1), "string - token didn't match (1)"),
        test::assert(successes[2].token == Token(TokenType::ID, "'can''t'", 1), "string - token didn't match (2)"),
        test::assert(successes[3].token == Token(TokenType::ID, "''", 1), "string - token didn't match (3)"),
        test::assert(successes[4].token == Token(TokenType::ID, "'abc'", 1), "string - token didn't match (4)"),
        test::assert(successes[5].token == Token(TokenType::UNDEFINED, "'abc", 1), "string - undefined token didn't match (5)"),
        test::assert(successes[6].token == Token(TokenType::ID, "'abc'", 1), "string - token didn't match (6)"),
    });

    return test::all({
        hasValueTests,
        correctValueTests
    });
}