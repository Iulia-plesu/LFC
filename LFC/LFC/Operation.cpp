#include "Operation.h"
#include <iostream>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <string>
#include <iomanip>
#include <sstream>

int Operation::priority(char op)
{
	if (op == '|')
		return 1;
	if (op == '.')
		return 2;
	if (op == '*')
		return 3;
	if (op == '(' || op == ')')
		return 0;
	return -1;
}

std::string Operation::polishForm(const std::string& expression)
{
	std::stack<char> polish;
	std::stack<char> op_stack;
	char prevChar = '\0';

	for (char current : expression) {
		if (current == ' ')
			continue;

		if (isalnum(current)) 
		{
			polish.push(current);
		}
		else 
			if (current == '(') {
				if (prevChar == ')' || prevChar == '(')
					return "Parantezerea este incorecta";
				op_stack.push(current);
			}
			else{
				if (current == ')') {
					if (prevChar == '(' || prevChar == ')')
						return "Parantezerea este incorecta";
					while (!op_stack.empty() && op_stack.top() != '(') {
						polish.push(op_stack.top());
						op_stack.pop();
					}
					if (!op_stack.empty())
						op_stack.pop();
				}
				else {
					if (priority(current) == -1)
						return "Caractere nepermise";
					while (!op_stack.empty() && priority(op_stack.top()) >= priority(current)) {
						polish.push(op_stack.top());
						op_stack.pop();
					}
					op_stack.push(current);
				}
			}
		prevChar = current;
	}

	while (!op_stack.empty()) {
		polish.push(op_stack.top());
		op_stack.pop();
	}

	std::string pForm;
	while (!polish.empty()) {
		pForm.insert(pForm.begin(), polish.top());
		polish.pop();
	}

	return pForm;
}

std::string GenerateUniqueState() {
	static int stateCounter = 0;
	std::ostringstream stateName;
	stateName << "q" << stateCounter++;
	return stateName.str();
}
DeterministicFiniteAutomaton Operation::BuildBasicAutomaton(char symbol)
{
	std::string initialState = GenerateUniqueState();
	std::string finalState = GenerateUniqueState();


	std::set<std::string> states = { initialState, finalState };
	std::set<char> alphabet = { symbol };
	std::set<std::string> finalStates = { finalState };

	DeterministicFiniteAutomaton dfa(states, alphabet, initialState, finalStates);
	dfa.AddTransition(initialState, symbol, finalState);

	return dfa;
}

DeterministicFiniteAutomaton Operation::Alternate(const DeterministicFiniteAutomaton& a1, const DeterministicFiniteAutomaton& a2)
{
	std::set<std::string> states{ a1.GetStates() };
	states.insert(a2.GetStates().begin(), a2.GetStates().end());

	// Combine alphabet from both automaton
	std::set<char> alphabet = a1.GetAlphabet();
	alphabet.insert(a2.GetAlphabet().begin(), a2.GetAlphabet().end());

	// Add traniztions from both automaton
	std::map<std::pair<std::string, char>, std::set<std::string>> transitions = a1.GetTransitions();
	auto a2Transitions = a2.GetTransitions();  //a2 Tranzitions

	// Adaugam tranzitiile din a2 la a1
	for (const auto& transition : a2Transitions) {
		transitions[transition.first] = transition.second;
	}

	
	std::string initialState = a1.GetInitialState();

	std::set<std::string> finalStates = a2.GetFinalStates();

	// Add lamda tranzitions
	for (const auto& state : a1.GetFinalStates()) {
		transitions[{state, '\0'}].insert(a2.GetInitialState()); 
	}

	return DeterministicFiniteAutomaton(states, alphabet, transitions, initialState, finalStates);
}

DeterministicFiniteAutomaton Operation::Concatenate(const DeterministicFiniteAutomaton& a1, const DeterministicFiniteAutomaton& a2)
{
	std::string newStart = GenerateUniqueState();
	std::string newFinal = GenerateUniqueState();

	// Combine states
	std::set<std::string> states = { newStart, newFinal };
	states.insert(a1.GetStates().begin(), a1.GetStates().end());
	states.insert(a2.GetStates().begin(), a2.GetStates().end());

	
	std::set<char> alphabet = a1.GetAlphabet();
	alphabet.insert(a2.GetAlphabet().begin(), a2.GetAlphabet().end());

	// Combine tranzitions
	std::map<std::pair<std::string, char>, std::set<std::string>> transitions = a1.GetTransitions();
	auto a2Transitions = a2.GetTransitions();
	transitions.insert(a2Transitions.begin(), a2Transitions.end());


	transitions[{newStart, '\0'}].insert(a1.GetInitialState());
	transitions[{newStart, '\0'}].insert(a2.GetInitialState());
	for (const auto& state : a1.GetFinalStates()) {
		transitions[{state, '\0'}].insert(newFinal);
	}
	for (const auto& state : a2.GetFinalStates()) {
		transitions[{state, '\0'}].insert(newFinal);
	}

	return DeterministicFiniteAutomaton(states, alphabet, transitions, newStart, { newFinal });
}

DeterministicFiniteAutomaton Operation::Star(const DeterministicFiniteAutomaton& a)
{
	std::string newStart = GenerateUniqueState();
	std::string newFinal = GenerateUniqueState();

	
	std::set<std::string> states = { newStart, newFinal };
	states.insert(a.GetStates().begin(), a.GetStates().end());

	std::set<char> alphabet = a.GetAlphabet();
	std::map<std::pair<std::string, char>, std::set<std::string>> transitions = a.GetTransitions();

	// Add lambda tranzitions
	transitions[{newStart, '\0'}].insert(a.GetInitialState());  // new_start -> old initial state
	transitions[{newStart, '\0'}].insert(newFinal);            // new_start -> new_final
	for (const auto& state : a.GetFinalStates())
	{
		transitions[{state, '\0'}].insert(a.GetInitialState()); // old final state -> old initial state
		transitions[{state, '\0'}].insert(newFinal);           // old final state -> new_final
	}


	return DeterministicFiniteAutomaton(states, alphabet, transitions, newStart, { newFinal });

}

DeterministicFiniteAutomaton Operation::BuildAutomatonFromRPN(const std::string& rpn)
{
	std::stack<DeterministicFiniteAutomaton> stack;

	for (char c : rpn) {
		if (isalnum(c)) {
			stack.push(BuildBasicAutomaton(c));
		}
		else if (c == '.') {
			auto a2 = stack.top(); stack.pop();
			auto a1 = stack.top(); stack.pop();
			stack.push(Alternate(a1, a2));
		}
		else if (c == '|') {
			auto a2 = stack.top(); stack.pop();
			auto a1 = stack.top(); stack.pop();
			stack.push(Concatenate(a1, a2));
		}
		else if (c == '*') {
			auto a = stack.top();
			stack.pop();
			stack.push(Star(a));
		}
	}

	return stack.top();  
}

std::set<std::string> Operation::LambdaClosure(const std::string& state, const std::map<std::pair<std::string, char>, std::set<std::string>>& transitions)
{
	std::set<std::string> closure;
	std::stack<std::string> stack;

	
	closure.insert(state);
	stack.push(state);

	// Process all tranzition with contains lambda
	while (!stack.empty()) {
		std::string currentState = stack.top();
		stack.pop();

		auto it = transitions.find({ currentState, '\0' });
		if (it != transitions.end()) {
			for (const auto& nextState : it->second) {
				if (closure.find(nextState) == closure.end()) {
					closure.insert(nextState);
					stack.push(nextState);
				}
			}
		}
	}

	return closure;
}

DeterministicFiniteAutomaton Operation::ConvertLambdaNFAtoDFA(const DeterministicFiniteAutomaton& afn)
{

	std::map<std::pair<std::string, char>, std::set<std::string>> dfaTransitions;

	
	std::set<std::string> dfaStates;
	std::string dfaInitialState;
	std::set<std::string> dfaFinalStates;

	// Queue for processing states
	std::queue<std::set<std::string>> queue;
	std::map<std::set<std::string>, std::string> stateNames;
	int stateCounter = 0;

	// Calculate lamda closuri from initial states
	std::set<std::string> initialClosure = LambdaClosure(afn.GetInitialState(), afn.GetTransitions());
	queue.push(initialClosure);
	stateNames[initialClosure] = "q" + std::to_string(stateCounter);
	dfaInitialState = "q" + std::to_string(stateCounter);
	dfaStates.insert(dfaInitialState);
	stateCounter++;

	//Process all states
	while (!queue.empty()) {
		std::set<std::string> currentSet = queue.front();
		queue.pop();
		std::string currentStateName = stateNames[currentSet];

		for (char symbol : afn.GetAlphabet()) {
			std::set<std::string> newState;

			// Generam noile stari prin tranzitii si calculam inchiderea \lambda
			for (const auto& state : currentSet) {
				auto it = afn.GetTransitions().find({ state, symbol });
				if (it != afn.GetTransitions().end()) {
					for (const auto& nextState : it->second) {
						auto closure = LambdaClosure(nextState, afn.GetTransitions());
						newState.insert(closure.begin(), closure.end());
					}
				}
			}

			if (!newState.empty()) {
				if (stateNames.find(newState) == stateNames.end()) {
					stateNames[newState] = "q" + std::to_string(stateCounter);
					dfaStates.insert(stateNames[newState]);
					queue.push(newState);
					stateCounter++;
				}
				//add tranzitions
				dfaTransitions[{currentStateName, symbol}].insert(stateNames[newState]);
			}
		}
	}

	
	for (auto it = stateNames.begin(); it != stateNames.end(); ++it) {
		const std::set<std::string>& stateSet = it->first;
		const std::string& name = it->second;             

		for (const auto& state : stateSet) {
			if (afn.GetFinalStates().count(state)) {
				dfaFinalStates.insert(name);
				break;
			}
		}
	}

	return DeterministicFiniteAutomaton(dfaStates, afn.GetAlphabet(), dfaTransitions, dfaInitialState, dfaFinalStates);
}

