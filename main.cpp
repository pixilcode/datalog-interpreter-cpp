#include <iostream>
#include <vector>
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"

void runTests();

int main(int argc, char** argv) {

    // Debug
    runTests();

    cout << "done!" << endl;

    return 0;
}

void runTests() {
    vector<Automaton*> automatons = {
            new ColonAutomaton(),
            new ColonDashAutomaton()
    };

    for(auto automaton : automatons) {
        auto testResult = automaton->testAutomaton();
        if (!test::is_ok(testResult))
            cout << "ERROR: " << test::get_error_message(testResult) << endl;
        delete automaton;
    }
}
