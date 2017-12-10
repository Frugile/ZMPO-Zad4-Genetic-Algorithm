#include "UserInterface.h"

void UserInterface::startInterface(CTree **p_tree)
{
	bool again = true;
	string command;

	bool errorOccure = false;
	bool* p_errorOccur = &errorOccure;
	//bool* p_errorOccur = new bool;
	//*p_errorOccur = false;



	//TESTING CODE:
	if (isTest)
	{
		switch (commandCounter)
		{
		case 0:
			command = "enter + * sin x sin x * cos x cos x";
			break;
		case 1:
			command = "print";
			break;
		case 2:
			command = "vars";
			break;
		case 3:
			command = "join + 12 34";
			break;
		default:
			isTest = false;;
			getline(cin, command);
		}
		cout << command << endl;
		commandCounter++;
	}
	else
	{
		getline(cin, command);

	}
	//TESTING CODE END

	//getline(cin, command); //orginal part of code - commented to do tests



	int endMark = command.find(' ');

	if (endMark > 0)
	{
		string type = command.substr(0, endMark); //getting bare comand

		string *p_expression = new string();
		*p_expression = command.substr(endMark + 1, command.length());

		if (type == COMMAND1)//"enter"
		{
			//cout << ">			Wyrazenie to: \"" << *p_expression << "\"" << endl; //toTest	
			delete *p_tree;
			*p_tree = new CTree(p_errorOccur, p_expression);
			if (*p_errorOccur)
			{
				cout << ERROR_TEXT_BAD_EXPRESSION << endl;
				cout << (*p_tree)->toString() << endl;
			}
		}

		if (type == COMMAND4)//"comp"
		{
			double gotValue = (*p_tree)->getValue(p_errorOccur, p_expression);
			if (*p_errorOccur)
				cout << ERROR_TEXT_BAD_NUMBER_OF_VAR << endl;
			else
				cout << gotValue << endl;
		}
		if (type == COMMAND5)//"join"
		{
			(*p_tree)->join(p_errorOccur, p_expression);
			cout << (*p_tree)->toString() << endl;
		}
		delete p_expression;
	} //if (endMark > 0)
	else
	{
		if (command == COMMAND4)//"comp"
		{
			double gotValue = (*p_tree)->getValue(p_errorOccur, nullptr);
			if (*p_errorOccur)
				cout << ERROR_TEXT_BAD_NUMBER_OF_VAR << endl;
			else
				cout << gotValue << endl;
		}
		else if (command == COMMAND2)//"vars"
		{
			cout << (*p_tree)->getVarsString() << endl;
		}
		else if (command == COMMAND3)//"print"
		{
			cout << (*p_tree)->toString() << endl;
		}
		else if (command == COMMAND6)//"end"
			again = false;
		else
			cout << ERROR_BADCOMMAND;
	} // if (endMark > 0) else

	  //delete p_errorOccur;
	if (again)
	{
		startInterface(p_tree);
	}
}

