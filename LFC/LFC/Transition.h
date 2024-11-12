#pragma once
#include <string>
class Transition
{
private:
	std::string m_deltaQs;
	char m_symbol;
	std::string m_deltaQf;
public:
	Transition() = default;
	Transition( const std::string& deltaQs,  char symbol, const std::string& deltaQf)
		: m_deltaQs(deltaQs), m_symbol(symbol), m_deltaQf(deltaQf)
	{}
	std::string GetStartState() const {
		return m_deltaQs;
	}
	std::string GetEndState() const {
		return m_deltaQf;
	}
	char GetSymbol() const {
		return m_symbol;
	}

};

