#pragma once
#include "SVGContainer.h"
#include <string>
#include <fstream>
#include "Base.h"

const std::string firstLine = "<?xml version=\"1.0\" standalone=\"no\"?>";
const std::string secondLine = "<!DOCTYPE svg PUBLIC \" - //W3C//DTD SVG 1.1//EN\" \" http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd \"> ";
const std::string tags[7] = { "<svg>", "<rect", "<circle", "<line", "<polygon" , "/>", "</svg>"};

class SVGFile : public SVGContainer
{
private:
	std::string filePath;
	std::ifstream fileStream;
	std::ofstream fileWrite;
	std::vector<std::string> parsedLines;
public:
	SVGFile();
	int openFile(const std::string); //TO BE REFACTORED
	int saveFile(const SVGContainer&); //TO BE REFACTORED
	int saveAsFile(const std::string, const SVGContainer&);
	int closeFile();

	std::string getFileName() const;
	
	std::vector<std::string> loadIntoContainer() const;
};