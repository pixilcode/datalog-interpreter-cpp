#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include "automaton/all.h" // include all automatons
#include "Lexer.h"
#include "parser.h"

void runTests();

int main(int argc, char** argv) {
    bool debug = std::getenv("DEBUG") != nullptr;

    // Debug
    if (debug) {
        runTests();
    }

    // Check for correct number of args
    if (argc != 2 && !debug) {
        cout << "ERROR: must provide datalog file" << endl;
        return 1;
    } else if (argc != 2) {
        cout << "Exiting..." << endl;
        return 0;
    }

    // Read in the file
    string fileLoc = argv[1];
    ifstream inputFile(fileLoc);

    if (inputFile.fail()) {
        cout << "ERROR: couldn't read file '" << fileLoc << "'" << endl;
        return 1;
    }

    stringstream contents;
    contents << inputFile.rdbuf();

    // Lex the inputs
    auto result = lexer::run(contents.str());

    // Filter out comments
    vector<Token> filtered;
    for (const Token& token : result) {
        if (token.type != TokenType::COMMENT)
            filtered.push_back(token);
    }

    try {
        // Parse the inputs
        auto parseAst = parser::parse(filtered);
        cout << "Success!" << endl;
        cout << parseAst.second.toString();
    } catch(parser::Error& error) {
        // Handle the error
        cout << "Failure!" << endl;
        if (debug) cout << "  " << error.message << endl;
        cout << "  " << error.token << endl;
    }

    return 0;
}

void runTests() {
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

    cout << "running automaton tests..." << endl;
    for(auto automaton : automatons) {
        auto testResult = automaton->testAutomaton();
        if (!test::is_ok(testResult))
            cout << "ERROR: " << test::get_error_message(testResult) << endl;
        delete automaton;
    }
    cout << "done!" << endl;
}
