#ifndef Q_MARKAUTOMATON_H
#define Q_MARKAUTOMATON_H

#include <string>
#include "Automaton.h"

using namespace std;

class QuestionMarkAutomaton : public Automaton {
public:
    AutomatonResult s0(const string& input, int currIndex, int currLine) override;
    TestResult testAutomaton() override;
};

#endif // Q_MARKAUTOMATON_H
