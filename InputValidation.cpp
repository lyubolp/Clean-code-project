#include <string>
#include "Base.h"
#include <set>

bool isNumberBiggerThanZero(const int numberToCheck)
{
	return numberToCheck > 0;
}
bool isNumberBiggerThanZero(const double numberToCheck)
{
	return numberToCheck > 0;
}

bool isColorStringValid(const std::string colorToCheck)
{
	if (colorToCheck[0] != '#') return false;
	if (colorToCheck.length() != 7) return false;

	bool isNumber = true, isCapitalLetter = true, isLowerLetter = true;

	for (int i = 0; i < 7; i++)
	{
		if (((colorToCheck[i] - '0') < 0) || ((colorToCheck[i] - '0') > 9))
		{
			isNumber = false;
		}

		if (((colorToCheck[i] - 'A') < 0) || ((colorToCheck[i] - 'A') > 25))
		{
			isCapitalLetter = false;
		}

		if (((colorToCheck[i] - 'a') < 0) || ((colorToCheck[i] - 'a') > 25))
		{
			isLowerLetter = false;
		}
	}

	return (isNumber && isCapitalLetter && isLowerLetter);
}