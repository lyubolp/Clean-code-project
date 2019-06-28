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
	std::cout << " <polygon> := create polygon <point1> <point2> ... <pointN> <color>\n\n";
	std::cout << "erase - erase a figure, by id: erase 2\n";
	std::cout << "translates - translates all or one figure:\n translate vertical=10 horizontal=100 \n translate 1 vertical=20 horizontal=200\n \n";
	std::cout << "within - checks if all figures are withing a rectangle or a circle: \n\ within rectangle <x> <y> <w> <h>, within circle <x> <y> <r>\n\n";
}

CommandLineInterface cmd;



int main()
{

    std::cout << "Opening file...\n";
    cmd.exec("open sample.svg");

    std::cout << "\n \n \tPrinting all shapes...\n";
    cmd.exec("print");

    std::cout << "\n \n \t Creating a rectangle and printing all shapes again...\n";
    cmd.exec("create rectangle 3 3 1 1 #3399ff");
    cmd.exec("print");


    std::cout << "\n \n \t Creating some more shapes and printing all...\n";
    cmd.exec("create rectangle 4 5 2 2 #3399ff");
    cmd.exec("create rectangle 7 3 1 1 #3399ff");
    cmd.exec("create circle 4 5 5 #3399ff");
    cmd.exec("create line 4 5 2 2 #3399ff");
    cmd.exec("create circle 5 2 2 #3399ff");
    cmd.exec("print");


    std::cout << "\n \n \t Time to erase the new ones... \n";
    cmd.exec("erase 6");
    cmd.exec("erase 6");
    cmd.exec("erase 1");
    cmd.exec("erase 6");
    cmd.exec("erase 5");
    cmd.exec("print");

    std::cout << "\n \n \t Testing the translate feature... \n";
    cmd.exec("translate \"2\" vertical=\"20\" horizontal=\"20\"");
    cmd.exec("translate vertical=\"10\" horizontal=\"10\"");
    cmd.exec("print");

    std::cout << "\n \n \t Testing the save feature... \n";
    cmd.exec("save");

    cmd.exec("saveas sample3.svg");
    cmd.exec("close");


    //int result = Catch::Session().run();

    return 0;
}