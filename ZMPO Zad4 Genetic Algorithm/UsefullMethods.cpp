#include "UsefullMethods.h"


bool UsefullMethods::ifOccur(int chance)
{
	return (UsefullMethods::randomNumber(100) <= chance) ? true : false;
}

int UsefullMethods::randomNumber(int bound)
{
	return rand() % bound + 1;
}
	