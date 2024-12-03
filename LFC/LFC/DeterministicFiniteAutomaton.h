#include <iostream>
#include <map>
#include <set>

#pragma once
class DeterministicFiniteAutomaton {
private:
    std::map<std::pair<std::string, char>, std::set<std::string>> m_delta;
    std::set<std::string> m_Q;
    std::set<char> m_sigma;
    std::string m_q0;
    std::set<std::string> m_F;

public:
    DeterministicFiniteAutomaton() = default;
    DeterministicFiniteAutomaton(const std::set<std::string>& Q,
        const std::set<char>& sigma,
        const std::string& q0,
        const std::set<std::string>& F);
    DeterministicFiniteAutomaton(const std::set<std::string>& Q,
        const std::set<char>& sigma,
        const std::map<std::pair<std::string, char>, std::set<std::string>>& delta,
        const std::string& q0,
        const std::set<std::string>& F);

    bool CheckWord(const std::string& input) const;

    void AddTransition(const std::string& startState, char symbol, const std::string& endState);

    bool VerifyAutomaton() const;

    void PrintAutomaton() const;

    const std::set<std::string>& GetStates()const;

    const std::set<char>& GetAlphabet() const;



    const  std::string& GetInitialState() const;



    const std::set<std::string>& GetFinalStates() const;


    const std::map<std::pair<std::string, char>, std::set<std::string>>& GetTransitions() const;

    void PrintTransitionTable(const DeterministicFiniteAutomaton& dfa);


};

