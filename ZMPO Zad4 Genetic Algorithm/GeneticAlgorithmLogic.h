#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

#include "CNode.h"
#include "CTree.h"

#define POPULATIONSIZE 4

#define CHANCEOFTREEMUTATION 20
#define CHANCEOFNODEMUTATION 10

#define CHANCEOFTREECROSSOVER 20
#define CHANCEOFNODECROSSOVER 10


//#define FILENAME "C:\\Users\\Frugile\\Documents\\Visual Studio 2015\\Projects\\ZMPO Zad4 Genetic Algorithm\\Debug\\x.txt"
#define FILENAME "C:\\Users\\Frugile\\Documents\\Visual Studio 2015\\Projects\\ZMPO Zad4 Genetic Algorithm\\Debug\\xy_pl_xx.txt" //PC
//#define FILENAME "C:\\Users\\najle\\Documents\\Visual Studio 2015\\Projects\\ZMPO Zad4 Genetic Algorithm\\Debug\\xy_pl_xx.txt" //Surface


#define new new(_NORMAL_BLOCK, __FILE__, __LINE__) //to check Memory Leaks

using namespace std;

class GeneticAlgorithmLogic
{
public:
	GeneticAlgorithmLogic();
	void deletePopulation();
	~GeneticAlgorithmLogic();
	void sortPopulationByQuality();
	void runGeneticAlgorithm();
private:
	vector<CTree*> v_population; 
	vector<double*>* pv_dateFromFile;
	vector<double*>* readDateFromFile(string fileName);
//	bool compCTreeByQuality(CTree* firstTree, CTree* secondTree); //nie działa, użyłem labdy
};
