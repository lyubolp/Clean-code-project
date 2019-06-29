//
// Created by lyubo on 29.06.19.
//

#ifndef CLEAN_CODE_PROJECT_UNITTESTS_H
#define CLEAN_CODE_PROJECT_UNITTESTS_H


TEST_CASE( "Test for the whole project", "[tests]" )
{
std::fstream file;
file.open("UnitTestLog.log", std::ios::out);
std::string line;

// Backup streambuffers of  cout
std::streambuf* stream_buffer_cout = std::cout.rdbuf();

// Get the streambuffer of the file
std::streambuf* stream_buffer_file = file.rdbuf();

// Redirect cout to file
std::cout.rdbuf(stream_buffer_file);


std::cout << "Opening file...\n";
CommandLineInterface::getInstance().exec("open sample.svg");

std::cout << "  \tPrinting all shapes...\n";
CommandLineInterface::getInstance().exec("print");

std::cout << "  \t Creating a rectangle and printing all shapes again...\n";
CommandLineInterface::getInstance().exec("create rectangle 3 3 1 1 #3399ff");
CommandLineInterface::getInstance().exec("print");


std::cout << "  \t Creating some more shapes and printing all...\n";
CommandLineInterface::getInstance().exec("create rectangle 4 5 2 2 #3399ff");
CommandLineInterface::getInstance().exec("create rectangle 7 3 1 1 #3399ff");
CommandLineInterface::getInstance().exec("create circle 4 5 5 #3399ff");
CommandLineInterface::getInstance().exec("create line 4 5 2 2 #3399ff");
CommandLineInterface::getInstance().exec("create circle 5 2 2 #3399ff");
CommandLineInterface::getInstance().exec("print");


std::cout << "  \t Time to erase the new ones... \n";
CommandLineInterface::getInstance().exec("erase 6");
CommandLineInterface::getInstance().exec("erase 6");
CommandLineInterface::getInstance().exec("erase 1");
CommandLineInterface::getInstance().exec("erase 6");
CommandLineInterface::getInstance().exec("erase 5");
CommandLineInterface::getInstance().exec("erase 3");

CommandLineInterface::getInstance().exec("print");

std::cout << "  \t Testing the translate feature... \n";
CommandLineInterface::getInstance().exec("translate \"2\" vertical=\"20\" horizontal=\"20\"");
CommandLineInterface::getInstance().exec("translate vertical=\"10\" horizontal=\"10\"");
CommandLineInterface::getInstance().exec("print");

std::cout << "  \t Testing the save feature... \n";
CommandLineInterface::getInstance().exec("save");

CommandLineInterface::getInstance().exec("saveas sample3.svg");
CommandLineInterface::getInstance().exec("close");

std::cout.rdbuf(stream_buffer_cout);


file.close();

file.open("UnitTestLog.log", std::ios::in);

std::vector<std::string> inputs;
std::string temp("Invalid line");
while (getline(file, temp)) //We get each line and check the tag name
{
inputs.push_back(temp);
}
const int OUTPUTS_SIZE = 41;
std::string outputs[OUTPUTS_SIZE] = {"Opening file...",
                                     "File opened successfully",
                                     "  \tPrinting all shapes...",
                                     "1. circle 65 62 2 #3399ff",
                                     "2. circle 55 52 2 #3399ff",
                                     "3. circle 25 22 2 #3399ff",
                                     "4. line 14 15 12 12 #3399ff",
                                     "5. circle 15 12 2 #3399ff",
                                     "  \t Creating a rectangle and printing all shapes again...",
                                     "1. circle 65 62 2 #3399ff",
                                     "2. circle 55 52 2 #3399ff",
                                     "3. circle 25 22 2 #3399ff",
                                     "4. line 14 15 12 12 #3399ff",
                                     "5. circle 15 12 2 #3399ff",
                                     "6. rectangle 3 3 1 1 #3399ff",
                                     "  \t Creating some more shapes and printing all...",
                                     "1. circle 65 62 2 #3399ff",
                                     "2. circle 55 52 2 #3399ff",
                                     "3. circle 25 22 2 #3399ff",
                                     "4. line 14 15 12 12 #3399ff",
                                     "5. circle 15 12 2 #3399ff",
                                     "6. rectangle 3 3 1 1 #3399ff",
                                     "7. rectangle 4 5 2 2 #3399ff",
                                     "8. rectangle 7 3 1 1 #3399ff",
                                     "9. circle 4 5 5 #3399ff",
                                     "10. line 4 5 2 2 #3399ff",
                                     "11. circle 5 2 2 #3399ff",
                                     "  \t Time to erase the new ones... ",
                                     "1. circle 55 52 2 #3399ff",
                                     "2. circle 25 22 2 #3399ff",
                                     "3. circle 15 12 2 #3399ff",
                                     "4. line 4 5 2 2 #3399ff",
                                     "5. circle 5 2 2 #3399ff",
                                     "  \t Testing the translate feature... ",
                                     "1. circle 65 62 2 #3399ff",
                                     "2. circle 55 52 2 #3399ff",
                                     "3. circle 25 22 2 #3399ff",
                                     "4. line 14 15 12 12 #3399ff",
                                     "5. circle 15 12 2 #3399ff",
                                     "  \t Testing the save feature... ",
                                     " sample3.svg File has been closed successfully"};

REQUIRE(inputs.size() == OUTPUTS_SIZE);
for(int i = 0; i < OUTPUTS_SIZE; i++)
{
REQUIRE(strcmp(inputs[i].data(), outputs[i].data()) == 0);
}

}
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

/*TEST_CASE( "Test for MathFunctions.h", "[tests]" )
{
    REQUIRE(checkIfDoubleIsInInterval(5.4, {5.3, 5.5}) == 1);
    REQUIRE(checkIfDoubleIsInInterval(5.4, {5.45, 5.5}) == 0);
    REQUIRE(checkIfDoubleIsInInterval(5.4, {5.4, 5.4})== 1);

    REQUIRE(getDistanceBetweenTwoPoints(point(0,1), point(3,5)) == 5);
    REQUIRE(getDistanceBetweenTwoPoints(point(0,1), point(1,2)) == sqrt(2));
}*/

#endif //CLEAN_CODE_PROJECT_UNITTESTS_H
