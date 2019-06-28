//
// Created by lyubo on 04.05.19.
//
#pragma once
#ifndef CLEAN_CODE_PROJECT_COMMANDLINEINTERFACE_HPP
#define CLEAN_CODE_PROJECT_COMMANDLINEINTERFACE_HPP

#include <string>
#include "Headers/Rectangle.hpp"
#include "Headers/Polygon.hpp"
#include "Headers/Circle.hpp"
#include "Headers/Line.hpp"
#include "Headers/SVGContainer.hpp"
#include "SVGFile.hpp"

class CommandLineInterface {
public:
    CommandLineInterface();

    bool exec(const std::string&);

private:
    Rectangle* createRectangleFromUserInput(const std::string&);
    Circle* createCircleFromUserInput(const std::string&);
    Line* createLineFromUserInput(const std::string&);
    Polygon* createPolygonFromUserInput(const std::string&);

    void fillPointsFromUserInput(point*, int&, std::string&);

    void createShape(const std::string&);

    void eraseShape(const std::string&);

    void translateShape(const std::string&);

    void openFromContainer(const std::vector <std::string>&);

    bool isFileOpen;
    SVGContainer shapes;
    SVGFile file;
};


#endif //CLEAN_CODE_PROJECT_COMMANDLINEINTERFACE_HPP
