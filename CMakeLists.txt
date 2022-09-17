cmake_minimum_required(VERSION 3.23)
project(project_1)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(project_1
        automaton/all.h
        automaton/Automaton.h
        automaton/AddAutomaton.h
        automaton/AddAutomaton.cpp
        automaton/ColonAutomaton.h
        automaton/ColonAutomaton.cpp
        automaton/ColonDashAutomaton.h
        automaton/ColonDashAutomaton.cpp
        automaton/CommaAutomaton.h
        automaton/CommaAutomaton.cpp
        automaton/LeftParenAutomaton.h
        automaton/LeftParenAutomaton.cpp
        automaton/MultiplyAutomaton.h
        automaton/MultiplyAutomaton.cpp
        automaton/PeriodAutomaton.h
        automaton/PeriodAutomaton.cpp
        automaton/QuestionMarkAutomaton.h
        automaton/QuestionMarkAutomaton.cpp
        automaton/RightParenAutomaton.h
        automaton/RightParenAutomaton.cpp
        main.cpp
        Token.h Test.h Test.cpp)
