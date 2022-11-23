#ifndef UNDEFINEDAUTOMATON_H
#define UNDEFINEDAUTOMATON_H

#include <string>
#include "Automaton.h"

using namespace std;

class UndefinedAutomaton : public Automaton {
public:
    AutomatonResult s0(const string &input, size_t currIndex, int currLine) override;

    TestResult testAutomaton() override;
};

#endif // UNDEFINEDAUTOMATON_H

