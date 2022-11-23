#ifndef ADDAUTOMATON_H
#define ADDAUTOMATON_H

#include <string>
#include "Automaton.h"

using namespace std;

class AddAutomaton : public Automaton {
public:
    AutomatonResult s0(const string &input, size_t currIndex, int currLine) override;

    TestResult testAutomaton() override;
};

#endif // ADDAUTOMATON_H
