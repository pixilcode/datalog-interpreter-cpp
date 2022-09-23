#include "QueriesAutomaton.h"

AutomatonResult QueriesAutomaton::s0(const string &input, size_t currIndex, int currLine) {
    if (currIndex + 7 <= input.length() && input.substr(currIndex, 7) == "Queries") {
        auto token = Token(TokenType::QUERIES, input.substr(currIndex, 7), currLine);
        return AutomatonSuccess(token, currIndex + 7, currLine);
    } else {
        return sErr();
    }
}

TestResult QueriesAutomaton::testAutomaton() {
    QueriesAutomaton queries;
    auto resultA = queries.start("Queries", 0, 1);
    auto resultB = queries.start("a", 0, 1);
    auto resultC = queries.start("", 0, 1);
    auto resultD = queries.start("Queries abc", 0, 1);

    auto hasValueTests = test::all({
        test::assert(resultA.has_value(), "queries - didn't match Queries"),
        test::assert(!resultB.has_value(), "queries - matched non-Queries 'a'"),
        test::assert(!resultC.has_value(), "queries - matched empty string"),
        test::assert(resultD.has_value(), "queries - didn't match Queries"),
    });

    if (!test::is_ok(hasValueTests)) return hasValueTests;

    auto resultAValue = resultA.value();
    auto resultAToken = resultAValue.token;

    auto resultDValue = resultD.value();
    auto resultDToken = resultDValue.token;

    auto correctValueTests = test::all({
        test::assert(resultAValue.finalIndex == 7, "queries - didn't advance index"),
        test::assert(resultAValue.finalLine == 1, "queries - incorrect line number"),
        test::assert(resultAToken.type == TokenType::QUERIES, "queries - incorrect token type"),
        test::assert(resultAToken.lexeme == "Queries", "queries - incorrect lexeme"),
        test::assert(resultAToken.line == 1, "queries - incorrect line"),

        test::assert(resultDValue.finalIndex == 7, "queries - didn't advance index"),
        test::assert(resultDValue.finalLine == 1, "queries - incorrect line number"),
        test::assert(resultDToken.type == TokenType::QUERIES, "queries - incorrect token type"),
        test::assert(resultDToken.lexeme == "Queries", "queries - incorrect lexeme"),
        test::assert(resultDToken.line == 1, "queries - incorrect line"),
    });

    return test::all({
        hasValueTests,
        correctValueTests
    });
}