#ifndef RIGHT_PARENAUTOMATON_H
#define RIGHT_PARENAUTOMATON_H

#include <string>
#include "Automaton.h"

using namespace std;

class RightParenAutomaton : public Automaton {
public:
    AutomatonResult s0(const string& input, size_t currIndex, int currLine) override;
    TestResult testAutomaton() override;
};

#endif // RIGHT_PARENAUTOMATON_H
