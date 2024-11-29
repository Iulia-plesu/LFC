#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>

class LambdaNFAtoDFA {
private:
    std::set<std::string> m_states;                     // Mulțimea de stări (Q)
    std::set<char> m_alphabet;                          // Alfabetul (Σ)
    std::map<std::pair<std::string, char>, std::set<std::string>> m_transitions; // Tranziții (δ)
    std::string m_initialState;                         // Starea inițială (q0)
    std::set<std::string> m_finalStates;                // Stările finale (F)

    // Funcție pentru λ-închiderea unei stări
    std::set<std::string> LambdaClosure(const std::string& state) const {
        std::set<std::string> closure = { state };  // Include starea însăși
        std::queue<std::string> toProcess;
        toProcess.push(state);

        while (!toProcess.empty()) {
            std::string current = toProcess.front();
            toProcess.pop();

            auto it = m_transitions.find({ current, '\0' }); // Verificăm λ-tranzițiile
            if (it != m_transitions.end()) {
                for (const auto& nextState : it->second) {
                    if (closure.find(nextState) == closure.end()) {
                        closure.insert(nextState);
                        toProcess.push(nextState);
                    }
                }
            }
        }
        return closure;
    }

    // Funcție pentru λ-închiderea unei mulțimi de stări
    std::set<std::string> LambdaClosure(const std::set<std::string>& states) const {
        std::set<std::string> closure;
        for (const auto& state : states) {
            auto singleClosure = LambdaClosure(state);
            closure.insert(singleClosure.begin(), singleClosure.end());
        }
        return closure;
    }

public:
    LambdaNFAtoDFA(const std::set<std::string>& states,
        const std::set<char>& alphabet,
        const std::map<std::pair<std::string, char>, std::set<std::string>>& transitions,
        const std::string& initialState,
        const std::set<std::string>& finalStates)
        : m_states(states), m_alphabet(alphabet), m_transitions(transitions), m_initialState(initialState), m_finalStates(finalStates) {}

    void ConvertToDFA() {
        // Mapare stări multiple la un reprezentant unic (A, B, C, ...)
        std::unordered_map<std::set<std::string>, std::string> stateName;
        std::map<std::string, std::set<std::string>> reverseStateName;

        // Funcție pentru generarea unui nume unic de stare
        auto generateStateName = [&stateName, &reverseStateName](const std::set<std::string>& stateSet) {
            static char name = 'A';
            if (stateName.find(stateSet) == stateName.end()) {
                std::string newName(1, name++);
                stateName[stateSet] = newName;
                reverseStateName[newName] = stateSet;
            }
            return stateName[stateSet];
            };

        // Calculăm starea inițială a DFA
        std::set<std::string> initialDFAState = LambdaClosure(m_initialState);
        std::string initialStateName = generateStateName(initialDFAState);

        // Coada de procesare a stărilor DFA
        std::queue<std::set<std::string>> toProcess;
        toProcess.push(initialDFAState);

        // Structuri pentru DFA
        std::set<std::string> dfaStates = { initialStateName };
        std::map<std::pair<std::string, char>, std::string> dfaTransitions;
        std::set<std::string> dfaFinalStates;

        // Parcurgem toate stările posibile
        while (!toProcess.empty()) {
            auto currentDFAState = toProcess.front();
            toProcess.pop();
            std::string currentStateName = generateStateName(currentDFAState);

            // Verificăm dacă este o stare finală
            for (const auto& nfaState : currentDFAState) {
                if (m_finalStates.find(nfaState) != m_finalStates.end()) {
                    dfaFinalStates.insert(currentStateName);
                    break;
                }
            }

            // Calculăm tranzițiile pentru fiecare simbol din alfabet
            for (char symbol : m_alphabet) {
                std::set<std::string> nextStates;

                for (const auto& nfaState : currentDFAState) {
                    auto it = m_transitions.find({ nfaState, symbol });
                    if (it != m_transitions.end()) {
                        nextStates.insert(it->second.begin(), it->second.end());
                    }
                }

                // Aplicăm λ-închiderile la stările obținute
                nextStates = LambdaClosure(nextStates);

                if (!nextStates.empty()) {
                    std::string nextStateName = generateStateName(nextStates);
                    dfaTransitions[{currentStateName, symbol}] = nextStateName;

                    // Adăugăm starea în mulțimea de stări dacă nu există deja
                    if (dfaStates.find(nextStateName) == dfaStates.end()) {
                        dfaStates.insert(nextStateName);
                        toProcess.push(nextStates);
                    }
                }
            }
        }

        // Afișăm DFA-ul obținut
        std::cout << "DFA States:\n";
        for (const auto& state : dfaStates) {
            std::cout << state << " = { ";
            for (const auto& s : reverseStateName[state]) std::cout << s << " ";
            std::cout << "}\n";
        }

        std::cout << "DFA Transitions:\n";
        for (const auto& transition : dfaTransitions) {
            std::cout << transition.first.first << " --" << transition.first.second << "--> " << transition.second << "\n";
        }

        std::cout << "DFA Final States:\n";
        for (const auto& finalState : dfaFinalStates) {
            std::cout << finalState << "\n";
        }
    }
};

int main() {
    // Exemplu: AFN cu λ-tranziții
    std::set<std::string> states = { "q0", "q1", "q2", "q3", "q4", "q5", "q6", "q7", "q8", "q9", "q10" };
    std::set<char> alphabet = { 'a', 'b' };
    std::map<std::pair<std::string, char>, std::set<std::string>> transitions = {
        {{"q0", '\0'}, {"q1", "q7"}},
        {{"q1", 'a'}, {"q2"}},
        {{"q2", '\0'}, {"q3"}},
        {{"q3", 'a'}, {"q4"}},
        {{"q4", '\0'}, {"q5"}},
        {{"q5", 'b'}, {"q6"}},
        {{"q6", '\0'}, {"q8"}},
        {{"q7", 'b'}, {"q9"}},
        {{"q9", 'b'}, {"q10"}},
        {{"q10", '\0'}, {"q8"}}
    };
    std::string initialState = "q0";
    std::set<std::string> finalStates = { "q8" };

    LambdaNFAtoDFA automaton(states, alphabet, transitions, initialState, finalStates);
    automaton.ConvertToDFA();

    return 0;
}
