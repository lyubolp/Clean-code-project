cmake_minimum_required(VERSION 3.14)
project(Clean_code_project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Clean_code_project
        Base.cpp
        Headers/Base.hpp
        Circle.cpp
        Headers/Circle.hpp
        Headers/DynamicMemoryManagment.hpp
        Headers/InputValidation.hpp
        Line.cpp
        Headers/Line.hpp
        main.cpp
        Polygon.cpp
        Headers/Polygon.hpp
        Rectangle.cpp
        Headers/Rectangle.hpp
        Headers/StringManip.hpp
        SVGContainer.cpp
        Headers/SVGContainer.hpp
        SVGFile.cpp
        Headers/SVGFile.hpp
        CommandLineInterface.cpp
        Headers/CommandLineInterface.hpp
        Headers/MathFunctions.hpp Headers/InputParser.hpp Headers/Point.cpp Headers/Point.hpp)
