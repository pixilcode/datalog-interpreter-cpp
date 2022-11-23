#ifndef QUERIESAUTOMATON_H
#define QUERIESAUTOMATON_H

#include <string>
#include "Automaton.h"

using namespace std;

class QueriesAutomaton : public Automaton {
public:
    AutomatonResult s0(const string &input, size_t currIndex, int currLine) override;

    TestResult testAutomaton() override;
};

#endif // QUERIESAUTOMATON_H

