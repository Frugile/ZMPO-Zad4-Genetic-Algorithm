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

void GeneticAlgorithmLogic::runGeneticAlgorithmTest()
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

	sortPopulationByQuality(); //toTest
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




	for (int k = 0; k < 1; k++)
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
	}



	stopDebugger = 42; //toTest



	for (int k = 0; k < 1000; k++)
	{

		for (size_t i = 0; i < POPULATIONSIZE; i += 2)
		{

//			v_population.at(i)->crossover(v_population.at(i + 1), CHANCEOFNODECROSSOVER);
			v_population.at(i)->crossoverNEWNEW(v_population.at(i + 1), CHANCEOFNODECROSSOVER);
			v_population.at(i)->refreshExpressionStringToTest();
			v_population.at(i + 1)->refreshExpressionStringToTest();
			v_population.at(i)->recalculateQuality(pv_dateFromFile);
			v_population.at(i + 1)->recalculateQuality(pv_dateFromFile);
		}
//
//		int firstTreeIndex = UsefullMethods::randomNumber(POPULATIONSIZE) - 1;
//		int secondTreeIndex = UsefullMethods::randomNumber(POPULATIONSIZE) - 1;
//		v_population.at(firstTreeIndex)->crossoverNEW(v_population.at(secondTreeIndex), CHANCEOFNODECROSSOVER);
//		v_population.at(firstTreeIndex)->refreshExpressionStringToTest();
//		v_population.at(secondTreeIndex)->refreshExpressionStringToTest();
//		v_population.at(firstTreeIndex)->recalculateQuality(pv_dateFromFile);
//		v_population.at(secondTreeIndex)->recalculateQuality(pv_dateFromFile);

		sortPopulationByQuality(); //toTest
		stopDebugger = 76; //toTest yea GIT :D

	}





	stopDebugger = 76; //toTest 





}

void GeneticAlgorithmLogic::runGeneticAlgorithm()
{
	// STWORZNIE

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

	double bestQualityTillNow = 100;

	while (true)
	{
		for (int repeat = 0; repeat < 1; repeat++)
		{

			// SELEKCJA

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

			// KRZYŻOWNIE

			for (size_t i = 0; i < POPULATIONSIZE; i += 2)
			{
				if (UsefullMethods::ifOccur(CHANCEOFTREECROSSOVER))
				{
					v_population.at(i)->crossoverNEWNEW(v_population.at(i + 1), CHANCEOFNODECROSSOVER);
					v_population.at(i)->refreshExpressionStringToTest();
					v_population.at(i + 1)->refreshExpressionStringToTest();
					v_population.at(i)->recalculateQuality(pv_dateFromFile);
					v_population.at(i + 1)->recalculateQuality(pv_dateFromFile);
				}
			}

			// MUTACJA

			for (size_t i = 0; i < POPULATIONSIZE; i++)
			{
				if (UsefullMethods::ifOccur(CHANCEOFTREEMUTATION))
				{
					v_population.at(i)->mutation(CHANCEOFNODEMUTATION);
					v_population.at(i)->refreshExpressionStringToTest();
				}
			}

			for (size_t i = 0; i < POPULATIONSIZE; i++)
			{
				v_population.at(i)->recalculateQuality(pv_dateFromFile);
			}

			sortPopulationByQuality(); //toTest
			bestQualityTillNow = (v_population.at(0)->getQuality() < bestQualityTillNow) ? v_population.at(0)->getQuality() : bestQualityTillNow;//toTest

		}
		sortPopulationByQuality(); //toTest

		int stopDebugger = 8; //toTest 
	}

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