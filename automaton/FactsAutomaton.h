#ifndef FACTSAUTOMATON_H
#define FACTSAUTOMATON_H

#include <string>
#include "Automaton.h"

using namespace std;

class FactsAutomaton : public Automaton {
public:
    AutomatonResult s0(const string& input, size_t currIndex, int currLine) override;
    TestResult testAutomaton() override;
};

#endif // FACTSAUTOMATON_H

