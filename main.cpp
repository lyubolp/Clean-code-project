#include <iostream>
#include "Headers/InputParser.h"
#include "Headers/InputValidation.h"
#include "Headers/CommandLineInterface.h"
#include <string>
#include "Headers/Rectangle.h"
#include "Headers/StringManip.h"

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

/*TEST_CASE( "Tests are computed", "[tests]" )
{
    Tests for InputValidation.h

    REQUIRE(isValidLineRectangle("<rect x=\"10\" y=\"10\" width=\"10\" height=\"20\" fill=\"yellow\" />"));
    REQUIRE(isValidLineRectangle("<rect x=\"100\" y=\"60\" width=\"10\" height=\"10\" fill=\"red\" />"));
    REQUIRE(isValidLineRectangle("<rect x=\"5\" y=\"5\" width=\"10\" height=\"10\" fill=\"green\" />"));
    REQUIRE(isValidLineCircle("<circle cx=\"5\" cy=\"5\" r=\"10\" fill=\"blue\" /> "));
    REQUIRE(isValidLineCircle("<circle cx=\"20\" cy=\"20\" r=\"10\" fill=\"red\" />"));
    REQUIRE(isValidLineLine("<line x1=\"20\" y1=\"20\" x2=\"30\" y2=\"30\" fill=\"blue\" />"));
    REQUIRE(isValidLineLine("<line x1=\"0\" y1=\"0\" x2=\"200\" y2=\"200\" fill=\"blue\" />"));
    REQUIRE(isColorStringValid("#FF22AA"));
}*/
/*TEST_CASE( "Tests are computed", "[tests]" ) {

    //Tests for StringManip.h

    REQUIRE(strcmp(removeChar("Hello world!", 'l').data(), "Heo word!") == 0);
    REQUIRE(strcmp(removeBrackets("<Hello world!/>").data(), "Hello world!") == 0);
    REQUIRE(strcmp(removeBlankSpaces("Hello world!").data(), "Helloworld!") == 0);
    REQUIRE(strcmp(replaceAll("Hello world!", 'l', 'o').data(), "Heooo worod!") == 0);

    std::string temp = "123/123/123";
    REQUIRE(cutFirstNumberFromStringAsDouble(temp, '/') == 123);
    REQUIRE(strcmp(temp.data(), "123/123") == 0);

    temp = "/123/123/123";
    REQUIRE(cutFirstNumberFromStringAsDouble(temp, '/') == 123);
    REQUIRE(strcmp(temp.data(), "123/123") == 0);


    temp = "Hello_world";
    REQUIRE(strcmp(cutFirstSubstringFromString(temp, '_').data(), "Hello") == 0);
    REQUIRE(strcmp(temp.data(), "world") == 0);


    temp = "_Hello_world";
    REQUIRE(strcmp(cutFirstSubstringFromString(temp, '_').data(), "Hello") == 0);
    REQUIRE(strcmp(temp.data(), "world") == 0);

    REQUIRE(strcmp(removeFirstSubstringFromString("Not_Hello world", '_').data(), "_Hello world") == 0);

    temp = "Hello not world";
    REQUIRE(strcmp(removeWordFromString("not", temp).data(), "Hello  world") == 0);

    REQUIRE(countChar("qweasdzxcqwe", 'q') == 2);

    REQUIRE(strcmp(concatenateTwoStrings("Hello" ,"world").data(), "Helloworld") == 0);
}*/

/*TEST_CASE( "Test for InputParser.h", "[tests]" )
{
    const std::string inputs[9]=
            {
                    "<rect x=\"10\" y=\"10\" width=\"10\" height=\"20\" fill=\"yellow\" />",
                    "<rect x=\"100\" y=\"60\" width=\"10\" height=\"10\" fill=\"red\" />",
                    "<rect x=\"5\" y=\"5\" width=\"10\" height=\"10\" fill=\"green\" />",
                    "<circle cx=\"20\" cy=\"20\" r=\"10\" fill=\"red\" />",
                    "<line x1=\"20\" y1=\"20\" x2=\"30\" y2=\"30\" fill=\"blue\" />",
                    "<polygon points=\"20,20 30,30 40,40\" fill=\"cyan\"/>",
                    "<circle cx=\"5\" cy=\"5\" r=\"10\" fill=\"blue\" />",
                    "<line x1=\"0\" y1=\"0\" x2=\"200\" y2=\"200\" fill=\"blue\" />",
                    "<polygon points=\"200,10 250,190 160,210\" fill=\"blue\"/>"
            };
    const std::string outputs[9]=
            {
                "create rectangle 10.000000 10.000000 10.000000 20.000000 yellow",
                "create rectangle 100.000000 60.000000 10.000000 10.000000 red",
                "create rectangle 5.000000 5.000000 10.000000 10.000000 green",
                "create circle 20.000000 20.000000 10.000000 red",
                "create line 20.000000 20.000000 30.000000 30.000000 blue",
                "create polygon 20 20 30 30 40 40 cyan",
                "create circle 5.000000 5.000000 10.000000 blue",
                "create line 0.000000 0.000000 200.000000 200.000000 blue",
                "create polygon 200 10 250 190 160 210 blue"
            };
    REQUIRE(strcmp(convertLineFromFileToCommandRectangle(inputs[0]).data(), outputs[0].data()) == 0);
    REQUIRE(strcmp(convertLineFromFileToCommandRectangle(inputs[1]).data(), outputs[1].data()) == 0);
    REQUIRE(strcmp(convertLineFromFileToCommandRectangle(inputs[2]).data(), outputs[2].data()) == 0);
    REQUIRE(strcmp(convertLineFromFileToCommandCircle(inputs[3]).data(), outputs[3].data()) == 0);
    REQUIRE(strcmp(convertLineFromFileToCommandLine(inputs[4]).data(), outputs[4].data()) == 0);
    REQUIRE(strcmp(convertLineFromFileToCommandPolygon(inputs[5]).data(), outputs[5].data()) == 0);
    REQUIRE(strcmp(convertLineFromFileToCommandCircle(inputs[6]).data(), outputs[6].data()) == 0);
    REQUIRE(strcmp(convertLineFromFileToCommandLine(inputs[7]).data(), outputs[7].data()) == 0);
    REQUIRE(strcmp(convertLineFromFileToCommandPolygon(inputs[8]).data(), outputs[8].data()) == 0);
}*/

TEST_CASE( "Test for InputParser.h", "[tests]" )
{
    const std::string inputs[9]=
            {
                    "<rect x=\"10\" y=\"10\" width=\"10\" height=\"20\" fill=\"yellow\" />",
                    "<rect x=\"100\" y=\"60\" width=\"10\" height=\"10\" fill=\"red\" />",
                    "<rect x=\"5\" y=\"5\" width=\"10\" height=\"10\" fill=\"green\" />",
                    "<circle cx=\"20\" cy=\"20\" r=\"10\" fill=\"red\" />",
                    "<line x1=\"20\" y1=\"20\" x2=\"30\" y2=\"30\" fill=\"blue\" />",
                    "<polygon points=\"20,20 30,30 40,40\" fill=\"cyan\"/>",
                    "<circle cx=\"5\" cy=\"5\" r=\"10\" fill=\"blue\" />",
                    "<line x1=\"0\" y1=\"0\" x2=\"200\" y2=\"200\" fill=\"blue\" />",
                    "<polygon points=\"200,10 250,190 160,210\" fill=\"blue\"/>"
            };
    const std::string outputs[9]=
            {
                    "create rectangle 10.000000 10.000000 10.000000 20.000000 yellow",
                    "create rectangle 100.000000 60.000000 10.000000 10.000000 red",
                    "create rectangle 5.000000 5.000000 10.000000 10.000000 green",
                    "create circle 20.000000 20.000000 10.000000 red",
                    "create line 20.000000 20.000000 30.000000 30.000000 blue",
                    "create polygon 20 20 30 30 40 40 cyan",
                    "create circle 5.000000 5.000000 10.000000 blue",
                    "create line 0.000000 0.000000 200.000000 200.000000 blue",
                    "create polygon 200 10 250 190 160 210 blue"
            };
    REQUIRE(strcmp(convertLineFromFileToCommandRectangle(inputs[0]).data(), outputs[0].data()) == 0);
    REQUIRE(strcmp(convertLineFromFileToCommandRectangle(inputs[1]).data(), outputs[1].data()) == 0);
    REQUIRE(strcmp(convertLineFromFileToCommandRectangle(inputs[2]).data(), outputs[2].data()) == 0);
    REQUIRE(strcmp(convertLineFromFileToCommandCircle(inputs[3]).data(), outputs[3].data()) == 0);
    REQUIRE(strcmp(convertLineFromFileToCommandLine(inputs[4]).data(), outputs[4].data()) == 0);
    REQUIRE(strcmp(convertLineFromFileToCommandPolygon(inputs[5]).data(), outputs[5].data()) == 0);
    REQUIRE(strcmp(convertLineFromFileToCommandCircle(inputs[6]).data(), outputs[6].data()) == 0);
    REQUIRE(strcmp(convertLineFromFileToCommandLine(inputs[7]).data(), outputs[7].data()) == 0);
    REQUIRE(strcmp(convertLineFromFileToCommandPolygon(inputs[8]).data(), outputs[8].data()) == 0);
}
int main()
{
    //cmd.exec("open sample.svg");

    int result = Catch::Session().run();

    return result;
}