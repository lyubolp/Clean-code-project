#include <iostream>
#include <string>

std::string removeChar(const std::string userInput, const char charToRemove)
{
	std::string result = userInput;

	int lengthOfResult = result.length();

	for (int i = 0; i < lengthOfResult; i++)
	{
		if (result[i] == charToRemove)
		{
			result.erase(i, 1);
			lengthOfResult--;
		}
	}
	return result;
}

std::string removeBrackets(const std::string userInput)
{
	std::string result = userInput;

	int lengthOfResult = result.length();

	for (int i = 0; i < lengthOfResult; i++)
	{
		if (result[i] == '>' || result[i] == '<' || result[i] == '/')
		{
			result.erase(i, 1);
			lengthOfResult = result.length();
		}
	}
	return result;
}

std::string removeBlankSpaces(const std::string userInput)
{
	std::string result = userInput;

	result = removeChar(result, ' ');
	result = removeChar(result, 32);
	result = removeChar(result, '\t');

	return result;
}

std::string replaceAll(const std::string input, const char replaced, const char with)
{
	std::string result = input;
	int lengthOfResult = result.size();
	for (int i = 0; i < lengthOfResult; i++)
	{
		if (result[i] == replaced)
		{
			result[i] = with;
			lengthOfResult--;
		}
	}
	return result;
}

double cutFirstNumberFromStringAsDouble(std::string& input, std::string delimiter)
{
	int indexOfFirstSpace;

	double result;
	indexOfFirstSpace = input.find(delimiter);
	result = std::stod(input.substr(0, indexOfFirstSpace));
	input = input.substr(indexOfFirstSpace + 1);

	return result;
}

std::string cutFirstSubstringFromString(std::string& input, std::string delimiter)
{
	int indexOfFirstSpace;

	std::string result;
	indexOfFirstSpace = input.find(delimiter);
	result = input.substr(0, indexOfFirstSpace);
	input = input.substr(indexOfFirstSpace + 1);

	return result;
}

std::string removeFirstSubstringFromString(std::string input, std::string delimiter)
{
	int indexOfFirstSpace;

	std::string result;
	indexOfFirstSpace = input.find(delimiter);
	result = input.substr(indexOfFirstSpace + 1);

	return result;
}
std::string removeWordFromString(std::string wordToRemove, std::string input)
{
	int indexOfWordToRemove = input.find(input);
	int lengthOfWordToRemove = wordToRemove.length();
	std::string result = input.substr(indexOfWordToRemove + lengthOfWordToRemove);

	return result;
}

int cutFirstNumberFromStringAsInt(std::string& input, std::string delimiter)
{
	int indexOfFirstSpace;

	int result;
	indexOfFirstSpace = input.find(delimiter);
	result = std::stoi(input.substr(0, indexOfFirstSpace));
	input = input.substr(indexOfFirstSpace + 1);

	return result;
}

int countChar(const std::string userInput, const char searched)
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

std::string concatenateTwoStrings(std::string first, std::string second)
{
	std::string result;

	result.append(first);
	result.append(second);

	return result;
}