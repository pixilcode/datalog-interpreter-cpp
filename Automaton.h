#ifndef AUTOMATON_H
#define AUTOMATON_H
#include <optional>
#include <tuple>
#include <utility>
#include "Token.h"

using namespace std;

struct AutomatonSuccess {
    Token token;
    int finalIndex;
    int finalLine;

    AutomatonSuccess(Token token, int finalIndex, int finalLine):
            token(move(token)),
            finalIndex(finalIndex),
            finalLine(finalLine) {}
};

typedef optional<AutomatonSuccess> AutomatonResult;

class Automaton {
public:
    AutomatonResult start(const string& input, int currIndex, int currLine) {
        return s0(input, currIndex, currLine);
    }

    virtual AutomatonResult s0(const string& input, int currIndex, int currLine) = 0;

    AutomatonResult sErr() {
        return nullopt;
    }
};

#endif // AUTOMATON_H

