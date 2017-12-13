﻿#pragma once
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
	void mutation(int chanceOfMutation);
	void refreshExpressionStringToTest(); //toTest
	void crossover(CTree* secondTree, int chanceOfNodeCrossover);
	string expressionStringToTest; //toTest

private:
	double quality;
	CNode *p_root;
};
