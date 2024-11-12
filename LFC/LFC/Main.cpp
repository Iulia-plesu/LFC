#include "DeterministicFiniteAutomaton.h"
#include <iostream>

int main() {
    
    std::set<std::string> states = { "q0", "q1"};
    std::set<char> alphabet = { 'a', 'b' };
    std::string initialState = "q0";
    std::set<std::string> finalStates = { "q1" };

    DeterministicFiniteAutomaton dfa(states, alphabet, initialState, finalStates);

    dfa.AddTransition("q0", 'a', "q0");
    dfa.AddTransition("q0", 'b', "q1");
    dfa.AddTransition("q1", 'b', "q1");

   
    if (!dfa.VerifyAutomaton()) {
        std::cerr << "DFA verification failed.\n";
        return 1;
    }

    
    std::cout << dfa;

    std::string word1 = "aaabbb";
    
    std::cout << "Word \"" << word1 << "\" is " << (dfa.CheckWord(word1) ? "accepted" : "rejected") << " by the DFA.\n";

    return 0;
}
