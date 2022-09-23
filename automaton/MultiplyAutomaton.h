#ifndef MULTIPLYAUTOMATON_H
#define MULTIPLYAUTOMATON_H

#include <string>
#include "Automaton.h"

using namespace std;

class MultiplyAutomaton : public Automaton {
public:
    AutomatonResult s0(const string& input, size_t currIndex, int currLine) override;
    TestResult testAutomaton() override;
};

#endif // MULTIPLYAUTOMATON_H
