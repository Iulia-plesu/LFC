#pragma once
#include <string>
class Transition
{
private:
	std::string m_deltaQs;
	char m_symbol;
	std::string m_deltaQf;
public:
	Transition(const std::string& deltaQs, char symbol, const std::string& deltaQf);
	Transition();
	std::string GetStartState() const;
	std::string GetEndState() const;
	char GetSymbol() const;

};

