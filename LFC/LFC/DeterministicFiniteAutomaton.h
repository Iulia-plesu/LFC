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
	std::set<std::string> m_Q; // set of states
	std::set<char> m_sigma; // alphabet
	std::vector<Transition> m_delta; // transitions
	std::string m_q0;
	std::set<std::string> m_F;

public:

	DeterministicFiniteAutomaton(const std::set<std::string>& Q,
		const std::set<char>& sigma,
		const std::string& q0,
		const std::set<std::string>& F);

	void AddTransition(const std::string& startState, char symbol, const std::string& endState);

	bool VerifyAutomaton() const;

	bool CheckWord(const std::string& word) const;
	friend std::ostream& operator<<(std::ostream& os, const DeterministicFiniteAutomaton& dfa);
};

