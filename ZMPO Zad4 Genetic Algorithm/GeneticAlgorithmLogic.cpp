#include "GeneticAlgorithmLogic.h"

GeneticAlgorithmLogic::GeneticAlgorithmLogic()
{
	srand(time(NULL));
}

void GeneticAlgorithmLogic::deletePopulation()
{
	for (int i = 0; i < v_population.size(); i++)
	{
		delete v_population.at(i);
	}
}

GeneticAlgorithmLogic::~GeneticAlgorithmLogic()
{
	deletePopulation();
	for (int i = 0; i < (*pv_dateFromFile).size(); i++)
	{
		delete (*pv_dateFromFile).at(i);
	}
	delete pv_dateFromFile;
}

void GeneticAlgorithmLogic::sortPopulationByQuality()
{
	sort(v_population.begin(), v_population.end(), [](CTree* firstTree, CTree* secondTree){return firstTree->getQuality() < secondTree->getQuality();}); //lambda
}

void GeneticAlgorithmLogic::runGeneticAlgorithm()
{

	v_population.reserve(POPULATIONSIZE);
	for (size_t i = 0; i < POPULATIONSIZE; i++)
	{
		v_population.push_back(new CTree());
	}

	pv_dateFromFile = readDateFromFile(FILENAME);

	for (size_t i = 0; i < POPULATIONSIZE; i++)
	{
		v_population.at(i)->recalculateQuality(pv_dateFromFile); //z jakiegoś powodu, najdłużej działa przy ogromnej populacji
	}

	int stopDebugger = 42; //toTest

	sortPopulationByQuality();
	//sort(v_population.begin(), v_population.end(), compCTreeByQuality);

	stopDebugger = 42; //toTest

	for (int j = 0; j < 1000; j++)
	{
		for (size_t i = 0; i < POPULATIONSIZE; i++)
		{
			if (UsefullMethods::ifOccur(CHANCEOFTREEMUTATION))
			{
				v_population.at(i)->mutation(CHANCEOFNODEMUTATION);
				v_population.at(i)->refreshExpressionStringToTest();
			}
		}
		stopDebugger = 42; //toTest
	}




	for (int k = 0; k < 10; k++)
	{
		vector<CTree*> v_selectedPopulation;
		v_selectedPopulation.reserve(POPULATIONSIZE);
		for (size_t i = 0; i < POPULATIONSIZE; i++)
		{
			int firstTreeIndex = UsefullMethods::randomNumber(POPULATIONSIZE) - 1;
			int secondTreeIndex = UsefullMethods::randomNumber(POPULATIONSIZE) - 1;
			if (v_population.at(firstTreeIndex)->getQuality() < v_population.at(secondTreeIndex)->getQuality())
				v_selectedPopulation.push_back(new CTree(*v_population.at(firstTreeIndex)));
			else
				v_selectedPopulation.push_back(new CTree(*v_population.at(secondTreeIndex)));
		}
		deletePopulation();
		v_population.clear();
		v_population.swap(v_selectedPopulation);
		sortPopulationByQuality();
		stopDebugger = 42; //toTest

	}



	stopDebugger = 42; //toTest




	for (size_t i = 0; i < POPULATIONSIZE; i+=2)
	{
		
		v_population.at(i)->crossover(v_population.at(i + 1));
		v_population.at(i)->refreshExpressionStringToTest();
		v_population.at(i+1)->refreshExpressionStringToTest();

	}


	sortPopulationByQuality();



	stopDebugger = 76; //toTest yea GIT :D





}

vector<double*>* GeneticAlgorithmLogic::readDateFromFile(string fileName)
{
	ifstream file;
	file.open(fileName);
	vector<double*>* pv_dateFromFile = new vector<double*>;

	if (!file.good())
	{
		cout << "Error5"; //toTest
	}
	else
	{
		do 
		{
			char separator;
			double firstVal;
			double secondVal;
			double thirdVal;
			file >> firstVal >> separator >> secondVal >> separator >> thirdVal;
//			if(file.good())
//			{
				pv_dateFromFile->push_back(new double(firstVal));
				pv_dateFromFile->push_back(new double(secondVal));
				pv_dateFromFile->push_back(new double(thirdVal));
//			}
		} while (file.good());
	}
	
	return pv_dateFromFile;
}

//bool GeneticAlgorithmLogic::compCTreeByQuality(CTree* firstTree, CTree* secondTree) //nie działa, użyłem labdy :p
//{
//	return firstTree->getQuality() < secondTree->getQuality();
//}