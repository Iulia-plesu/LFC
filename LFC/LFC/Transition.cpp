#include "Transition.h"

Transition::Transition(const std::string& deltaQs, char symbol, const std::string& deltaQf)
	: m_deltaQs(deltaQs), m_symbol(symbol), m_deltaQf(deltaQf) {}


Transition::Transition()
{
		m_deltaQs = "nullptr";
		m_symbol = 'n';
		m_deltaQf = "nullptr";
}

std::string Transition::GetStartState() const
{
		return m_deltaQs;
}

std::string Transition::GetEndState() const
{
	return m_deltaQf;
}

char Transition::GetSymbol() const
{
	return m_symbol;
}
