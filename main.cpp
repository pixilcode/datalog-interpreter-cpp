#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include "automaton/all.h" // include all automatons
#include "Lexer.h"
#include "parser.h"
#include "Interpreter.h"

void runTests();

int main(int argc, char **argv) {
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
    for (const Token &token: result) {
        if (token.type != TokenType::COMMENT)
            filtered.push_back(token);
    }

    try {
        // Parse the inputs
        auto parseAst = parser::parse(filtered);
        auto interpreter = Interpreter(parseAst.second);
        auto [rulesEval, numPasses, queryResults] = interpreter.runQuery();

        cout << "Rule Evaluation" << endl;
        for (const auto &[rule, relation]: rulesEval) {
            cout << rule.toString(false) << endl;

            auto header = relation.getHeader();
            auto tuples = relation.getTuples();
            for (const auto &tuple: tuples) {
                auto values = tuple.getValues();

                cout << "  ";
                for (size_t i = 0; i < values.size(); i++) {
                    if (i > 0) cout << ", ";
                    cout << header.getAttributes().at(i);
                    cout << "=";
                    cout << values.at(i);
                }
                cout << endl;
            }
        }

        cout << endl << "Schemes populated after " << numPasses << " passes through the Rules." << endl;

        cout << endl << "Query Evaluation" << endl;
        for (const auto &queryResult: queryResults) {
            bool success = !queryResult.second.empty();

            // Print out query and success message
            string message = (success) ?
                             "Yes(" + to_string(queryResult.second.size()) + ")" :
                             "No";
            cout << queryResult.first.toString(false) << " " << message << endl;

            // Print out relation if successful and if the attributes aren't empty
            if (success && queryResult.second.hasAttributes()) {
                auto header = queryResult.second.getHeader();
                auto tuples = queryResult.second.getTuples();
                for (const auto &tuple: tuples) {
                    auto values = tuple.getValues();

                    cout << "  ";
                    for (size_t i = 0; i < values.size(); i++) {
                        if (i > 0) cout << ", ";
                        cout << header.getAttributes().at(i);
                        cout << "=";
                        cout << values.at(i);
                    }
                    cout << endl;
                }
            }
        }
    } catch (parser::Error &error) {
        // Handle the error
        cout << "Failure!" << endl;
        if (debug) cout << "  " << error.message << endl;
        cout << "  " << error.token << endl;
    }

    return 0;
}

void runTests() {
    vector<Automaton *> automatons = {
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
    for (auto automaton: automatons) {
        auto testResult = automaton->testAutomaton();
        if (!test::is_ok(testResult))
            cout << "ERROR: " << test::get_error_message(testResult) << endl;
        delete automaton;
    }
    cout << "done!" << endl;
}
