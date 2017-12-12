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


	GeneticAlgorithmLogic* p_geneticAlgorithm = new GeneticAlgorithmLogic();
//	p_geneticAlgorithm->runGeneticAlgorithmTest();
	p_geneticAlgorithm->runGeneticAlgorithm();



//	for (int i = 0; i < 3; i++)
//	{
//		cout << sin(90.93) << endl;
//	}
//	


	delete p_geneticAlgorithm;

	_CrtDumpMemoryLeaks(); //to check Memory Leaks
	cout << "Main END" << endl; //toTest
	string stop; //toTest
	getline(cin, stop); //toTest
	return 0;
}

/*
TODO:
- tablica dynamiczna populacji -/
- wylicznie jakoœci drzewa -/
- mutowanie -/
- turnieje -/
- krzy¿owanie ~
- inne rzeczy
- ew. przerobiæ krzy¿ownaie tak, ¿eby wywo³ywaæ je od razu na root, bez du¿ego kodu w CTree

*/
