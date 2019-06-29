#include <iostream>
#include "Headers/InputParser.hpp"
#include "Headers/InputValidation.hpp"
#include "Headers/CommandLineInterface.hpp"
#include <string>
#include "Headers/Rectangle.hpp"
#include "Headers/StringManip.hpp"

//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

bool openedFile = false; //flag that shows if a file is already open

void man() //Shows user manual
{
	std::cout << "SVG project \n";
	std::cout << "Avaiable commands:\n";
	std::cout << "open - to open a file: open C:\\file.svg\n";
	std::cout << "close - to close the file: close\n";
	std::cout << "save - to save the current file: save\n";
	std::cout << "saveas - to save the file in a new place: saveas C:\\file.svg\n";
	std::cout << "exit - to exit the program: exit\n";
	std::cout << "print - prints all figures\n";
	std::cout << "create - creates a new figure:\n\n";
	std::cout << "create <figure> <points> <additionalPoints> <color>\n";
	std::cout << " <rectangle> := create rectangle <x> <y> <width> <height> <color>\n";
	std::cout << " <circle> := create circle <x> <y> <r> <color>\n";
	std::cout << " <line> := create line <x1> <y1> <x2> <y2> <color>\n";
	std::cout << "erase - erase a figure, by id: erase 2\n";
	std::cout << "translates - translates all or one figure:\n translate vertical=10 horizontal=100 \n translate 1 vertical=20 horizontal=200\n \n";
}


int main()
{
    std::string userInput;

    while(userInput.compare("exit") != 0)
    {
        std::cout << "Please enter a command (type man for manual)... \n";
        getline(std::cin, userInput);
    }

    return 0;
}