#pragma once
#include "CNode.h"
using namespace std;

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__) //to check Memory Leaks


class CTree
{
public:
	CTree();
	~CTree();
	CTree(CTree &otherTree);
	void recalculateQuality(vector<double*>* pv_dateToCalculate);
	double getQuality();
//	bool compCTreeByQuality(CTree* firstTree, CTree* secondTree);
	void mutation(int chanceOfMutation);
	void refreshExpressionStringToTest(); //toTest
	void crossover(CTree* secondTree, int chanceOfNodeCrossover);
	void crossoverNEW(CTree* secondTree, int chanceOfNodeCrossover);

private:
	double quality;
	string expressionStringToTest; //toTest
	CNode *p_root;
};
