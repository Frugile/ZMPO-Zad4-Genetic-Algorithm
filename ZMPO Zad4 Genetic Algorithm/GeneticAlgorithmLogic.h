#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

#include "CNode.h"
#include "CTree.h"

#define POPULATIONSIZE 1000

#define CHANCEOFTREEMUTATION 60
#define CHANCEOFNODEMUTATION 70

#define CHANCEOFTREECROSSOVER 50
#define CHANCEOFNODECROSSOVER 40

#define DESIREDQUALITY 1.0


//#define FILENAME "C:\\Users\\Frugile\\Documents\\Visual Studio 2015\\Projects\\ZMPO Zad4 Genetic Algorithm\\Debug\\x.txt"
#define FILENAME "C:\\Users\\Frugile\\Documents\\Visual Studio 2015\\Projects\\ZMPO Zad4 Genetic Algorithm\\Debug\\xy_pl_xx.txt" //PC
#define FILENAMERESULT "C:\\Users\\Frugile\\Documents\\Visual Studio 2015\\Projects\\ZMPO Zad4 Genetic Algorithm\\Debug\\result.txt" //PC

//#define FILENAME "C:\\Users\\najle\\Documents\\Visual Studio 2015\\Projects\\ZMPO Zad4 Genetic Algorithm\\Debug\\xy_pl_xx.txt" //Surface


#define new new(_NORMAL_BLOCK, __FILE__, __LINE__) //to check Memory Leaks

using namespace std;

class GeneticAlgorithmLogic
{
public:
	GeneticAlgorithmLogic();
	~GeneticAlgorithmLogic();
//	void runGeneticAlgorithmTest();
	void runGeneticAlgorithm();
private:
	vector<CTree*> v_population; 
	vector<double*>* pv_dateFromFile;
	vector<double*>* readDateFromFile(string fileName);
	void saveDateToFile(string fileName, string strintgToSave);
	void deletePopulation();
	void sortPopulationByQuality();
};
