#ifndef IDAUTOMATON_H
#define IDAUTOMATON_H

#include <string>
#include "Automaton.h"

using namespace std;

class IdAutomaton : public Automaton {
public:
    AutomatonResult s0(const string &input, size_t currIndex, int currLine) override;

    AutomatonResult s1(const string &input, size_t initIndex, size_t currIndex, int currLine);

    TestResult testAutomaton() override;
};

#endif // IDAUTOMATON_H

