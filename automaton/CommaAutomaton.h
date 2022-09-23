#ifndef COMMAAUTOMATON_H
#define COMMAAUTOMATON_H

#include <string>
#include "Automaton.h"

using namespace std;

class CommaAutomaton : public Automaton {
public:
    AutomatonResult s0(const string& input, size_t currIndex, int currLine) override;
    TestResult testAutomaton() override;
};

#endif // COMMAAUTOMATON_H
