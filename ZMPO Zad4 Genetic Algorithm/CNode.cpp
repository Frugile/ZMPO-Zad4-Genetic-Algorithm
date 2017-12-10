#include "CNode.h"

CNode::CNode() : value(0), depth(0), nodeType(0), v_children()
{
}

CNode::~CNode()
{
	deleteChildren();
}

CNode::CNode(CNode& secondNode)
{
	value = secondNode.value;
	nodeOperOrVar = secondNode.nodeOperOrVar;
	nodeType = secondNode.nodeType;
	depth = secondNode.depth;
	for (int i = 0; i < secondNode.v_children.size(); i++)
	{
		v_children.push_back(new CNode(*secondNode.v_children.at(i)));
	}
}

void CNode::deleteChildren()
{
	for (int i = 0; i < v_children.size(); i++)
	{
		delete v_children.at(i);
	}
}

CNode::CNode(int depth)
{
	randomThisNode(depth);
}

void CNode::randomThisNode(int depth)
{
	this->depth = depth;

	nodeType = (depth == MAXDEPTH) ? randomEndType() : randomType();
	
	switch (nodeType)
	{
	case OPERATORTYPE:
		nodeOperOrVar = randomOper();
		switch (nodeOperOrVar.at(0))
		{
		case PLUS:
		case MINUS:
		case MULTIPLICATION:
		case DIVISION:
			v_children.push_back(new CNode(depth + 1));
			v_children.push_back(new CNode(depth + 1));
			break;
		case SIN[0]:
		case COS[0]:
			v_children.push_back(new CNode(depth + 1));
			break;
		default:
			cout << "Error0"; //toTest
		}
		break;
	case NUMBERTYPE:
		value = UsefullMethods::randomNumber(MAXRANDOMNUMBER);
		break;
	case VARIABLETYPE:
		nodeOperOrVar = randomVar();
		break;
	default:
		cout << "Error1"; //toTest
	}
}

void CNode::mutation(int chanceOfMutation)
{
	if(nodeType == OPERATORTYPE)
	{
		if (UsefullMethods::ifOccur(chanceOfMutation)) 
		{
			nodeOperOrVar = "";
			deleteChildren();
			v_children.clear();
			randomThisNode(depth);
		}
		else
		{
			switch (nodeOperOrVar.at(0))
			{
			case PLUS:
			case MINUS:
			case MULTIPLICATION:
			case DIVISION:
				if (UsefullMethods::ifOccur(50))
					v_children.at(0)->mutation(chanceOfMutation);
				else
					v_children.at(1)->mutation(chanceOfMutation);
				break;
			case SIN[0]:
			case COS[0]:
				v_children.at(0)->mutation(chanceOfMutation);
				break;
			default:
				cout << "Error6"; //toTest
			}
		}
	}
	else
	{
//		value = 0;
		nodeOperOrVar = "";
		randomThisNode(depth);
	}
}

string CNode::randomVar()
{
	return (UsefullMethods::ifOccur(50)) ? FIRSTVARIABLE : SECONDVARIABLE;
}

string CNode::randomOper()
{
	string oper;
	int randomNumb = UsefullMethods::randomNumber(6);
	switch (randomNumb)
	{
	case 1:
		oper = PLUS;
		break;
	case 2:
		oper = MINUS;
		break;
	case 3:
		oper = MULTIPLICATION;
		break;
	case 4:
		oper = DIVISION;
		break;
	case 5:
		oper = SIN;
		break;
	case 6:
		oper = COS;
		break;
	default:
		cout << "Error2"; //toTest
	}
	return oper;
}

char CNode::randomType()
{
	char type = OPERATORTYPE;

	int randomNumb = UsefullMethods::randomNumber(100);

	if(randomNumb < 100 - CHANCEOFOPERATOR)
	{
		if(randomNumb < 100 - (CHANCEOFOPERATOR + CHANCEOFNUMBER))
			type = VARIABLETYPE;
		else
			type = NUMBERTYPE;
	}
	return type;
}

char CNode::randomEndType()
{
	/*char type = NUMBERTYPE;

	int randomNumb = randomNumber(100-CHANCEOFOPERATOR);

	if (randomNumb < 100 - (CHANCEOFOPERATOR + CHANCEOFNUMBER))
		type = VARIABLETYPE;
	
	return type;*/

	return UsefullMethods::ifOccur(CHANCEOFNUMBER / (100 - CHANCEOFOPERATOR)) ? NUMBERTYPE : VARIABLETYPE;

}

string CNode::toString()
{
	string text;
	stringstream stream;
	switch (nodeType)
	{
	case OPERATORTYPE:
		text = nodeOperOrVar;
		for (int i = 0; i < v_children.size(); i++)
		{
			text.append(" ").append(v_children.at(i)->toString());
		}
		break;
	case NUMBERTYPE:
		stream << fixed << setprecision(2) << value;
		text = stream.str();
		break;
	case VARIABLETYPE:
		text = nodeOperOrVar;
		break;
	default:
		text = "error in toString CNode"; //toTest
	}
	return text;
}

double CNode::getValue(vector<double*>* pv_varsValues, int variablesIndexes[])
{
	double value;
	switch (nodeType)
	{
	case OPERATORTYPE:
		if (nodeOperOrVar[0] == PLUS) { value = v_children.at(0)->getValue(pv_varsValues, variablesIndexes) + v_children.at(1)->getValue(pv_varsValues, variablesIndexes); }
		if (nodeOperOrVar[0] == MINUS) { value = v_children.at(0)->getValue(pv_varsValues, variablesIndexes) - v_children.at(1)->getValue(pv_varsValues, variablesIndexes); }
		if (nodeOperOrVar[0] == MULTIPLICATION) { value = v_children.at(0)->getValue(pv_varsValues, variablesIndexes) * v_children.at(1)->getValue(pv_varsValues, variablesIndexes); }
		if (nodeOperOrVar[0] == DIVISION) { value = v_children.at(0)->getValue(pv_varsValues, variablesIndexes) / v_children.at(1)->getValue(pv_varsValues, variablesIndexes); }
		if (nodeOperOrVar == SIN) { value = sin(v_children.at(0)->getValue(pv_varsValues, variablesIndexes)); }
		if (nodeOperOrVar == COS) { value = cos(v_children.at(0)->getValue(pv_varsValues, variablesIndexes)); }
		break;
	case NUMBERTYPE:
		value = this->value;
		break;
	case VARIABLETYPE:
		if (nodeOperOrVar == FIRSTVARIABLE)
			value = *(pv_varsValues->at(variablesIndexes[0]));
		if (nodeOperOrVar == SECONDVARIABLE)
			value = *(pv_varsValues->at(variablesIndexes[1]));
		break;
	default:
		cout << "Error4"; //toTest
		value = 0; //toTest
	}
	return value;
}

CNode** CNode::choseCrossoverPart()
{
	CNode** pp_choosenPart = nullptr;

	switch (nodeOperOrVar.at(0))
	{
	case PLUS:
	case MINUS:
	case MULTIPLICATION:
	case DIVISION:
		int choosenChildrenIndex = UsefullMethods::ifOccur(50) ? 0 : 1;
		if (v_children.at(choosenChildrenIndex)->nodeType != OPERATORTYPE)
			pp_choosenPart = &(v_children.at(choosenChildrenIndex));
		else
			pp_choosenPart = v_children.at(choosenChildrenIndex)->choseCrossoverPart();

		break;
	case SIN[0]:
	case COS[0]:

		if (v_children.at(0)->nodeType != OPERATORTYPE)
			pp_choosenPart = &(v_children.at(0));
		else
			pp_choosenPart = v_children.at(0)->choseCrossoverPart();

		break;
	default:
		cout << "Error8"; //toTest
	}

	return pp_choosenPart;
}
