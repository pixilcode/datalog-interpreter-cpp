#ifndef PROJECT_1_LEXER_H
#define PROJECT_1_LEXER_H

#include <string>
#include <vector>
#include "Token.h"
#include "automaton/all.h"

using namespace std;

namespace lexer {
    typedef vector<Token> Result;
    Result run(const string& code);
    Result nextToken(
        const string& code,
        size_t currIndex,
        int currLine,
        vector<Token> tokens,
        const vector<Automaton*>& automatons
    );
    bool compareResults(AutomatonResult& resultA, AutomatonResult& resultB);
}

#endif //PROJECT_1_LEXER_H
