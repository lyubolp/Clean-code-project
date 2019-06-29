#include <iostream>
#include "Headers/InputParser.hpp"
#include "Headers/InputValidation.hpp"
#include "Headers/CommandLineInterface.hpp"
#include <string>
#include <fcntl.h>
#include "Headers/Rectangle.hpp"
#include "Headers/StringManip.hpp"

//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"


int main()
{

    std::string userInput;

    while(userInput.compare("exit") != 0)
    {
        std::cout << "Please enter a command (type man for manual)... ";
        getline(std::cin, userInput);
        CommandLineInterface::getInstance().exec(userInput);
    }

    return 0;
}