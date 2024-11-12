#pragma once
#include "Transition.h"
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
class DeterministicFiniteAutomaton
{
private:
	std::set<std::string> m_Q; //multimea de q-uri 
	std::set<char> m_sigma; // alfabet, multime de litere
	std::vector<Transition> m_delta; // tranzitii
	std::string m_q0;
	std::set<std::string> m_F;

public:
	DeterministicFiniteAutomaton(
		const std::set<std::string>& Q,
		const std::set<char>& sigma,
		const std::string& q0,
		const std::set<std::string>& F)
		: m_Q(Q), 
		m_sigma(sigma), 
		m_q0(q0), 
		m_F(F){}

	void AddTransition(const std::string& startState, char symbol, const std::string& endState) {
		m_delta.push_back(Transition(startState, symbol, endState));
	}

	bool VerifyAutomaton() {
		for (const auto& state : m_Q) {
			for (const auto& symbol : m_sigma) {
				bool found = std::any_of(m_delta.begin(), m_delta.end(),
					[&state, &symbol]( const Transition& t) {
						return t.GetStartState() == state && t.GetSymbol() == symbol;
					});
				if (!found) {
					std::cerr << "Missing transition for state " << state << " and symbol " << symbol << '\n';
					return false;
				}
			}
		}
		if (m_Q.find(m_q0) == m_Q.end()) {
			std::cerr << "Initial state " << m_q0 << " is not in the set of states.\n";
			return false;
		}
		for (const auto& finalState : m_F) {
			if (m_Q.find(finalState) == m_Q.end()) {
				std::cerr << "Final state " << finalState << " is not in the set of states.\n";
				return false;
			}
		}
		return true;
	}

	bool CheckWord(const std::string& word) const {
		std::string currentState = m_q0;
		for (char symbol : word) {
			auto it = std::find_if(m_delta.begin(), m_delta.end(),
				[&currentState, &symbol](const Transition& t) {
					return t.GetStartState() == currentState && t.GetSymbol() == symbol;
				});
			if (it == m_delta.end()) {
				return false;  // No valid transition
			}
			currentState = it->GetEndState();  // Move to the next state
		}
		return m_F.find(currentState) != m_F.end();  // Accept if the final state is in F
	}
	friend std::ostream& operator<<(std::ostream& os, const DeterministicFiniteAutomaton& dfa) {
		os << "States (Q): { ";
		for (const auto& state : dfa.m_Q) os << state << " ";
		os << "}\nAlphabet (Σ): { ";
		for (const auto& symbol : dfa.m_sigma) os << symbol << " ";
		os << "}\nInitial State (q0): " << dfa.m_q0 << "\nFinal States (F): { ";
		for (const auto& finalState : dfa.m_F) os << finalState << " ";
		os << "}\nTransitions (δ):\n";
		for (const auto& transition : dfa.m_delta) {
			os << "  δ(" << transition.GetStartState() << ", " << transition.GetSymbol()
				<< ") -> " << transition.GetEndState() << "\n";
		}
		return os;
	}
};

