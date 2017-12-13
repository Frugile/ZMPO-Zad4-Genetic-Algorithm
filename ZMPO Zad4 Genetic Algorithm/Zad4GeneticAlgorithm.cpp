#include "UserInterface.h"
#include <iostream>
#include <string>
#include <vector>


#pragma region MemoryCheck
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include "GeneticAlgorithmLogic.h"
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)   
#pragma endregion


#define WELCOME "Hi! \n"

using namespace std;



int main()
{
//	cout << WELCOME;;


	GeneticAlgorithmLogic geneticAlgorithm;
	geneticAlgorithm.runGeneticAlgorithm();
	

	_CrtDumpMemoryLeaks(); //to check Memory Leaks
	cout << "Main END" << endl; //toTest
	string stop; //toTest
	getline(cin, stop); //toTest
	return 0;
}

