#include <iostream>
#include <vector>
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"

void runTests();

int main(int argc, char** argv) {
    // Debug
    runTests();

    return 0;
}

void runTests() {
    vector<Automaton*> automatons = {
            new ColonAutomaton(),
            new ColonDashAutomaton()
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
