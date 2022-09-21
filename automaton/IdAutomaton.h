#ifndef IDAUTOMATON_H
#define IDAUTOMATON_H

#include <string>
#include "Automaton.h"

using namespace std;

class IdAutomaton : public Automaton {
public:
    AutomatonResult s0(const string& input, int currIndex, int currLine) override;
    AutomatonResult s1(const string& input, int initIndex, int currIndex, int currLine);
    TestResult testAutomaton() override;
};

#endif // IDAUTOMATON_H

