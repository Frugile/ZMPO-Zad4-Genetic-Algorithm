#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include "UsefullMethods.h"

#define MAXDEPTH 6
#define CHANCEOFOPERATOR 20
#define CHANCEOFNUMBER 40
#define MAXRANDOMNUMBER 90

#define NUMBERTYPE 'n'
#define OPERATORTYPE 'o'
#define VARIABLETYPE 'v'

#define PLUS '+'
#define MINUS '-'
#define MULTIPLICATION '*'
#define DIVISION '/'

#define SIN "sin"
#define COS "cos"

#define FIRSTVARIABLE "x"
#define SECONDVARIABLE "y"




#define new new(_NORMAL_BLOCK, __FILE__, __LINE__) //to check Memory Leaks

using namespace std;

class CNode
{
public:
	friend class CTree;
	CNode();
	void deleteChildren();
	CNode(int depth);
	~CNode();
	CNode(CNode &secondNode);
	void randomThisNode(int depth);
	void mutation(int chanceOfNodeMutation);
	string toString();
	double getValue(vector<double*>* pv_varsValues, int variablesIndexes[]);
	CNode** choseCrossoverPart(int chanceOfNodeCrossover, int heightOfFirstSubtree, int maxHeightOfSecondSubtree);
	void recalculateDeph(int depth);
	int recalculateHeight();
	int getHeight();
	//	double getValue(vector<double*>* pv_varsValues);


private:
	double value;
	int depth;
	int height;
	char nodeType;
	string nodeOperOrVar;
	vector<CNode *> v_children;
	char randomType();
	char randomEndType();
	static string randomVar(); //robić statyczne metody?
	string randomOper();
//	int randomNumber(int bound);
//	bool ifOccur(int chance);

};