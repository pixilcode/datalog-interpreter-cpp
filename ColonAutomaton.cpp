#include "ColonAutomaton.h"

AutomatonResult ColonAutomaton::s0(const std::string &input, int currIndex, int currLine) {
    if (input[currIndex] == ':') {
        auto token = Token(TokenType::COLON, input.substr(currIndex, currIndex + 1), currLine);
        return AutomatonSuccess(token, currIndex + 1, currLine);
    } else {
        return sErr();
    }
}