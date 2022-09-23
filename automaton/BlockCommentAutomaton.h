#ifndef BLOCKCOMMENTAUTOMATON_H
#define BLOCKCOMMENTAUTOMATON_H

#include <string>
#include "Automaton.h"

using namespace std;

class BlockCommentAutomaton : public Automaton {
public:
    AutomatonResult s0(const string& input, int currIndex, int currLine) override;
    AutomatonResult s1(const string& input, int initIndex, int currIndex, int initLine, int currLine);
    TestResult testAutomaton() override;
};

#endif // BLOCKCOMMENTAUTOMATON_H

