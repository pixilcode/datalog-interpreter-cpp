#ifndef LEFT_PARENAUTOMATON_H
#define LEFT_PARENAUTOMATON_H

#include <string>
#include "Automaton.h"

using namespace std;

class LeftParenAutomaton : public Automaton {
public:
    AutomatonResult s0(const string& input, size_t currIndex, int currLine) override;
    TestResult testAutomaton() override;
};

#endif // LEFT_PARENAUTOMATON_H
