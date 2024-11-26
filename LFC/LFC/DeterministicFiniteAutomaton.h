#include <iostream>
#include <map>
#include <set>
#include <string>
#include<Stack>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <string>
#include <iostream>


class DeterministicFiniteAutomaton {
private:
    // Cheia este un std::pair <startState, symbol>, iar valoarea este endState
    std::map<std::pair<std::string, char>, std::string> m_delta;
    std::set<std::string> m_Q; // Set de stări
    std::set<char> m_sigma;    // Alfabetul
    std::string m_q0;          // Starea inițială
    std::set<std::string> m_F; // Stările finale

public:
    DeterministicFiniteAutomaton() = default;
    DeterministicFiniteAutomaton(const std::set<std::string>& Q,
        const std::set<char>& sigma,
        const std::string& q0,
        const std::set<std::string>& F);
    DeterministicFiniteAutomaton(const std::set<std::string>& Q,
        const std::set<char>& sigma,
        const std::map<std::pair<std::string, char>, std::string>& delta,
        const std::string& q0,
        const std::set<std::string>& F);

    void addState(const std::string& state, bool isFinal = false) {
        m_Q.insert(state);
        if (isFinal) {
            m_F.insert(state);
        }
    }

    
    void setInitialState(const std::string& state) {
        m_q0 = state;
        m_Q.insert(state);
    }


    bool CheckWord(const std::string& input) const;

    void AddTransition(const std::string& startState, char symbol, const std::string& endState);

    bool VerifyAutomaton() const;
    
    void PrintAutomaton() const;

    const std::set<std::string>& GetStates()const;

    const std::set<char>& GetAlphabet() const;
   

   
    const  std::string& GetInitialState() const;
  

    
    const std::set<std::string>& GetFinalStates() const;

    
    const std::map<std::pair<std::string, char>, std::string>& GetTransitions() const;
   
};

int priority(char op);

std::string polishForm(const std::string& expression);

DeterministicFiniteAutomaton BuildBasicAutomaton(char symbol);

DeterministicFiniteAutomaton Concatenate(const DeterministicFiniteAutomaton& a1, const DeterministicFiniteAutomaton& a2);

// Implementarea funcției Union
DeterministicFiniteAutomaton Union(const DeterministicFiniteAutomaton& a1, const DeterministicFiniteAutomaton& a2);

// Implementarea funcției Star
DeterministicFiniteAutomaton Star(const DeterministicFiniteAutomaton& a);


DeterministicFiniteAutomaton BuildAutomatonFromRPN(const std::string & rpn);
DeterministicFiniteAutomaton BuildAutomatonFromFile(const std::string& filename);

