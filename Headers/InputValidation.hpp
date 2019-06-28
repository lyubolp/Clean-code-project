
#pragma once
#include <string>
#include "StringManip.hpp"

inline bool isValidLineRectangle(std::string line)
{
    int xf = line.find("x=");
    int yf = line.find("y=");
    int wf = line.find("width=");
    int hf = line.find("height=");
    int cf = line.find("fill=");


    return !(xf == -1 || yf == -1 || wf == -1 || hf == -1 || cf == -1);
}

inline bool isValidLineCircle(std::string line)
{
    int xf = line.find("cx=");
    int yf = line.find("cy=");
    int rf = line.find("r=");
    int cf = line.find("fill=");

    return !(xf == -1 || yf == -1 || rf == -1 || cf == -1);
}

inline bool isValidLineLine(std::string line)
{
    int x1f = line.find("x1=");
    int y1f = line.find("y1=");
    int x2f = line.find("x2=");
    int y2f = line.find("y2=");

    int cf = line.find("fill=");

    return  !(x1f == -1 || y1f == -1 || x2f == -1 || y2f == -1 || cf == -1);
}



inline bool isColorStringValid(const std::string colorToCheck)
{
	if (colorToCheck[0] != '#') return false;
	if (colorToCheck.length() != 7) return false;

	bool isNumber = false, isCapitalLetter = false, isLowerLetter = false;

	for (int i = 1; i < 7; i++)
	{
		if (0 <= ((colorToCheck[i] - '0')) && ((colorToCheck[i] - '0') <= 9))
		{
			isNumber = true;
		}
		else if ((0 <= (colorToCheck[i] - 'A')) && ((colorToCheck[i] - 'A') <= 25))
		{
			isCapitalLetter = true;
		}
		else if ((0 <= (colorToCheck[i] - 'a')) && ((colorToCheck[i] - 'a') <= 25))
		{
			isLowerLetter = true;
		}

		if(!(isNumber || isCapitalLetter || isLowerLetter))
        {
		    return false;
        }
	}

	return true;
}
