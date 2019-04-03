#include "StringManip.h"

std::string removeChar(const std::string userInput, const char rc)
{
	std::string result = userInput;

	int s = result.length();

	for (int i = 0; i < s; i++)
	{
		if (result[i] == rc)
		{
			result.erase(i, 1);
			s--;
		}
	}
	return result;
}

std::string removeBrackets(const std::string userInput)
{
	std::string result = userInput;

	int s = result.length();

	for (int i = 0; i < s; i++)
	{
		if (result[i] == '>' || result[i] == '<' || result[i] == '/')
		{
			result.erase(i, 1);
			s = result.length();
		}
	}
	return result;
}

std::string removeBlankSpaces(const std::string rhs)
{
	std::string result = rhs;

	result = removeChar(result, ' ');
	result = removeChar(result, 32);
	result = removeChar(result, '\t');

	return result;
}

std::string replaceAll(const std::string input, const char replaced, const char with)
{
	std::string result = input;
	int s = result.size();
	for (int i = 0; i < s; i++)
	{
		if (result[i] == replaced)
		{
			result[i] = with;
			s--;
		}
	}
	return result;
}


int countChar(const std::string rhs, const char searched)
{
	int r = 0, s = rhs.length();
	for (int i = 0; i < s; i++)
	{
		if (rhs[i] == searched)
		{
			r++;
		}
	}
	return r;
}