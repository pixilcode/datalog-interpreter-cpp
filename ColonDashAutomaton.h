#ifndef PROJECT_1_COLONDASHAUTOMATON_H
#define PROJECT_1_COLONDASHAUTOMATON_H

#include <string>
#include "Automaton.h"

class ColonDashAutomaton : public Automaton {
private:
    AutomatonResult s1(const string& input, int initialIndex, int currIndex, int currLine);

public:
    AutomatonResult s0(const string& input, int currIndex, int currLine) override;
    TestResult testAutomaton() override;
};

#endif //PROJECT_1_COLONDASHAUTOMATON_H
