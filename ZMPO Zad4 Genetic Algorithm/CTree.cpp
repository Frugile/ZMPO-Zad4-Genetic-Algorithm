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

	int variablesIndexes[2];

	int calculationNumer = pv_dateToCalculate->size() / 3;

	for(int i = 0; i < calculationNumer; i++)
	{
		variablesIndexes[0] = i*3;
		variablesIndexes[1] = 1 + i*3;
		this->quality += pow(*(pv_dateToCalculate->at(2+ i*3)) - p_root->getValue(pv_dateToCalculate, variablesIndexes), 2);
	}
}

double CTree::getQuality()
{
	return quality;
}

//bool CTree::compCTreeByQuality(CTree* firstTree, CTree* secondTree)
//{
//	return firstTree->getQuality() < secondTree->getQuality();
//}

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

/*

void CTree::crossover(CTree* secondTree, int chanceOfNodeCrossover)
{
	CNode** pp_thisTreePart = nullptr;
	CNode** pp_secondTreePart = nullptr; //może nie bedzie potrzebne

	//chose thisTree node

	if(p_root->nodeType != OPERATORTYPE || UsefullMethods::ifOccur(chanceOfNodeCrossover))
		pp_thisTreePart = &p_root;
	else
	{
		int choosenChildrenIndex = UsefullMethods::ifOccur(50) ? 0 : 1;
		switch (p_root->nodeOperOrVar.at(0))
		{
		case PLUS:
		case MINUS:
		case MULTIPLICATION:
		case DIVISION:
			if (p_root->v_children.at(choosenChildrenIndex)->nodeType != OPERATORTYPE || UsefullMethods::ifOccur(chanceOfNodeCrossover))
				pp_thisTreePart = &(p_root->v_children.at(choosenChildrenIndex));
			else
				pp_thisTreePart = p_root->v_children.at(choosenChildrenIndex)->choseCrossoverPart(chanceOfNodeCrossover, 0,  MAXDEPTH);
			/*if (UsefullMethods::ifOccur(50))
			{
				if (p_root->v_children.at(0)->nodeType != OPERATORTYPE)
					pp_thisTreePart = &(p_root->v_children.at(0));
				else
					pp_thisTreePart = p_root->v_children.at(0)->choseCrossoverPart();
			}
			else
			{
				if (p_root->v_children.at(1)->nodeType != OPERATORTYPE)
					pp_thisTreePart = &(p_root->v_children.at(1));
				else
					pp_thisTreePart = p_root->v_children.at(1)->choseCrossoverPart();
			}				#1#
			break;
		case SIN[0]:
		case COS[0]:
			if (p_root->v_children.at(0)->nodeType != OPERATORTYPE || UsefullMethods::ifOccur(chanceOfNodeCrossover))
				pp_thisTreePart = &(p_root->v_children.at(0));
			else
				pp_thisTreePart = p_root->v_children.at(0)->choseCrossoverPart(chanceOfNodeCrossover, 0, MAXDEPTH);
			break;
		default:
			cout << "Error7"; //toTest
		}




	}

	//choose secondTree node //chwilowe roziwązanie

	int heightOfFirstSubtree = (*pp_thisTreePart)->height;
	int maxHeightOfSecondSubtree = (MAXDEPTH - (*pp_thisTreePart)->depth);

//	int height = secondTree->p_root->getHeight(); //toTest
	bool ifFirstSubtreeFitsEnd = (MAXDEPTH - secondTree->p_root->depth == heightOfFirstSubtree);
	bool ifSecondSubtreeFits = (secondTree->p_root->getHeight() <= maxHeightOfSecondSubtree);


	if (secondTree->p_root->nodeType != OPERATORTYPE || UsefullMethods::ifOccur(chanceOfNodeCrossover) && ifSecondSubtreeFits || ifFirstSubtreeFitsEnd)
		pp_secondTreePart = &(secondTree->p_root);
	else
	{
		int choosenChildrenIndex = UsefullMethods::ifOccur(50) ? 0 : 1;

		switch (secondTree->p_root->nodeOperOrVar.at(0))
		{
		case PLUS:
		case MINUS:
		case MULTIPLICATION:
		case DIVISION:
			ifFirstSubtreeFitsEnd = (MAXDEPTH - secondTree->p_root->v_children.at(choosenChildrenIndex)->depth == heightOfFirstSubtree);
			ifSecondSubtreeFits = (secondTree->p_root->v_children.at(choosenChildrenIndex)->getHeight() <= maxHeightOfSecondSubtree);
//			height = secondTree->p_root->v_children.at(choosenChildrenIndex)->getHeight();
			if (secondTree->p_root->v_children.at(choosenChildrenIndex)->nodeType != OPERATORTYPE || (UsefullMethods::ifOccur(chanceOfNodeCrossover) && ifSecondSubtreeFits) || ifFirstSubtreeFitsEnd)
				pp_secondTreePart = &(secondTree->p_root->v_children.at(choosenChildrenIndex));
			else
				pp_secondTreePart = secondTree->p_root->v_children.at(choosenChildrenIndex)->choseCrossoverPart(chanceOfNodeCrossover, heightOfFirstSubtree, maxHeightOfSecondSubtree);
			
			break;
		case SIN[0]:
		case COS[0]:
			ifFirstSubtreeFitsEnd = (MAXDEPTH - secondTree->p_root->v_children.at(0)->depth == heightOfFirstSubtree);
			ifSecondSubtreeFits = (secondTree->p_root->v_children.at(0)->getHeight() <= maxHeightOfSecondSubtree);
			if (secondTree->p_root->v_children.at(0)->nodeType != OPERATORTYPE || (UsefullMethods::ifOccur(chanceOfNodeCrossover) && ifSecondSubtreeFits) || ifFirstSubtreeFitsEnd)
				pp_secondTreePart = &(secondTree->p_root->v_children.at(0));
			else
				pp_secondTreePart = secondTree->p_root->v_children.at(0)->choseCrossoverPart(chanceOfNodeCrossover, heightOfFirstSubtree, maxHeightOfSecondSubtree);
			break;
		default:
			cout << "Error7"; //toTest
		}




	}


	//swap

	CNode* p_temp = *pp_thisTreePart;
	*pp_thisTreePart = *pp_secondTreePart;
	*pp_secondTreePart = p_temp;


	//recalculate depths
	p_root->recalculateDeph(0);
	secondTree->p_root->recalculateDeph(0);
	p_root->recalculateHeight();
	secondTree->p_root->recalculateHeight();

	//TODO: 
	//- make it "deph safe" - so it wont make trees that exceed max deph
}

void CTree::crossoverNEW(CTree* secondTree, int chanceOfNodeCrossover)
{
	CNode* p_node1 = nullptr;
	CNode* p_node2 = nullptr;
	CNode** pp_thisTreePart = &p_node1;
	CNode** pp_secondTreePart = &p_node2;

	pp_thisTreePart = p_root->choseCrossoverPartNEW(pp_thisTreePart, chanceOfNodeCrossover, 0, MAXDEPTH);

	int heightOfFirstSubtree = (*pp_thisTreePart)->height;
	int maxHeightOfSecondSubtree = (MAXDEPTH - (*pp_thisTreePart)->depth);


	/*pp_secondTreePart = #1#secondTree->p_root->choseCrossoverPartNEW(pp_secondTreePart, chanceOfNodeCrossover, heightOfFirstSubtree, maxHeightOfSecondSubtree);

	CNode* p_temp = *pp_thisTreePart;
	*pp_thisTreePart = *pp_secondTreePart;
	*pp_secondTreePart = p_temp;

	p_root->recalculateDeph(0);
	secondTree->p_root->recalculateDeph(0);
	p_root->recalculateHeight();
	secondTree->p_root->recalculateHeight();

}
*/

void CTree::crossoverNEWNEW(CTree* secondTree, int chanceOfNodeCrossover)
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
				pp_thisTreePart = p_root->v_children.at(choosenChildrenIndex)->choseCrossoverPartNEWNEW(chanceOfNodeCrossover, heightOfFirstSubtree, maxHeightOfSecondSubtree);
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
				pp_secondTreePart = secondTree->p_root->v_children.at(choosenChildrenIndex)->choseCrossoverPartNEWNEW(chanceOfNodeCrossover, heightOfFirstSubtree, maxHeightOfSecondSubtree);
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

