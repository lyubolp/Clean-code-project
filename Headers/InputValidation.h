
#pragma once
#include <string>

inline bool isValidLineRectangle(std::string line)
{
    int xf = line.find("x=");
    int yf = line.find("y=");
    int wf = line.find("width=");
    int hf = line.find("height=");
    int cf = line.find("fill=");

    return (xf == -1 || yf == -1 || wf == -1 || hf == -1 || cf == -1);
}

inline bool isValidLineCircle(std::string line)
{
    int xf = line.find("cx=");
    int yf = line.find("cy=");
    int rf = line.find("r=");
    int cf = line.find("fill=");

    return (xf == -1 || yf == -1 || rf == -1 || cf == -1);
}

inline bool isValidLineLine(std::string line)
{
    int x1f = line.find("x1=");
    int y1f = line.find("y1=");
    int x2f = line.find("x2=");
    int y2f = line.find("y2=");

    int cf = line.find("fill=");

    return  (x1f == -1 || y1f == -1 || x2f == -1 || y2f == -1 || cf == -1);
}


inline bool isNumberBiggerThanZero(const int numberToCheck)
{
	return numberToCheck > 0;
}
inline bool isNumberBiggerThanZero(const double numberToCheck)
{
	return numberToCheck > 0;
}

inline bool isColorStringValid(const std::string colorToCheck)
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
