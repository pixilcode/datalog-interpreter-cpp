#include <cstdlib>
#include <iostream>
#include <cstring>
#include <vector>
#include "automaton/all.h" // include all automatons

void runTests();

int main(int argc, char** argv) {
    // Debug
    if (strcmp(std::getenv("DEBUG"), "true") == 0)
        runTests();

    return 0;
}

void runTests() {
    vector<Automaton*> automatons = {
            new AddAutomaton(),
            new ColonAutomaton(),
            new ColonDashAutomaton(),
            new CommaAutomaton(),
            new LeftParenAutomaton(),
            new MultiplyAutomaton(),
            new PeriodAutomaton(),
            new QuestionMarkAutomaton(),
            new RightParenAutomaton(),
            new SchemesAutomaton(),
            new FactsAutomaton()
    };

    cout << "running tests..." << endl;
    for(auto automaton : automatons) {
        auto testResult = automaton->testAutomaton();
        if (!test::is_ok(testResult))
            cout << "ERROR: " << test::get_error_message(testResult) << endl;
        delete automaton;
    }
    cout << "done!" << endl;
}
