#include "UsefullMethods.h"


bool UsefullMethods::ifOccur(int chance)
{
	return (UsefullMethods::randomNumber(100) <= chance) ? true : false;
}

int UsefullMethods::randomNumber(int bound)
{
	return rand() % bound + 1;
}

int UsefullMethods::randomNumberCloserToZero(int bound)
{
	int randomNumber;

	int randomTo100 = rand() % 100 + 1;
	if (randomTo100 < 20)
	{
		randomNumber = rand() % (bound/10) + 1;
	}
	else if (randomTo100 < 40)
	{
		randomNumber = rand() % (bound/8) + 1;

	}
	else if (randomTo100 < 50)
	{
		randomNumber = rand() % (bound/6) + 1;

	}
	else if (randomTo100 < 60)
	{
		randomNumber = rand() % (bound / 4) + 1;

	}
	else if (randomTo100 < 70)
	{
		randomNumber = rand() % (bound / 2) + 1;

	}
	else
	{
		randomNumber = rand() % bound + 1;

	}

	return randomNumber;
}