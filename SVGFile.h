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

	void addFirstTagsToFile();
	void addLineToFile(std::string);

	bool isValidLineRectangle(std::string);
	bool isValidLineCircle(std::string);
	bool isValidLineLine(std::string);

	std::string convertLineFromFileToCommandRectangle(std::string);
	std::string convertLineFromFileToCommandCircle(std::string);
	std::string convertLineFromFileToCommandLine(std::string);
	std::string convertLineFromFileToCommandPolygon(std::string);

	std::string convertRectangleObjectToLine(const BaseShape*);
	std::string convertCircleObjectToLine(const BaseShape*);
	std::string convertLineObjectToLine(const BaseShape*);
	std::string convertPolygonObjectToLine(const BaseShape*);
	
public:
	SVGFile();
	int openFile(const std::string);
	int saveFile(const SVGContainer&);
	int saveAsFile(const std::string, const SVGContainer&);
	int closeFile();

	std::string getFileName() const;
	
	std::vector<std::string> loadIntoContainer() const;
};