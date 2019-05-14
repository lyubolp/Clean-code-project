cmake_minimum_required(VERSION 3.14)
project(Clean_code_project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Clean_code_project
        Base.cpp
        Headers/Base.h
        Circle.cpp
        Headers/Circle.h
        Headers/DynamicMemoryManagment.h
        Headers/InputValidation.h
        Line.cpp
        Headers/Line.h
        main.cpp
        Polygon.cpp
        Headers/Polygon.h
        Rectangle.cpp
        Headers/Rectangle.h
        Headers/StringManip.h
        SVGContainer.cpp
        Headers/SVGContainer.h
        SVGFile.cpp
        Headers/SVGFile.h
        CommandLineInterface.cpp
        Headers/CommandLineInterface.h
        Headers/MathFunctions.h Headers/InputParser.h)
