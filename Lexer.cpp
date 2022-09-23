#include "Lexer.h"

#include <algorithm>
#include <stdexcept>
#include <utility>

lexer::Result lexer::run(const string& code) {
    vector<Automaton*> automatons = {
            new AddAutomaton(),
            new BlockCommentAutomaton(),
            new ColonAutomaton(),
            new ColonDashAutomaton(),
            new CommaAutomaton(),
            new FactsAutomaton(),
            new IdAutomaton(),
            new LeftParenAutomaton(),
            new LineCommentAutomaton(),
            new MultiplyAutomaton(),
            new PeriodAutomaton(),
            new QueriesAutomaton(),
            new QuestionMarkAutomaton(),
            new RightParenAutomaton(),
            new RulesAutomaton(),
            new SchemesAutomaton(),
            new StringAutomaton(),
            new UndefinedAutomaton(),
    };
    auto result = lexer::nextToken(code, 0, 1, {}, automatons);
    for (auto automaton : automatons) delete automaton;
    return result;
}

lexer::Result lexer::nextToken(const string& code, int currIndex, int currLine, vector<Token> tokens, const vector<Automaton*>& automatons) {
    // Skip whitespace
    if(currIndex < code.size() && isspace(code[currIndex])) {
        int nextLine = (code[currIndex] == '\n') ? currLine + 1 : currLine;
        return lexer::nextToken(code, currIndex + 1, nextLine, std::move(tokens), automatons);
    } else {
        // Run each automaton
        vector<AutomatonResult> autoResults(automatons.size(), nullopt);
        for (int i = 0; i < automatons.size(); i++) {
            autoResults[i] = automatons[i]->start(code, currIndex, currLine);
        }

        // Get the "greatest" result (the result that takes precedence)
        AutomatonResult greatest = *max_element(autoResults.begin(), autoResults.end(), compareResults);

        // If there is a "greatest" token...
        if (greatest.has_value()) {
            // ...add the token to the list of tokens...
            tokens.emplace_back(greatest->token);
            // ...then lex the next token
            return lexer::nextToken(code, greatest->finalIndex, greatest->finalLine, std::move(tokens), automatons);
        }

        // Otherwise, handle the end-of-file case
        else {
            // Check to make sure it's the end of file, then return the list of tokens
            if (currIndex >= code.size()) {
                tokens.emplace_back(TokenType::END_OF_FILE, "", currLine);
                return tokens;
            } else {
                // If it isn't actually the end of the file,
                // it's a bug that the developer needs to fix
                // since the 'UNDEFINED' token should be applied
                // in this case
                throw std::runtime_error("no automatons matched, but didn't reach end of file");
            }
        }
    }
}

bool lexer::compareResults(AutomatonResult& resultA, AutomatonResult& resultB) {
    if (resultA.has_value() && resultB.has_value())
        return resultA->token < resultB->token;
    else if (resultA.has_value() && !resultB.has_value())
        return false;
    else
        return true;
}