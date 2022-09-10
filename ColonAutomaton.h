#ifndef COLONAUTOMATON_H
#define COLONAUTOMATON_H

#include "Automaton.h"

class ColonAutomaton : public Automaton
{
public:
    AutomatonResult s0(const std::string &input, int currIndex, int currLine);
};

#endif // COLONAUTOMATON_H

