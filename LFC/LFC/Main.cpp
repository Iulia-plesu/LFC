#include<iostream>
#include"DeterministicFiniteAutomaton.h"
int main() {
    // Automat 1: q0, a -> q1
    std::set<std::string> states1 = { "q0", "q1" };
    std::set<char> alphabet1 = { 'a' };
    std::string initialState1 = "q0";
    std::set<std::string> finalStates1 = { "q1" };

    DeterministicFiniteAutomaton dfa1(states1, alphabet1, initialState1, finalStates1);
    dfa1.AddTransition("q0", 'a', "q1");

    // Automat 2: q1, b -> q2
    std::set<std::string> states2 = { "q1", "q2" };
    std::set<char> alphabet2 = { 'b' };
    std::string initialState2 = "q1";
    std::set<std::string> finalStates2 = { "q2" };

    DeterministicFiniteAutomaton dfa2(states2, alphabet2, initialState2, finalStates2);
    dfa2.AddTransition("q1", 'b', "q2");

    // Concatenare cu tranziție epsilon
    DeterministicFiniteAutomaton concatenatedDFA = Concatenate(dfa1, dfa2);

    // Afișăm automatul concatenat
    concatenatedDFA.PrintAutomaton();

    return 0;
}
