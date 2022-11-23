#ifndef PERIODAUTOMATON_H
#define PERIODAUTOMATON_H

#include <string>
#include "Automaton.h"

using namespace std;

class PeriodAutomaton : public Automaton {
public:
    AutomatonResult s0(const string &input, size_t currIndex, int currLine) override;

    TestResult testAutomaton() override;
};

#endif // PERIODAUTOMATON_H
