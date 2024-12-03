#pragma once
#include"DeterministicFiniteAutomaton.h"
#include <map>
#include <set>
#include <string>
class Operation
{
public:
    int priority(char op);

    std::string polishForm(const std::string& expression);

    DeterministicFiniteAutomaton BuildBasicAutomaton(char symbol);

    DeterministicFiniteAutomaton Concatenate(const DeterministicFiniteAutomaton& a1, const DeterministicFiniteAutomaton& a2);

   
    DeterministicFiniteAutomaton Union(const DeterministicFiniteAutomaton& a1, const DeterministicFiniteAutomaton& a2);

    DeterministicFiniteAutomaton Star(const DeterministicFiniteAutomaton& a);


    DeterministicFiniteAutomaton BuildAutomatonFromRPN(const std::string& rpn);



    std::set<std::string> LambdaClosure(
        const std::string& state,
        const std::map<std::pair<std::string, char>, std::set<std::string>>& transitions);



    DeterministicFiniteAutomaton ConvertLambdaNFAtoDFA(const DeterministicFiniteAutomaton& afn);
};

