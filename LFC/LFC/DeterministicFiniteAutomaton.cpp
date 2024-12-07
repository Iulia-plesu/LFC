#include"DeterministicFiniteAutomaton.h"
#include<iostream>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <string>
#include<iomanip>

DeterministicFiniteAutomaton::DeterministicFiniteAutomaton(const std::set<std::string>& Q,
	const std::set<char>& sigma,
	const std::string& q0,
	const std::set<std::string>& F)
	: m_Q(Q), m_sigma(sigma), m_q0(q0), m_F(F) {}

DeterministicFiniteAutomaton::DeterministicFiniteAutomaton(const std::set<std::string>& Q,
	const std::set<char>& sigma,
	const std::map<std::pair<std::string, char>, std::set<std::string>>& delta,
	const std::string& q0,
	const std::set<std::string>& F) : m_Q(Q), m_sigma(sigma), m_delta(delta), m_q0(q0), m_F(F) {}


bool DeterministicFiniteAutomaton::CheckWord(const std::string& input) const 
{
	std::string currentState = m_q0; 

	for (char symbol : input) 
	{
		auto it = m_delta.find({ currentState, symbol });
		if (it == m_delta.end()) 
		{
			return false;
		}
		const std::set<std::string>& toStates = it->second;

		if (toStates.empty()) 
		{
			return false;
		}
		currentState = *toStates.begin();
	}
	return m_F.find(currentState) != m_F.end();
}

void DeterministicFiniteAutomaton::AddTransition(const std::string& startState, char symbol, const std::string& endState)
{
	m_delta[{startState, symbol}].insert(endState);
}

bool DeterministicFiniteAutomaton::VerifyAutomaton() const
{
	for (const auto& transition : m_delta) 
	{
		const std::string& fromState = transition.first.first;
		char symbol = transition.first.second;
		const std::set<std::string>& toStates = transition.second;

		if (m_Q.find(fromState) == m_Q.end()) 
		{
			std::cerr << "Error: Start state " << fromState << " not in states.\n";
			return false;
		}

		for (const auto& toState : toStates) 
		{
			if (m_Q.find(toState) == m_Q.end()) 
			{
				std::cerr << "Error: End state " << toState << " not in states.\n";
				return false;
			}
		}
	}
	return true;
}

void DeterministicFiniteAutomaton::PrintAutomaton() const 
{
	std::cout << "States: ";
	for (const auto& state : m_Q) 
	{
		std::cout << state << " ";
	}

	std::cout << "\nAlphabet: ";
	for (const auto& symbol : m_sigma) 
	{
		std::cout << symbol << " ";
	}

	std::cout << "\nInitial state: " << m_q0 << "\nFinal states: ";
	for (const auto& finalState : m_F) 
	{
		std::cout << finalState << " ";
	}

	std::cout << "\nTransitions:\n";
	for (const auto& transition : m_delta) 
	{
		const auto& fromState = transition.first.first;
		char symbol = transition.first.second;
		const auto& toStates = transition.second;

		for (const auto& toState : toStates) 
		{
			std::cout << fromState << " --" << symbol << "--> " << toState << "\n";
		}
	}
}


const std::set<std::string>& DeterministicFiniteAutomaton::GetStates() const
{
	return m_Q;
}

const std::set<char>& DeterministicFiniteAutomaton::GetAlphabet() const
{
	return m_sigma;
}

const std::string& DeterministicFiniteAutomaton::GetInitialState() const
{
	return m_q0;
}

const std::set<std::string>& DeterministicFiniteAutomaton::GetFinalStates() const
{
	return m_F;
}

const std::map<std::pair<std::string, char>, std::set<std::string>>& DeterministicFiniteAutomaton::GetTransitions() const
{
	return m_delta;
}

void DeterministicFiniteAutomaton::PrintTransitionTable(const DeterministicFiniteAutomaton& dfa)
{
	const auto& states = m_Q;
	const auto& alphabet = m_sigma;
	const auto& transitions = m_delta;
	const auto& initialState = m_q0;
	const auto& finalStates = m_F;

	size_t maxStateLength = 0;
	for (const auto& state : states) 
	{
		maxStateLength = std::max(maxStateLength, state.length());
	}
	size_t columnWidth = std::max(maxStateLength + 2, size_t(5));

	std::cout << std::string(columnWidth, ' ') << " |";
	for (const char symbol : alphabet) 
	{
		std::cout << " " << std::setw(columnWidth) << symbol;
	}

	std::cout << "\n" << std::string(columnWidth, '-') << "-+-";
	for (size_t i = 0; i < alphabet.size(); ++i) 
	{
		std::cout << std::string(columnWidth, '-');
		if (i != alphabet.size() - 1) std::cout << "-";
	}
	std::cout << "\n";

	for (const std::string& state : states) 
	{
		std::string stateDisplay = state;
		if (state == initialState) 
		{
			stateDisplay = "*" + stateDisplay;
		}
		if (finalStates.count(state)) 
		{
			stateDisplay = '^' + stateDisplay;
		}

		std::cout << std::setw(columnWidth) << stateDisplay << " |";

		for (const char symbol : alphabet) 
		{
			auto it = transitions.find({ state, symbol });
			if (it != transitions.end() && !it->second.empty()) 
			{
				std::cout << " " << std::setw(columnWidth) << *it->second.begin();
			}
			else 
			{
				std::cout << " " << std::setw(columnWidth) << "-";
			}
		}
		std::cout << "\n";
	}
}

