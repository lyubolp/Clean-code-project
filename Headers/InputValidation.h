
#pragma once
#include <string>

inline bool isValidLineRectangle(std::string line)
{
    int xf, yf, wf, hf, cf; //We make sure the line has all attributes

    xf = line.find("x=");
    yf = line.find("y=");
    wf = line.find("width=");
    hf = line.find("height=");
    cf = line.find("fill=");

    return (xf == -1 || yf == -1 || wf == -1 || hf == -1 || cf == -1);
}

inline bool isValidLineCircle(std::string line)
{
    int xf, yf, rf, cf;

    xf = line.find("cx=");
    yf = line.find("cy=");
    rf = line.find("r=");
    cf = line.find("fill=");

    return (xf == -1 || yf == -1 || rf == -1 || cf == -1);
}

inline bool isValidLineLine(std::string line)
{
    int x1f, y1f, x2f, y2f, cf;

    x1f = line.find("x1=");
    y1f = line.find("y1=");
    x2f = line.find("x2=");
    y2f = line.find("y2=");

    cf = line.find("fill=");

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
