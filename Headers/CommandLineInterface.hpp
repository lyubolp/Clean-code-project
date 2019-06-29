//
// Created by lyubo on 04.05.19.
//
#pragma once
#ifndef CLEAN_CODE_PROJECT_COMMANDLINEINTERFACE_HPP
#define CLEAN_CODE_PROJECT_COMMANDLINEINTERFACE_HPP

#include <string>
#include "Headers/Rectangle.hpp"
#include "Headers/Circle.hpp"
#include "Headers/Line.hpp"
#include "Headers/SVGContainer.hpp"
#include "SVGFile.hpp"

class CommandLineInterface {
public:

    static CommandLineInterface& getInstance();

    bool exec(const std::string&);

private:

    CommandLineInterface();

    CommandLineInterface(const CommandLineInterface&) = delete;
    CommandLineInterface operator=(const CommandLineInterface&) = delete;

    bool execCreate(const std::string&);
    bool execSave(const std::string&) const;
    bool execSaveAs(const std::string&) const;
    bool execErase(const std::string&);
    bool execTranslate(const std::string&);
    bool execClose(const std::string&);
    bool execOpen(const std::string&);
    bool execPrint(const std::string&);

    std::pair<Point*, Point> generatePointsFromUserInput(std::string&, const shape&) const;

    Rectangle* createRectangleFromUserInput(const std::string&) const;
    Circle* createCircleFromUserInput(const std::string&) const;
    Line* createLineFromUserInput(const std::string&) const;

    void fillPointsFromUserInput(Point*, int&, std::string&) const;

    void createShape(const std::string&);

    void eraseShape(const std::string&);

    const double getValueFromCommand(std::string&, const std::string&);
    void translateShape(const std::string&);

    bool isFileOpen;
};


#endif //CLEAN_CODE_PROJECT_COMMANDLINEINTERFACE_HPP
