#pragma once

#include "Headers/SVGContainer.h"
#include "Headers/StringManip.h"
#include "Headers/InputValidation.h"
#include <string>
#include <fstream>
#include "Headers/Base.h"
#include "Headers/InputParser.h"


class SVGFile
{
private:
	std::string filePath;
	std::ifstream fileStream;
	std::ofstream fileWrite;
	std::vector<std::string> parsedLines;

	void addFirstTagsToFile();
	void addLineToFile(std::string);
	void convertLineFromFileToCommand(std::string&);
	void convertObjectToLine(const BaseShape*);


public:
	SVGFile();
	const int openFile(const std::string &);
	int saveFile(const SVGContainer&);
	int saveAsFile(const std::string, const SVGContainer&);
	int closeFile();

	std::string getFileName() const;
	
	std::vector<std::string> loadIntoContainer() const;
};