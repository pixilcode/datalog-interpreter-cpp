#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "automaton/all.h" // include all automatons
#include "Lexer.h"

void runTests();

int main(int argc, char** argv) {
    // Debug
    if (std::getenv("DEBUG") != nullptr) {
        runTests();
        return 0;
    }

    // Check for correct number of args
    if (argc != 2) {
        cout << "ERROR: must provide datalog file" << endl;
        return 1;
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

    // Print out the resulting tokens
    for (auto token : result) cout << token << endl;
    cout << "Total Tokens = " << result.size() << endl;

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
