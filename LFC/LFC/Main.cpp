#include "DeterministicFiniteAutomaton.h"
#include <iostream>

int main() {
    // Define states, alphabet, initial state, and final states
    std::set<std::string> states = { "q0", "q1", "q2" };
    std::set<char> alphabet = { 'a', 'b' };
    std::string initialState = "q0";
    std::set<std::string> finalStates = { "q2" };

    // Create DFA instance
    DeterministicFiniteAutomaton dfa(states, alphabet, initialState, finalStates);

    // Add transitions
    dfa.AddTransition("q0", 'a', "q1");
    dfa.AddTransition("q1", 'b', "q2");

    // Verify DFA
    if (!dfa.VerifyAutomaton()) {
        std::cerr << "DFA verification failed.\n";
        return 1;
    }

    // Print DFA
    std::cout << dfa;

    // Check words
    std::string word1 = "ab";
    //std::string word2 = "aba";
    std::cout << "Word \"" << word1 << "\" is " << (dfa.CheckWord(word1) ? "accepted" : "rejected") << " by the DFA.\n";
    //std::cout << "Word \"" << word2 << "\" is " << (dfa.CheckWord(word2) ? "accepted" : "rejected") << " by the DFA.\n";

    return 0;
}
