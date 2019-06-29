#pragma once

#include "Headers/SVGContainer.hpp"
#include "Headers/StringManip.hpp"
#include "Headers/InputValidation.hpp"
#include <string>
#include <fstream>
#include "Headers/Base.hpp"
#include "Headers/InputParser.hpp"


class SVGFile
{
public:

    static SVGFile& getInstance();

	const int openFile(const std::string &);

	int saveFile(const SVGContainer&);
	int saveAsFile(const std::string&, const SVGContainer&);

	int closeFile();

	std::string getFileName() const;
	
	std::vector<std::string> loadIntoContainer() const;

private:
    SVGFile();

    SVGFile(const SVGFile&) = delete;
    SVGFile operator=(const SVGFile&) = delete;

    std::string filePath;
    std::ifstream fileStream;
    std::ofstream fileWrite;
    std::vector<std::string> parsedLines;

    void addFirstTagsToFile();
    void addLineToFile(std::string);
    void convertLineFromFileToCommand(std::string&);
    void convertObjectToLine(const BaseShape*);
};