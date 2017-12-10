#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "CTree.h"

#define NUMBERTYPE 'n'
#define OPERATORTYPE 'o'
#define VARIABLETYPE 'v'

#define COMMAND1 "enter"
#define COMMAND2 "vars"
#define COMMAND3 "print"
#define COMMAND4 "comp"
#define COMMAND5 "join"
#define COMMAND6 "end"
#define ERROR_BADCOMMAND "Podano niepoprawna komende, sprobuj jeszcze raz:\n"
#define ERROR_TEXT_UNNOWN "Wystapil nieznany blad"
#define ERROR_TEXT_BAD_EXPRESSION "Podano blednie wyrazenie, nastapila proba naprawy i teraz wyrazenie ma postac:"
#define ERROR_TEXT_BAD_NUMBER_OF_VAR "Podano blednie liczbe zmiennych, sprobuj jeszcze raz:"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)  //to check Memory Leaks

using namespace std;

class UserInterface
{
public:
	void startInterface(CTree **p_tree);
private:
	CTree* p_tree;
	int commandCounter = 0; //for TESTING CODE
	bool isTest = true; //for TESTING CODE
};