#include "CTree.h"

CTree::CTree()
{
	p_root = new CNode(0);
	expressionStringToTest = p_root->toString(); //toTest
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
}

void CTree::refreshExpressionStringToTest()
{
	expressionStringToTest = p_root->toString();
}


void CTree::crossover(CTree* secondTree)
{
	CNode** pp_thisTreePart = nullptr;
	CNode** pp_secondTreePart = nullptr; //może nie bedzie potrzebne

	//chose thisTree node

	if(p_root->nodeType != OPERATORTYPE)
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
			if (p_root->v_children.at(choosenChildrenIndex)->nodeType != OPERATORTYPE)
				pp_thisTreePart = &(p_root->v_children.at(choosenChildrenIndex));
			else
				pp_thisTreePart = p_root->v_children.at(choosenChildrenIndex)->choseCrossoverPart();
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
			}				*/
			break;
		case SIN[0]:
		case COS[0]:
			if (p_root->v_children.at(0)->nodeType != OPERATORTYPE)
				pp_thisTreePart = &(p_root->v_children.at(0));
			else
				pp_thisTreePart = p_root->v_children.at(0)->choseCrossoverPart();
			break;
		default:
			cout << "Error7"; //toTest
		}




	}

	//choose secondTree node //chwilowe roziwązanie

	if (secondTree->p_root->nodeType != OPERATORTYPE)
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
			if (secondTree->p_root->v_children.at(choosenChildrenIndex)->nodeType != OPERATORTYPE)
				pp_secondTreePart = &(secondTree->p_root->v_children.at(choosenChildrenIndex));
			else
				pp_secondTreePart = secondTree->p_root->v_children.at(choosenChildrenIndex)->choseCrossoverPart();
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
			}				*/
			break;
		case SIN[0]:
		case COS[0]:
			if (secondTree->p_root->v_children.at(0)->nodeType != OPERATORTYPE)
				pp_secondTreePart = &(secondTree->p_root->v_children.at(0));
			else
				pp_secondTreePart = secondTree->p_root->v_children.at(0)->choseCrossoverPart();
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




	//TODO: 
	//- make it "deph safe" - so it wont make trees that exceed max deph
}

