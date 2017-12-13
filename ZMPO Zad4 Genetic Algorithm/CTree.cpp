#include "CTree.h"

CTree::CTree()
{
	p_root = new CNode(0);
	expressionStringToTest = p_root->toString(); //toTest
	p_root->recalculateHeight();
}

CTree::~CTree()
{
	delete p_root;
}

CTree::CTree(CTree& otherTree)
{
	p_root = new CNode(*otherTree.p_root);
	quality = otherTree.getQuality();
	expressionStringToTest = p_root->toString(); //toTest
}

void CTree::recalculateQuality(vector<double*>* pv_dateToCalculate)
{
	this->quality = 0;

	int variablesIndexes[NUMBEROFVARIABLES];

	int calculationNumer = pv_dateToCalculate->size() / NUMBEROFVARIABLES + 1;

	for(int i = 0; i < calculationNumer; i++)
	{
		variablesIndexes[0] = i*(NUMBEROFVARIABLES + 1);
		variablesIndexes[1] = 1 + i*(NUMBEROFVARIABLES + 1);
		this->quality += pow(*(pv_dateToCalculate->at(2+ i*(NUMBEROFVARIABLES + 1))) - p_root->getValue(pv_dateToCalculate, variablesIndexes), 2);
	}
}

double CTree::getQuality()
{
	return quality;
}

void CTree::mutation(int chanceOfMutation)
{
	p_root->mutation(chanceOfMutation);
	p_root->recalculateHeight();
	p_root->recalculateHeight();
}

void CTree::refreshExpressionStringToTest()
{
	expressionStringToTest = p_root->toString();
}

void CTree::crossover(CTree* secondTree, int chanceOfNodeCrossover)
{
	CNode** pp_thisTreePart = nullptr;
	CNode** pp_secondTreePart = nullptr;

	int heightOfFirstSubtree = 0;
	int maxHeightOfSecondSubtree = MAXDEPTH;

	if (p_root->nodeType != OPERATORTYPE)
	{
		pp_thisTreePart = &p_root;
	}
	else if (heightOfFirstSubtree == MAXDEPTH - p_root->depth)
	{
		pp_thisTreePart = &p_root;
	}
	else if (p_root->height <= maxHeightOfSecondSubtree ^ UsefullMethods::ifOccur(chanceOfNodeCrossover))
	{
		pp_thisTreePart = &p_root;
	}
	else
	{
		int choosenChildrenIndex = UsefullMethods::ifOccur(50) ? 0 : 1;
		switch (p_root->nodeOperOrVar.at(0))
		{
		case SIN[0]:
		case COS[0]:
			choosenChildrenIndex = 0;
		case PLUS:
		case MINUS:
		case MULTIPLICATION:
		case DIVISION:
			if (p_root->v_children.at(choosenChildrenIndex)->nodeType != OPERATORTYPE)
			{
				pp_thisTreePart = &p_root->v_children.at(choosenChildrenIndex);
			}
			else if (heightOfFirstSubtree == MAXDEPTH - p_root->v_children.at(choosenChildrenIndex)->depth)
			{
				pp_thisTreePart = &p_root->v_children.at(choosenChildrenIndex);
			}
			else if (p_root->v_children.at(choosenChildrenIndex)->height <= maxHeightOfSecondSubtree && UsefullMethods::ifOccur(chanceOfNodeCrossover))
			{
				pp_thisTreePart = &p_root->v_children.at(choosenChildrenIndex);
			}
			else
			{
				pp_thisTreePart = p_root->v_children.at(choosenChildrenIndex)->choseCrossoverPart(chanceOfNodeCrossover, heightOfFirstSubtree, maxHeightOfSecondSubtree);
			}

//			pp_thisTreePart = p_root->v_children.at(choosenChildrenIndex)->choseCrossoverPartNEWNEW(chanceOfNodeCrossover, heightOfFirstSubtree, maxHeightOfSecondSubtree);
			break;
		default:
			cout << "Error13"; //toTest
		}
	}

	heightOfFirstSubtree = (*pp_thisTreePart)->height;
	maxHeightOfSecondSubtree = (MAXDEPTH - (*pp_thisTreePart)->depth);

	if (secondTree->p_root->nodeType != OPERATORTYPE)
	{
		pp_secondTreePart = &secondTree->p_root;
	}
	else if (heightOfFirstSubtree == MAXDEPTH - secondTree->p_root->depth)
	{
		pp_secondTreePart = &secondTree->p_root;
	}
	else if (secondTree->p_root->height <= maxHeightOfSecondSubtree && UsefullMethods::ifOccur(chanceOfNodeCrossover))
	{
		pp_secondTreePart = &secondTree->p_root;
	}
	else
	{
		int choosenChildrenIndex = UsefullMethods::ifOccur(50) ? 0 : 1;
		switch (secondTree->p_root->nodeOperOrVar.at(0))
		{
		case SIN[0]:
		case COS[0]:
			choosenChildrenIndex = 0;
		case PLUS:
		case MINUS:
		case MULTIPLICATION:
		case DIVISION:
			if (secondTree->p_root->v_children.at(choosenChildrenIndex)->nodeType != OPERATORTYPE)
			{
				pp_secondTreePart = &secondTree->p_root->v_children.at(choosenChildrenIndex);
			}
			else if (heightOfFirstSubtree == MAXDEPTH - secondTree->p_root->v_children.at(choosenChildrenIndex)->depth)
			{
				pp_secondTreePart = &secondTree->p_root->v_children.at(choosenChildrenIndex);
			}
			else if (secondTree->p_root->v_children.at(choosenChildrenIndex)->height <= maxHeightOfSecondSubtree && UsefullMethods::ifOccur(chanceOfNodeCrossover))
			{
				pp_secondTreePart = &secondTree->p_root->v_children.at(choosenChildrenIndex);
			}
			else
			{
				pp_secondTreePart = secondTree->p_root->v_children.at(choosenChildrenIndex)->choseCrossoverPart(chanceOfNodeCrossover, heightOfFirstSubtree, maxHeightOfSecondSubtree);
			}
//			pp_secondTreePart = secondTree->p_root->v_children.at(choosenChildrenIndex)->choseCrossoverPartNEWNEW(chanceOfNodeCrossover, heightOfFirstSubtree, maxHeightOfSecondSubtree);
			break;
		default:
			cout << "Error13"; //toTest
		}
	}

	CNode* p_temp = *pp_thisTreePart;
	*pp_thisTreePart = *pp_secondTreePart;
	*pp_secondTreePart = p_temp;

	p_root->recalculateDeph(0);
	p_root->recalculateHeight();

	secondTree->p_root->recalculateDeph(0);
	secondTree->p_root->recalculateHeight();


}

