#include "DeterministicFiniteAutomaton.h"
#include"Operation.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include<regex>

bool IsValidRegex(const std::string& expression) 
{
    try 
    {
        std::regex testRegex(expression);
    }
    catch (const std::regex_error& e) 
    {  
        std::cerr << "Error: Invalid regular expression. " << e.what() << "\n";
        return false;
    }
    return true; 
}

void DisplayMenu() 
{
    std::cout << "Menu:\n"
        << "(a) Display the readable regular expression from the file.\n"
        << "(b) Display the automaton M both in the console and in an output file.\n"
        << "(c) Check if a word is accepted by the automaton.\n"
        << "(d) Display the nondeterministic automaton with lambda transitions.\n"
        << "(e) Verify automaton\n"
        << "(f) Exit.\n";
}

std::string ReadRegexFromFile(const std::string& filename) 
{
    std::ifstream file(filename);
    std::string regex;
    std::getline(file, regex);
    file.close();
    return regex;
}

void WriteAutomatonToFile(const DeterministicFiniteAutomaton& dfa, const std::string& filename) 
{
    std::ofstream file(filename);

    file << "States: ";
    for (const auto& state : dfa.GetStates()) 
    {
        file << state << " ";
    }

    file << "\nAlphabet: ";
    for (const auto& symbol : dfa.GetAlphabet()) 
    {
        file << symbol << " ";
    }

    file << "\nInitial state: " << dfa.GetInitialState()
        << "\nFinal states: ";
    for (const auto& finalState : dfa.GetFinalStates()) 
    {
        file << finalState << " ";
    }

    file << "\nTransitions:\n";
   
    for (const auto& transition : dfa.GetTransitions()) 
    {
        const auto& fromState = transition.first.first;
        char symbol = transition.first.second;
        const auto& toStates = transition.second;

        for (const auto& toState : toStates) 
        {
            file << fromState << " --" << symbol << "--> " << toState << "\n";
        }
    }
    file.close();
    std::cout << "The automaton has been saved in the file " << filename << "\n";
}

int main() 
{
    std::string inputFile = "exp.txt";
    std::string regex = ReadRegexFromFile(inputFile);

    std::cout << "Read regular expression: " << regex << "\n";

    if (!IsValidRegex(regex)) 
    {
        return 1;
    }
    std::cout << "The regular expression is valid.\n";


    Operation operation;

    std::string rpn = operation.polishForm(regex);


    DeterministicFiniteAutomaton nfa = operation.BuildAutomatonFromRPN(rpn);

    DeterministicFiniteAutomaton dfa = operation.ConvertLambdaNFAtoDFA(nfa);

    char option;
    do {
        DisplayMenu();
        std::cout << "Select the desired option: ";
        std::cin >> option;

        switch (option) {
        case 'a':
            std::cout << "Readable regular expression: " << rpn << "\n";
            break;

        case 'b':
            std::cout << "Displaying automaton M:\n";
            dfa.PrintAutomaton();
            std::cout << '\n';
            dfa.PrintTransitionTable(dfa);
            WriteAutomatonToFile(dfa, "output.txt");
            break;

        case 'c': {
            std::string word;
            std::cout << "Enter the word to check: ";
            std::cin >> word;
            if (dfa.CheckWord(word)) {
                std::cout << "The word \"" << word << "\" is accepted by the automaton.\n";
            }
            else {
                std::cout << "The word \"" << word << "\" is not accepted by the automaton.\n";
            }
            break;
        }
        case 'd': 
            std::cout << "Nondeterministic automaton with lambda transitions:\n";
            nfa.PrintAutomaton();
            std::cout << '\n';
            nfa.PrintTransitionTable(nfa);
            break;
        
        case 'e':
            if (dfa.VerifyAutomaton()) {
                std::cout << "Is a valid automaton\n";
            }
            else {
                std::cout << "Is not a valid automaton \n";
            }
            break;

        case 'f':
            std::cout << "Exiting the program.\n";
            break;

        default:
            std::cout << "Invalid option. Please try again.\n";
        }

    } while (option != 'f');

    return 0;
}
