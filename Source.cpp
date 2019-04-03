#include <iostream>
#include "Polygon.h"
#include "Line.h"
#include "Rectangle.h"
#include "Circle.h"
#include "SVGContainer.h"
#include "SVGFile.h"

SVGContainer svgc; //Main container
SVGFile svgf; //Main file reader
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

void menu()
{
	bool exit = false; //IF the program should exit, or should the menu again
	std::string command; //The command
	std::cout << "Please enter command or type in \"man\" to view available commands \n";

	std::getline(std::cin, command);

	if (command.find("open") != -1)
	{
		if (!openedFile)
		{
			if (svgf.openFile(command) == 1)
			{
				std::cout << "Successfully opened " << svgf.getFileName() << "\n";
				svgc.openFromContainer(svgf.loadIntoContainer()); //We open a file
				openedFile = true;
			}
			else
			{
				std::cout << "Error openning file \n";
			}

		}
		else
		{
			std::cout << "There is an open file at the moment, please close it.\n";
		}
	}
	else if (command.find("close") != -1)
	{
		if (openedFile)
		{
			svgf.closeFile();
			std::cout << "Successfully closed " << svgf.getFileName() << "\n";
			openedFile = false;
			//When we close a file, we reset the containers
			svgc = SVGContainer();
			svgf = SVGFile();
		}
		else
		{
			std::cout << "There is no open file at the moment, please open a file it.\n";
		}
	}
	else if (command.find("save") != -1)
	{
		if (command[4] == 'a')
		{
			if (openedFile)
			{
				svgf.saveAsFile(command, svgc); //Saving the file in a new location
				std::cout << "Successfully saved " << svgf.getFileName() << "\n";
			}
			else
			{
				std::cout << "There is no open file at the moment, please open a file it.\n";
			}
		}
		else
		{
			if (openedFile)
			{
				svgf.saveFile(svgc); //Saveing the file
				std::cout << "Successfully saved " << svgf.getFileName() << "\n";
			}
			else
			{
				std::cout << "There is no open file at the moment, please open a file it.\n";
			}
		}
	}
	else if (command.find("man") != -1)
	{
		man(); //Calls the manual
	}
	else if (command.find("exit") != -1)
	{
		exit = true; //We raise the exit flag
	}
	else if (command.find("print") != -1)
	{
		if (openedFile)
		{
			svgc.print(); //Print the figures
		}
		else
		{
			std::cout << "There is no open file at the moment, please open a file it.\n";
		}
	}
	else if (command.find("create") != -1)
	{
		if (openedFile)
		{
			svgc.create(command); //We create a figure
			std::cout << "Successfully created ";
			svgc.print(svgc.getCount() - 1);
			std::cout << "\n";
		}
		else
		{
			std::cout << "There is no open file at the moment, please open a file it.\n";
		}
	}
	else if (command.find("erase") != -1)
	{
		if (openedFile)
		{
			svgc.erase(command); //Erasing the figure
			std::cout << "Successfully erased " << command[6];
			std::cout << "\n";
		}
		else
		{
			std::cout << "There is no open file at the moment, please open a file it.\n";
		}
	}
	else if (command.find("translate") != -1)
	{
		if (openedFile)
		{
			svgc.translate(command); //Transleting the figures
			if (command[10] == 'v')
			{
				std::cout << "Successfully translated all figures ";
			}
			else
			{
				std::cout << "Successfully translated " << command[10];
			}
			std::cout << "\n";
		}
		else
		{
			std::cout << "There is no open file at the moment, please open a file it.\n";
		}

	}
	else if (command.find("within") != -1)
	{
		if (openedFile)
		{
			std::cout << "Figures within: \n";
			svgc.within(command); //Checking within

			std::cout << "\n";
		}
		else
		{
			std::cout << "There is no open file at the moment, please open a file it.\n";
		}
	}
	if (!exit) menu(); //If the exit flag is not raised, we call the menu again



}

int main()
{
	menu();
	return 0;
}