#ifndef AUTOMATON_H
#define AUTOMATON_H
#include <optional>
#include <tuple>
#include <utility>
#include "../Token.h"
#include "../Test.h"

using namespace std;

struct AutomatonSuccess {
    Token token;
    int finalIndex;
    int finalLine;

    AutomatonSuccess(Token token, int finalIndex, int finalLine):
            token(std::move(token)),
            finalIndex(finalIndex),
            finalLine(finalLine) {}
};

typedef optional<AutomatonSuccess> AutomatonResult;

class Automaton {
public:
    virtual AutomatonResult s0(const string& input, size_t currIndex, int currLine) = 0;
    AutomatonResult start(const string& input, size_t currIndex, int currLine) {
        return s0(input, currIndex, currLine);
    }

    static AutomatonResult sErr() {
        return nullopt;
    }

    virtual TestResult testAutomaton() = 0;
    virtual ~Automaton() = default;
};

#endif // AUTOMATON_H

