#include <cstdlib>
#include <iostream>
#include <cstring>
#include <vector>
#include "automaton/all.h" // include all automatons

void runTests();

int main(int argc, char** argv) {
    // Debug
    cout << std::getenv("DEBUG") << std::endl;
    if (strcmp(std::getenv("DEBUG"), "true") == 0)
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
