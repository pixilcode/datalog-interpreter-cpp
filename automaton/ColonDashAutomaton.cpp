#include <optional>
#include <vector>
#include "ColonDashAutomaton.h"

AutomatonResult ColonDashAutomaton::s0(const string& input, int currIndex, int currLine) {
    return (currIndex < input.length() && input[currIndex] == ':') ?
        s1(input, currIndex, currIndex + 1, currLine) :
        sErr();
}

AutomatonResult ColonDashAutomaton::s1(const string& input, int initialIndex, int currIndex, int currLine) {
    if (currIndex < input.length() && input[currIndex] == '-') {
        auto token = Token(TokenType::COLON_DASH, input.substr(initialIndex, currIndex + 1), currLine);
        return AutomatonSuccess(token, currIndex + 1, currLine);
    } else {
        return sErr();
    }
}

TestResult ColonDashAutomaton::testAutomaton() {
    ColonDashAutomaton colonDash;
    vector<AutomatonResult> results = {
            colonDash.start(":-", 0, 1),
            colonDash.start(":", 0, 1),
            colonDash.start("", 0, 1),
            colonDash.start(":-:", 0, 1),
            colonDash.start("abc", 0, 1)
    };

    return test::all({
        test::assert(results[0].has_value(), "colondash - didn't match colondash"),
        test::assert(!results[1].has_value(), "colondash - matched non-colondash value ':'"),
        test::assert(!results[2].has_value(), "colondash - matched empty string"),
        test::assert(results[3].has_value(), "colondash - didn't match colondash in ':-:'"),
        test::assert(!results[4].has_value(), "colondash - matched non-colondash in 'abc'"),
    });
}