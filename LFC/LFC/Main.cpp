#include <iostream>
#include <string>
#include"DeterministicFiniteAutomaton.h"
int main() {
    std::cout << "Introdu expresia regulata: ";
    std::string regex = "a.b";

    // Conversie în forma poloneză inversată (RPN)
    std::string rpn = polishForm(regex);
    std::cout << "Expresia in RPN: " << rpn << "\n";

    // Construire automat din RPN
    DeterministicFiniteAutomaton dfa = BuildAutomatonFromRPN(rpn);
    std::cout << "Automatul finit determinist construit:\n";
    dfa.PrintAutomaton();

    return 0;
}
