//
// Created by lyubo on 04.05.19.
//
#pragma once
#ifndef CLEAN_CODE_PROJECT_COMMANDLINEINTERFACE_H
#define CLEAN_CODE_PROJECT_COMMANDLINEINTERFACE_H

#include <string>
#include "Headers/Rectangle.h"
#include "Headers/Polygon.h"
#include "Headers/Circle.h"
#include "Headers/Line.h"
#include "Headers/SVGContainer.h"

class CommandLineInterface {
private:
    SVGContainer shapes;
    Rectangle* createRectangleFromUserInput(const std::string&);
    Circle* createCircleFromUserInput(const std::string&);
    Line* createLineFromUserInput(const std::string&);
    Polygon* createPolygonFromUserInput(const std::string&);

    void fillPointsFromUserInput(point*, int&, std::string&);

public:
    void createShape(const std::string&);
    void eraseShape(const std::string&);
    void translateShape(const std::string&);
    void figureWithingCommand(const std::string&);
    void openFromContainer(const std::vector <std::string>&);


};


#endif //CLEAN_CODE_PROJECT_COMMANDLINEINTERFACE_H
