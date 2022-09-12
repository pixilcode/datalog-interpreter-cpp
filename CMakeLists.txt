cmake_minimum_required(VERSION 3.23)
project(project_1)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(project_1
        Automaton.h
        ColonAutomaton.cpp
        ColonAutomaton.h
        main.cpp
        Token.h Test.h Test.cpp)
