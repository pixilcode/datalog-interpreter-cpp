#ifndef EOFAUTOMATON_H
#define EOFAUTOMATON_H

#include <string>
#include "Automaton.h"

using namespace std;

class EofAutomaton : public Automaton {
public:
    AutomatonResult s0(const string& input, int currIndex, int currLine) override;
    TestResult testAutomaton() override;
};

#endif // EOFAUTOMATON_H

