#include"DeterministicFiniteAutomaton.h"
#include<iostream>
#include <sstream>

DeterministicFiniteAutomaton::DeterministicFiniteAutomaton(const std::set<std::string>& Q, 
	const std::set<char>& sigma, 
	const std::string& q0, 
	const std::set<std::string>& F)
	: m_Q(Q), m_sigma(sigma), m_q0(q0), m_F(F) {}

DeterministicFiniteAutomaton::DeterministicFiniteAutomaton(const std::set<std::string>& Q,
	const std::set<char>& sigma, 
	const std::map<std::pair<std::string, char>, std::string>& delta, 
	const std::string& q0, 
	const std::set<std::string>& F): m_Q(Q), m_sigma(sigma), m_delta(delta), m_q0(q0), m_F(F) {}




bool DeterministicFiniteAutomaton::CheckWord(const std::string& input) const
{
	std::string currentState = m_q0;
	for (char symbol : input) {
		auto it = m_delta.find({ currentState, symbol });
		if (it == m_delta.end()) {
			return false; 
		}
		currentState = it->second;
	}
	return m_F.find(currentState) != m_F.end();
}

void DeterministicFiniteAutomaton::AddTransition(const std::string& startState, char symbol, const std::string& endState)
{
	m_delta[{startState, symbol}] = endState;
}

bool DeterministicFiniteAutomaton::VerifyAutomaton() const
{
	for (const auto& transition : m_delta) {
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

void DeterministicFiniteAutomaton::PrintAutomaton() const
{
	std::cout << "States: ";
	for (const auto& state : m_Q) std::cout << state << " ";

	std::cout << "\nAlphabet: ";

	for (const auto& symbol : m_sigma) std::cout << symbol << " ";

	std::cout << "\nInitial state: " << m_q0 
	<<"\nFinal states: ";

	for (const auto& finalState : m_F) std::cout << finalState << " ";
	std::cout << "\nTransitions:\n";

	for (const auto& transition : m_delta) {
		std::cout << transition.first.first << " --" << transition.first.second
			<< "--> " << transition.second << "\n";
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

const std::map<std::pair<std::string, char>, std::string>& DeterministicFiniteAutomaton::GetTransitions() const
{
	 return m_delta; 
}

int priority(char op)
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

std::string polishForm(const std::string& expression)
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

int stateCounter = 0;

// Funcție pentru a genera un nume unic de stare
std::string GenerateUniqueState() {
	std::ostringstream stateName;
	stateName << "q" << stateCounter++;
	return stateName.str();
}

DeterministicFiniteAutomaton BuildBasicAutomaton(char symbol) {
    // Generăm stări unice
    std::string initialState = GenerateUniqueState();
    std::string finalState = GenerateUniqueState();

    // Construim automatul
    std::set<std::string> states = { initialState, finalState };
    std::set<char> alphabet = { symbol };
    std::set<std::string> finalStates = { finalState };

    DeterministicFiniteAutomaton dfa(states, alphabet, initialState, finalStates);
    dfa.AddTransition(initialState, symbol, finalState);

    return dfa;
}

DeterministicFiniteAutomaton Concatenate(const DeterministicFiniteAutomaton& a1, const DeterministicFiniteAutomaton& a2)
{
	
	std::set<std::string> states{ a1.GetStates() };
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

DeterministicFiniteAutomaton Union(const DeterministicFiniteAutomaton& a1, const DeterministicFiniteAutomaton& a2) {
	// 1. Generăm stări unice pentru new_start și new_final
	std::string newStart = GenerateUniqueState();
	std::string newFinal = GenerateUniqueState();

	// 2. Combinăm stările
	std::set<std::string> states = { newStart, newFinal };
	states.insert(a1.GetStates().begin(), a1.GetStates().end());
	states.insert(a2.GetStates().begin(), a2.GetStates().end());

	// 3. Combinăm alfabetele
	std::set<char> alphabet = a1.GetAlphabet();
	alphabet.insert(a2.GetAlphabet().begin(), a2.GetAlphabet().end());

	// 4. Combinăm tranzițiile
	std::map<std::pair<std::string, char>, std::string> transitions = a1.GetTransitions();
	auto a2Transitions = a2.GetTransitions();
	transitions.insert(a2Transitions.begin(), a2Transitions.end());


	transitions[{newStart, '\0'}] = a1.GetInitialState();
	transitions[{newStart, 'L'}] = a2.GetInitialState();
	for (const auto& state : a1.GetFinalStates()) {
		transitions[{state, '\0'}] = newFinal; 
	}
	for (const auto& state : a2.GetFinalStates()) {
		transitions[{state, '\0'}] = newFinal;
	}

	// 5. Returnăm noul automat
	return DeterministicFiniteAutomaton(states, alphabet, transitions, newStart, { newFinal });
}

DeterministicFiniteAutomaton Star(const DeterministicFiniteAutomaton& a) {
	// Generăm stări noi pentru start și final
	std::string newStart = GenerateUniqueState();
	std::string newFinal = GenerateUniqueState();

	// Combinăm stările
	std::set<std::string> states = { newStart, newFinal };
	states.insert(a.GetStates().begin(), a.GetStates().end());

	// Preluăm alfabetul și tranzițiile existente
	std::set<char> alphabet = a.GetAlphabet();
	std::map<std::pair<std::string, char>, std::string> transitions = a.GetTransitions();

	// Adăugăm tranziții lambda
	transitions[{newStart, '\0'}] = a.GetInitialState();  // new_start -> vechea stare inițială
	transitions[{newStart, 'L'}] = newFinal;            // new_start -> new_final
for (const auto& state : a.GetFinalStates()) 
	{
    transitions[{state, '\0'}] = a.GetInitialState(); // vechea stare finală -> vechea stare inițială
    transitions[{state, 'L'}] = newFinal;           // vechea stare finală -> new_final
	}


	return DeterministicFiniteAutomaton(states, alphabet, transitions, newStart, { newFinal });
}

DeterministicFiniteAutomaton BuildAutomatonFromRPN(const std::string& rpn)
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

DeterministicFiniteAutomaton BuildAutomatonFromFile(const std::string& filename)
{

std::ifstream file(filename);

std::set<std::string> states;
std::set<char> alphabet;
std::string initialState;
std::set<std::string> finalStates;
std::map<std::pair<std::string, char>, std::string> transitions;

std::string line;


std::getline(file, line);
std::istringstream statesStream(line);
std::string state;
while (statesStream >> state) {
	states.insert(state);
}

std::getline(file, line);
std::istringstream alphabetStream(line);
char symbol;
while (alphabetStream >> symbol) {
	alphabet.insert(symbol);
}

std::getline(file, line);
initialState = line;

std::getline(file, line);
std::istringstream finalStatesStream(line);
while (finalStatesStream >> state) {
	finalStates.insert(state);
}

while (std::getline(file, line)) {
	std::istringstream transitionStream(line);
	std::string startState, endState;
	char transitionSymbol;
	transitionStream >> startState >> transitionSymbol >> endState;
	transitions[{startState, transitionSymbol}] = endState;
}

file.close();

return DeterministicFiniteAutomaton(states, alphabet, transitions, initialState, finalStates);
}
