#pragma once

#include <iomanip>

using namespace std;

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__) //to check Memory Leaks

class UsefullMethods
{
public:
	static int randomNumber(int bound);
	static int randomNumberCloserToZero(int bound);
	static bool ifOccur(int chance);
};
