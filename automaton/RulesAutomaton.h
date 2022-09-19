#ifndef RULESAUTOMATON_H
#define RULESAUTOMATON_H

#include <string>
#include "Automaton.h"

using namespace std;

class RulesAutomaton : public Automaton {
public:
    AutomatonResult s0(const string& input, int currIndex, int currLine) override;
    TestResult testAutomaton() override;
};

#endif // RULESAUTOMATON_H

