#include "DeterministicFiniteAutomaton.h"

DeterministicFiniteAutomaton::DeterministicFiniteAutomaton(const std::set<std::string>& Q, 
	const std::set<char>& sigma, 
	const std::string& q0, 
	const std::set<std::string>& F):
	m_Q(Q),
	m_sigma(sigma),
	m_q0(q0),
	m_F(F){}

void DeterministicFiniteAutomaton::AddTransition(const std::string& startState, char symbol, const std::string& endState)
{
	m_delta.push_back(Transition(startState, symbol, endState));
	if (endState == " ")
	{
		m_delta.push_back(Transition());
	}
}

bool DeterministicFiniteAutomaton::VerifyAutomaton() const
{
		for (const auto& transition : m_delta) {

			if (m_Q.find(transition.GetStartState()) == m_Q.end()) {
				std::cerr << "Error: Start state( Tranzition)  " << transition.GetStartState()
					<< " don't appear in  (m_Q)." << std::endl;
				return false;
			}


			if (m_Q.find(transition.GetEndState()) == m_Q.end()) {
				std::cerr << "Error: Start state( Tranzition)  " << transition.GetEndState()
					<< " don't appear in  (m_Q)." << std::endl;
				return false;
			}


			if (m_sigma.find(transition.GetSymbol()) == m_sigma.end()) {
				std::cerr << "Error: Symbol  " << transition.GetSymbol()
					<< " don't appear in (m_sigma)." << std::endl;
				return false;
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

bool DeterministicFiniteAutomaton::CheckWord(const std::string& word) const
{
	std::string currentState = m_q0;
	for (char symbol : word) {
		auto it = std::find_if(m_delta.begin(), m_delta.end(),
			[&currentState, &symbol](const Transition& t) {
				return t.GetStartState() == currentState && t.GetSymbol() == symbol;
			});
		if (it == m_delta.end()) {
			return false;  
		}
		currentState = it->GetEndState(); 
	}
	return m_F.find(currentState) != m_F.end();  
}

std::ostream& operator<<(std::ostream& os, const DeterministicFiniteAutomaton& dfa)
{
	os << "States (Q): { ";
	for (const auto& state : dfa.m_Q) os << state << " ";
	os << "}\nAlphabet (Sigma): { ";
	for (const auto& symbol : dfa.m_sigma) os << symbol << " ";
	os << "}\nInitial State (q0): " << dfa.m_q0 << "\nFinal States (F): { ";
	for (const auto& finalState : dfa.m_F) os << finalState << " ";
	os << "}\nTransitions (Delta):\n";
	for (const auto& transition : dfa.m_delta) {
		os << "  delta(" << transition.GetStartState() << ", " << transition.GetSymbol()
			<< ") -> " << transition.GetEndState() << "\n";
	}
	return os;
}
