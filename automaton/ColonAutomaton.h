#ifndef COLONAUTOMATON_H
#define COLONAUTOMATON_H

#include <string>
#include "Automaton.h"

using namespace std;

class ColonAutomaton : public Automaton {
public:
    AutomatonResult s0(const string& input, size_t currIndex, int currLine) override;
    TestResult testAutomaton() override;
};

#endif // COLONAUTOMATON_H
