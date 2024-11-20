#include <iostream>
#include <map>
#include <set>
#include <string>
#include<Stack>

class DeterministicFiniteAutomaton {
private:
    // Folosim std::map pentru a reprezenta tranzițiile
    // Cheia este un std::pair <startState, symbol>, iar valoarea este endState
    std::map<std::pair<std::string, char>, std::string> m_delta;
    std::set<std::string> m_Q; // Set de stări
    std::set<char> m_sigma;    // Alfabetul
    std::string m_q0;          // Starea inițială
    std::set<std::string> m_F; // Stările finale

public:
    // Constructor
    DeterministicFiniteAutomaton(const std::set<std::string>& Q,
        const std::set<char>& sigma,
        const std::string& q0,
        const std::set<std::string>& F)
        : m_Q(Q), m_sigma(sigma), m_q0(q0), m_F(F) {}
    DeterministicFiniteAutomaton(const std::set<std::string>& Q,
        const std::set<char>& sigma,
        const std::map<std::pair<std::string, char>, std::string>&delta,
        const std::string& q0,
        const std::set<std::string>& F)
        : m_Q(Q), m_sigma(sigma),m_delta(delta), m_q0(q0), m_F(F) {}

    // Adăugarea unei tranziții
    void AddTransition(const std::string& startState, char symbol, const std::string& endState) {
        // Adăugăm tranziția în mapă
        m_delta[{startState, symbol}] = endState;
    }

    // Verificarea automatului (validitatea tranzițiilor)
    bool VerifyAutomaton() const {
        for (const auto& transition : m_delta) {
            // Verificăm dacă stările sunt valide
            if (m_Q.find(transition.first.first) == m_Q.end()) {
                std::cerr << "Error: Start state " << transition.first.first << " not in states.\n";
                return false;
            }
            if (m_Q.find(transition.second) == m_Q.end()) {
                std::cerr << "Error: End state " << transition.second << " not in states.\n";
                return false;
            }
        }
        return true;
    }

    // Verificarea unui cuvânt
    bool CheckWord(const std::string& word) const {
        std::string currentState = m_q0;
        for (char symbol : word) {
            // Căutăm tranziția pentru starea curentă și simbolul curent
            auto it = m_delta.find({ currentState, symbol });
            if (it == m_delta.end()) {
                return false; // Nu există tranziție validă
            }
            currentState = it->second; // Actualizăm starea curentă
        }
        return m_F.find(currentState) != m_F.end(); // Verificăm dacă starea finală este acceptată
    }

    // Afișarea automatului
    void PrintAutomaton() const {
        std::cout << "States: ";
        for (const auto& state : m_Q) std::cout << state << " ";
        std::cout << "\nAlphabet: ";
        for (const auto& symbol : m_sigma) std::cout << symbol << " ";
        std::cout << "\nInitial state: " << m_q0 << "\nFinal states: ";
        for (const auto& finalState : m_F) std::cout << finalState << " ";
        std::cout << "\nTransitions:\n";

        // Afișăm tranzițiile
        for (const auto& transition : m_delta) {
            std::cout << transition.first.first << " --" << transition.first.second
                << "--> " << transition.second << "\n";
        }
    }
    // Getter și Setter pentru stări
    const std::set<std::string>& GetStates()const { return m_Q; }
    void SetStates(const std::set<std::string>& newStates) { m_Q = newStates; }

    // Getter și Setter pentru alfabet
    const std::set<char>& GetAlphabet() const { return m_sigma; }
    void SetAlphabet(const std::set<char>& newAlphabet) { m_sigma = newAlphabet; }

    // Getter și Setter pentru starea inițială
   const  std::string & GetInitialState() const { return m_q0; }
    void SetInitialState(const std::string& newInitialState) { m_q0 = newInitialState; }

    // Getter și Setter pentru stările finale
    const std::set<std::string>& GetFinalStates() const  { return m_F; }
    void SetFinalStates(const std::set<std::string>& newFinalStates) { m_F = newFinalStates; }

    // Getter și Setter pentru tranziții
   const std::map<std::pair<std::string, char>, std::string>& GetTransitions() const { return m_delta; }
    void SetTransitions(const std::map<std::pair<std::string, char>, std::string>& newTransitions) { m_delta = newTransitions; }
};

bool IsOperator(char c) {
    return c == '|' || c == '.' || c == '*';
}

// Prioritatea operatorilor
int GetPrecedence(char c) {
    if (c == '*') return 3;
    if (c == '.') return 2;
    if (c == '|') return 1;
    return 0;
}

// Conversia expresiei regulate în RPN
std::string ConvertToRPN(const std::string& regex) {
    std::stack<char> operators;
    std::string output;

    for (char c : regex) {
        if (isalnum(c)) {
            output += c;  // Caracter direct în expresie
        }
        else if (c == '(') {
            operators.push(c);
        }
        else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                output += operators.top();
                operators.pop();
            }
            if (!operators.empty() && operators.top() == '(') {
                operators.pop();
            }
        }
        else if (IsOperator(c)) {
            while (!operators.empty() && GetPrecedence(operators.top()) >= GetPrecedence(c)) {
                output += operators.top();
                operators.pop();
            }
            operators.push(c);
        }
    }

    while (!operators.empty()) {
        output += operators.top();
        operators.pop();
    }

    return output;
}

DeterministicFiniteAutomaton BuildBasicAutomaton(char symbol) {
    std::set<std::string> states = { "q0", "q1" };
    std::set<char> alphabet = { symbol };
    std::string initialState = "q0";
    std::set<std::string> finalStates = { "q1" };

    DeterministicFiniteAutomaton dfa(states, alphabet, initialState, finalStates);
    dfa.AddTransition("q0", symbol, "q1");

    return dfa;
}

DeterministicFiniteAutomaton Concatenate( const DeterministicFiniteAutomaton& a1, const DeterministicFiniteAutomaton& a2) {
    // 1. Combină stările celor două automate
    std::set<std::string> states { a1.GetStates() };
    states.insert(a2.GetStates().begin(), a2.GetStates().end());  // Adăugăm stările lui a2

    // 2. Combină alfabetul celor două automate
    std::set<char> alphabet = a1.GetAlphabet();
    alphabet.insert(a2.GetAlphabet().begin(), a2.GetAlphabet().end()); // Adăugăm alfabetul lui a2

    // 3. Adaugă tranzițiile celor două automate
    std::map<std::pair<std::string, char>, std::string> transitions = a1.GetTransitions();  // Tranzițiile lui a1
    auto a2Transitions = a2.GetTransitions();  // Tranzițiile lui a2

    // Adăugăm tranzițiile din a2 la a1
    for (const auto& transition : a2Transitions) {
        transitions[transition.first] = transition.second;
    }

    // 4. Starea inițială este cea a primului automat
    std::string initialState = a1.GetInitialState();

    // 5. Stările finale sunt cele ale celui de-al doilea automat
    std::set<std::string> finalStates = a2.GetFinalStates();

    // 6. Adăugăm tranziție epsilon de la stările finale ale lui a1 la starea inițială a lui a2
    for (const auto& state : a1.GetFinalStates()) {
        transitions[{state, '\0'}] = a2.GetInitialState();  // Epsilon tranziție de la q1 din a1 la q1 din a2
    }

    // 7. Returnăm noul DFA concatenat
    return DeterministicFiniteAutomaton(states, alphabet, transitions, initialState, finalStates);
}




// Implementarea funcției Union
DeterministicFiniteAutomaton Union( const DeterministicFiniteAutomaton& a1, const DeterministicFiniteAutomaton& a2) {
    // 1. Combină stările celor două automate
    std::set<std::string> states = { "new_start" }; // Stare de start comună
    states.insert(a1.GetStates().begin(), a1.GetStates().end());
    states.insert(a2.GetStates().begin(), a2.GetStates().end());

    // 2. Combină alfabetul celor două automate
    std::set<char> alphabet = a1.GetAlphabet();
    alphabet.insert(a2.GetAlphabet().begin(), a2.GetAlphabet().end());

    // 3. Adaugă tranzițiile celor două automate
    std::map<std::pair<std::string, char>, std::string> transitions = a1.GetTransitions();
    auto a2Transitions = a2.GetTransitions();
    for (const auto& transition : a2Transitions) {
        transitions[transition.first] = transition.second;
    }

    // 4. Starea inițială este o stare comună, "new_start"
    std::string initialState = "new_start";

    // 5. Stările finale sunt cele ale celor două automate
    std::set<std::string> finalStates = a1.GetFinalStates();
    finalStates.insert(a2.GetFinalStates().begin(), a2.GetFinalStates().end());

    // 6. Adăugăm tranziții epsilon de la starea "new_start" la stările inițiale ale celor două automate
    transitions[{initialState, '\0'}] = a1.GetInitialState();  // Tranziție epsilon către a1
    transitions[{initialState, '\0'}] = a2.GetInitialState();  // Tranziție epsilon către a2

    // 7. Returnăm automatul rezultat
    return DeterministicFiniteAutomaton(states, alphabet, transitions, initialState, finalStates);
}


// Implementarea funcției Star
DeterministicFiniteAutomaton Star(const DeterministicFiniteAutomaton& a) {
    std::set<std::string> states = { "new_start", "new_final" };
    states.insert(a.GetStates().begin(), a.GetStates().end());

    std::set<char> alphabet = a.GetAlphabet();
    std::map<std::pair<std::string, char>, std::string> transitions = a.GetTransitions();

    std::string initialState = "new_start";
    std::set<std::string> finalStates = { "new_final" };

    transitions[{initialState, '\0'}] = a.GetInitialState();
    transitions[{initialState, '\0'}] = "new_final";
    for (const auto& state : a.GetFinalStates()) {
        transitions[{state, '\0'}] = a.GetInitialState();
        transitions[{state, '\0'}] = "new_final";
    }

    return DeterministicFiniteAutomaton(states, alphabet, transitions, initialState, finalStates);
}





DeterministicFiniteAutomaton BuildAutomatonFromRPN(const std::string& rpn) {
    std::stack<DeterministicFiniteAutomaton> stack;

    for (char c : rpn) {
        if (isalnum(c)) {
            stack.push(BuildBasicAutomaton(c));  // Construim automatul pentru un simbol
        }
        else if (c == '.') {  // Concatenare
            auto a2 = stack.top(); stack.pop();
            auto a1 = stack.top(); stack.pop();
            stack.push(Concatenate(a1, a2));
        }
        else if (c == '|') {  // Unire
            auto a2 = stack.top(); stack.pop();
            auto a1 = stack.top(); stack.pop();
            stack.push(Union(a1, a2));
        }
        else if (c == '*') {  // Steaua
            auto a = stack.top(); stack.pop();
            stack.push(Star(a));
        }
    }

    return stack.top();  // Automat rezultat
}

