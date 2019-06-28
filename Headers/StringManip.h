#ifndef CLEAN_CODE_PROJECT_STRINGMANIP_H
#define CLEAN_CODE_PROJECT_STRINGMANIP_H
#include <iostream>
#include <string>
#include <limits>

const std::string invalidDelimiter = "Invalid delimiter";
inline const int countChar(const std::string& userInput, const char searched)
{
    int amountOfChars = 0, s = userInput.length();
    for (int i = 0; i < s; i++)
    {
        if (userInput[i] == searched)
        {
            amountOfChars++;
        }
    }
    return amountOfChars;
}

inline const std::string removeChar(const std::string& userInput, const char charToRemove)
{
	std::string result = userInput;

	int lengthOfResult = result.length();

	for (int i = 0; i < lengthOfResult; i++)
	{
		if (result[i] == charToRemove)
		{
			result.erase(i, 1);
			i--;
			lengthOfResult--;
		}
	}
	return result;
}

inline const std::string removeBrackets(const std::string& userInput)
{
	std::string result = userInput;

	int lengthOfResult = result.length();

	for (int i = 0; i < lengthOfResult; i++)
	{
		if (result[i] == '>' || result[i] == '<' || result[i] == '/')
		{
			result.erase(i, 1);
			lengthOfResult = result.length();
			i--;
		}
	}
	return result;
}

inline const std::string removeBlankSpaces(const std::string& userInput)
{
	std::string result = userInput;

	result = removeChar(result, ' ');
	result = removeChar(result, 32);
	result = removeChar(result, '\t');

	return result;
}

inline const std::string replaceAll(const std::string& input, const char replaced, const char with)
{
	std::string result = input;
	int lengthOfResult = result.size();
	for (int i = 0; i < lengthOfResult; i++)
	{
		if (result[i] == replaced)
		{
			result[i] = with;
		}
	}
	return result;
}
inline const int findNthOccuranceOfChar(const std::string& input, const char& toFind, const int& n)
{
    int counter = 0;

    for(int i = 0; i < input.length(); i++)
    {
        if(input[i] == toFind)
        {
            counter++;
            if(counter == n)
            {
                return i;
            }
        }
    }
    return -1;
}
inline const double cutFirstNumberFromStringAsDouble(std::string& input, const char& delimiter)
{
	int indexOfFirstSpace = 0;
    int isFirstSymbolDelimitier = 0;
	double result = -1;

	if(input[0] == delimiter && countChar(input, delimiter) > 1)
    {
	    isFirstSymbolDelimitier = 1;
        indexOfFirstSpace = findNthOccuranceOfChar(input, delimiter, 2);
    }
	else
    {
        indexOfFirstSpace = findNthOccuranceOfChar(input, delimiter, 1);
    }


	if(indexOfFirstSpace == std::string::npos)
    {
	    std::cout << invalidDelimiter;
	    return std::numeric_limits<double>::min();
    }
	result = std::stod(input.substr(isFirstSymbolDelimitier, indexOfFirstSpace - isFirstSymbolDelimitier));
	input = input.substr(indexOfFirstSpace + 1);

	return result;
}

inline const std::string cutFirstSubstringFromString(std::string& input, const char& delimiter)
{
	int indexOfFirstSpace;
    int isFirstSymbolDelimitier = 0;
	std::string result;

    if(input[0] == delimiter)
    {
        isFirstSymbolDelimitier = 1;

        indexOfFirstSpace = findNthOccuranceOfChar(input, delimiter, 2);
    }
    else
    {
        indexOfFirstSpace = findNthOccuranceOfChar(input, delimiter, 1);
    }
    if(indexOfFirstSpace == std::string::npos)
    {
	    return invalidDelimiter;
    }
	result = input.substr(isFirstSymbolDelimitier, indexOfFirstSpace - isFirstSymbolDelimitier);
	input = input.substr(indexOfFirstSpace + 1);

	return result;
}

inline const std::string removeFirstSubstringFromString(const std::string& input, const char& delimiter)
{
	int indexOfFirstSpace;

	std::string result;
	indexOfFirstSpace = input.find(delimiter);
	result = input.substr(indexOfFirstSpace+1);

	return result;
}


inline const std::string concatenateTwoStrings(const std::string& first, const std::string& second)
{
    std::string result;

    result.append(first);
    result.append(second);

    return result;
}

inline const std::string removeWordFromString(const std::string& wordToRemove, const std::string& from)
{
	int indexOfWordToRemove = from.find(wordToRemove);
	int lengthOfWordToRemove = wordToRemove.length();
	std::string part1 = from.substr(0, indexOfWordToRemove);
	std::string part2 = from.substr(indexOfWordToRemove + lengthOfWordToRemove);
	std::string result = concatenateTwoStrings(part1, part2);

	return result;
}


inline const int cutFirstNumberFromStringAsInt(std::string& input, const char& delimiter)
{
	return (int)cutFirstNumberFromStringAsDouble(input, delimiter);
}



#endif