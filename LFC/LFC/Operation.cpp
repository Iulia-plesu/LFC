#include "Operation.h"
#include<iostream>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <string>
#include<iomanip>
#include<sstream>

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

		if (isalnum(current)) {

			polish.push(current);
		}
		else if (current == '(') {
			if (prevChar == ')' || prevChar == '(')
				return "Parantezerea este incorecta";
			op_stack.push(current);
		}
		else if (current == ')') {
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

DeterministicFiniteAutomaton Operation::Concatenate(const DeterministicFiniteAutomaton& a1, const DeterministicFiniteAutomaton& a2)
{
	std::set<std::string> states{ a1.GetStates() };
	states.insert(a2.GetStates().begin(), a2.GetStates().end());

	// 2. Combina alfabetul celor doua automate
	std::set<char> alphabet = a1.GetAlphabet();
	alphabet.insert(a2.GetAlphabet().begin(), a2.GetAlphabet().end());

	// 3. Adauga tranzitiile celor douaautomate
	std::map<std::pair<std::string, char>, std::set<std::string>> transitions = a1.GetTransitions();
	auto a2Transitions = a2.GetTransitions();  // Tranzitiile lui a2

	// Adaugam tranzitiile din a2 la a1
	for (const auto& transition : a2Transitions) {
		transitions[transition.first] = transition.second;
	}

	// 4. Starea initiala este cea a primului automat
	std::string initialState = a1.GetInitialState();

	// 5. Starile finale sunt cele ale celui de-al doilea automat
	std::set<std::string> finalStates = a2.GetFinalStates();

	// 6. Adaugam tranzitie epsilon de la starile finale ale lui a1 la starea initiaala a lui a2
	for (const auto& state : a1.GetFinalStates()) {
		transitions[{state, '\0'}].insert(a2.GetInitialState());  // Epsilon tranzitie de la q1 din a1 la q1 din a2
	}

	// 7. Returnam noul DFA concatenat
	return DeterministicFiniteAutomaton(states, alphabet, transitions, initialState, finalStates);
}

DeterministicFiniteAutomaton Operation::Union(const DeterministicFiniteAutomaton& a1, const DeterministicFiniteAutomaton& a2)
{
	// 1. Generam stari unice pentru new_start și new_final
	std::string newStart = GenerateUniqueState();
	std::string newFinal = GenerateUniqueState();

	// 2. Combinam stările
	std::set<std::string> states = { newStart, newFinal };
	states.insert(a1.GetStates().begin(), a1.GetStates().end());
	states.insert(a2.GetStates().begin(), a2.GetStates().end());

	// 3. Combinam alfabetele
	std::set<char> alphabet = a1.GetAlphabet();
	alphabet.insert(a2.GetAlphabet().begin(), a2.GetAlphabet().end());

	// 4. Combinam tranzitiile
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

	// 5. Returnam noul automat
	return DeterministicFiniteAutomaton(states, alphabet, transitions, newStart, { newFinal });
}

DeterministicFiniteAutomaton Operation::Star(const DeterministicFiniteAutomaton& a)
{
	// Generam stari noi pentru start și final
	std::string newStart = GenerateUniqueState();
	std::string newFinal = GenerateUniqueState();

	// Combinam stările
	std::set<std::string> states = { newStart, newFinal };
	states.insert(a.GetStates().begin(), a.GetStates().end());

	// Preluam alfabetul și tranzitiile existente
	std::set<char> alphabet = a.GetAlphabet();
	std::map<std::pair<std::string, char>, std::set<std::string>> transitions = a.GetTransitions();

	// Adaugam tranzitii lambda
	transitions[{newStart, '\0'}].insert(a.GetInitialState());  // new_start -> vechea stare initiala
	transitions[{newStart, '\0'}].insert(newFinal);            // new_start -> new_final
	for (const auto& state : a.GetFinalStates())
	{
		transitions[{state, '\0'}].insert(a.GetInitialState()); // vechea stare finala -> vechea stare initiala
		transitions[{state, '\0'}].insert(newFinal);           // vechea stare finala -> new_final
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
			stack.push(Concatenate(a1, a2));
		}
		else if (c == '|') {
			auto a2 = stack.top(); stack.pop();
			auto a1 = stack.top(); stack.pop();
			stack.push(Union(a1, a2));
		}
		else if (c == '*') {
			auto a = stack.top();
			stack.pop();
			stack.push(Star(a));
		}
	}

	return stack.top();  // Automat rezultat
}

std::set<std::string> Operation::LambdaClosure(const std::string& state, const std::map<std::pair<std::string, char>, std::set<std::string>>& transitions)
{
	std::set<std::string> closure;
	std::stack<std::string> stack;

	// Adaugam starea initiala in inchidere si pe stiva
	closure.insert(state);
	stack.push(state);

	// Procesam toate starile accesibile prin lambda
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

	// Seturi pentru strile si tranzitiile AFD
	std::set<std::string> dfaStates;
	std::string dfaInitialState;
	std::set<std::string> dfaFinalStates;

	// Coada pentru procesarea starilor
	std::queue<std::set<std::string>> queue;
	std::map<std::set<std::string>, std::string> stateNames;
	int stateCounter = 0;

	// Calculam \lambda-inchiderea starii initiale
	std::set<std::string> initialClosure = LambdaClosure(afn.GetInitialState(), afn.GetTransitions());
	queue.push(initialClosure);
	stateNames[initialClosure] = "q" + std::to_string(stateCounter);
	dfaInitialState = "q" + std::to_string(stateCounter);
	dfaStates.insert(dfaInitialState);
	stateCounter++;

	// Procesam toate starile
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

			// Daca s-a generat o stare nouă
			if (!newState.empty()) {
				if (stateNames.find(newState) == stateNames.end()) {
					stateNames[newState] = "q" + std::to_string(stateCounter);
					dfaStates.insert(stateNames[newState]);
					queue.push(newState);
					stateCounter++;
				}
				// Adaugam tranziția
				dfaTransitions[{currentStateName, symbol}].insert(stateNames[newState]);
			}
		}
	}

	// Determinam starile finale ale AFD
	for (auto it = stateNames.begin(); it != stateNames.end(); ++it) {
		const std::set<std::string>& stateSet = it->first; // Multimea de stari
		const std::string& name = it->second;             // Numele starii in AFD

		for (const auto& state : stateSet) {
			if (afn.GetFinalStates().count(state)) {
				dfaFinalStates.insert(name);
				break;
			}
		}
	}

	// Returnam automatul determinist generat
	return DeterministicFiniteAutomaton(dfaStates, afn.GetAlphabet(), dfaTransitions, dfaInitialState, dfaFinalStates);
}

