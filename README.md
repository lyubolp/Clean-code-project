# Documentation for SVG Project

## Project description

The goal of the project is to create a command line tool which manipulates SVG files. The tool can open, save and close SVG files, create and erase shapes and translate existing shapes.

## Classes

The project consists for the following classes:

- `Base` - abstract class, that represents a shape. It is used as a foundation for the other shapes.

  - `Circle` - represents a circle
  - `Line` - represents a line
  - `Rectangle` - represents an rectangle

- `Point` - represents a two-dimensional point through x and y coordinates

- `SVGContainer` - this class is where all the shapes are contained as objects. It supports the following operations:

  - Adding a shape
  - Printing a shape
  - Printing all shapes
  - Erasing a shape
  - Translating a shape
  - Access a shape

- `SVGFile` - this class represents the file operations that should be executed on an SVG file:

  - Open a file
  - Save the opened file
  - Save the SVG shapes as a new file
  - Load the file into the SVG container
  - Converting lines from the SVG file to commands to the main interface (see below)

- `CommandLineInterface` - the main interface of the application:

  - It has one main method for executing commands

  On top of that, it also has:

  - Methods that create the requested object based on special commands
  - Methods that call the erase or translate functions from the `SVGContainer` 

## Public methods 

### BaseShape (class)

- `BaseShape()` - constructor for BaseShape
- `BaseShape(const std::pair<const Point*, const int>& ,const std::string&, const shape&)` - constructor with parameters for BaseShape (sets the points of the shape, their amount, the color and the type of the shape)
- `BaseShape(const BaseShape&)` - copy  constructor
- `BaseShape& operator=(const BaseShape&)` - operator= for the class
- `virtual ~BaseShape()` - destructor
- `const shape getType() const` - returns the shape type (shape type is an enum with the following values - `DEFAULT`, `RECTANGLE`, `CIRCLE`, `LINE`)
- `const std::string getColor() const` - return the color of the shape (supported colors are hex colors only)
- `const Point * getPoints() const` - returns a pointer to the shape's points
- `const int getPointsCount() const` - returns the amount of points the shape has
- `virtual const Point getAdditionalPoints() const = 0` - virtual methods that get points that are not defined in `BaseShape`(Rectangle: (width/height), Circle (radius,0), Line(x,y) at the end of it)
- `void translate(const int&, const int&)` - translates the shape horizontally and vertically
- `virtual void print() const = 0`  - prints all available information of the shape

### Circle (class)

- `Circle()` - constructor for Circle
- `Circle(const Point*, const std::string&, const double&)` - constructor with parameters for Circle (sets the points of the shape, their amount, the color and the type of the shape)
- `void setSize(const Point&) override` - sets the radius of the circle
- `void print() const override` - prints the information about the circle
- `const Point getAdditionalPoints() const override` - returns the radius in the following format (radius, 0)

### CommandLineInterface (class)

- `static CommandLineInterface& getInstance()` - CommandLineInterface is singleton, this is how we access the instance
- `bool exec(const std::string&)` - executes a user command and returns true/false depending on the outcome

### DynamicMemoryManagment (group of functions)

- `inline void deleteDynamicArray(Point* objectToDelete)` - deletes an dynamic array of points
- `inline Point* copyDynamicArray(const Point* source, const int sizeOfBothArrays)` - copies the content of `source` to a new dynamic array
- `inline Point* insertObjectIntoArray(std::pair<Point, const int> objectToInsertAtPosition, std::pair<Point*, const int> arrayToBeInsertedInWithItsSize)` - inserts a point at a specified index in an dynamic array
- `inline bool isNullptr(const Point* pointToCheck)` - checks if the pointer is `nullptr`

### InputParser (group of functions)

- `inline const std::string convertLineFromFileToCommandRectangle(const std::string &line)` - converts a line from the opened SVG file to a command, which will be used to create the `Rectangle` object:

  ```c++
  //<rect x="77.000000" y="73.000000" width="1.000000" height="1.000000" fill="#3399ff" />
  //to
  //create rectangle 77.000000 73.000000 1.000000 1.000000 #3399ff
  ```

- `inline std::string convertLineFromFileToCommandCircle(std::string line)` - converts a line from the opened SVG file to a command, which will be used to create the `Circle` object:

  ```c++
  //<circle cx="35.000000" cy="32.000000" r="2.000000" fill="#3399ff" />
  //to
  //create circle 32.000000 32.000000 2.000000 #3399ff
  ```

- `inline std::string convertLineFromFileToCommandLine(std::string line)` - converts a line from the opened SVG file to a command, which will be used to create the `Line` object:

- `inline std::string convertRectangleObjectToLine(const BaseShape *objectToConvert)` - converts an `Rectangle` object to valid SVG

- `inline std::string convertCircleObjectToLine(const BaseShape *objectToConvert)` - converts an `Circle` objecto to valid SVG

- `inline std::string convertLineObjectToLine(const BaseShape *objectToConvert)` - converts an `Line` objecto to valid SVG

### InputValidation (group of functions)

- `inline bool isValidLineRectangle(std::string line)` - checks if the SVG line represents a valid rectangle line
- `inline bool isValidLineCircle(std::string line)` - checks if the SVG line represents a valid circle
- `inline bool isValidLineLine(std::string line)` - checks if the SVG line represents a valid line
- `inline bool isColorStringValid(const std::string colorToCheck)` - checks if the string is a valid hex color

### Line (class)

- `Line()` - constructor
- `Line(const Point*, const std::string)` - constructor that has the two points and the color of the line
- `void print() const override;` - prints the information about the line

### MathFunction (group of functions)

- `inline bool checkIfDoubleIsInInterval(const double toCheck, const std::pair<double, double> interval)` - checks if a double is in a specified interval
- `inline double getDistanceBetweenTwoPoints(const Point &a, const Point &b)` - get the distance between two 2D points
- `inline bool isNumberBiggerThanZero(const int numberToCheck)` - checks if the number is positive
- `inline bool isNumberBiggerThanZero(const double numberToCheck)` - checks if the number is positive

### Point (class)

- `Point()` - constructor for the `Point` class
- `Point(const double&, const double& );` - sets the x & y coordinates
- `double getX() const;` - getter for X
- `double getY() const;` - getter for Y
- `void setX(const double& x);` - setter for X
- `void setY(const double& y);` - setter for Y

### Rectangle(class)

- `Rectangle()` - constructor
- `Rectangle(const Point*, const std::string, const double, const double)` -  constructor with arguments - (x,y), color, width and heght
- `const Point getAdditionalPoints() const override;` - return (width,height)
- `void setSize(const Point&) override;` - sets the width and height
- `void print() const override;` - prints all information about the rectangle

### StringManip (group of functions)

- `inline const int countChar(const std::string& userInput, const char searched)` - counts how many times a character occurs in a string
- `inline const std::string removeChar(const std::string& userInput, const char charToRemove)` - removes all occurrences of a character in a string
- `inline const std::string removeBrackets(const std::string& userInput)` - remove '<', '>' and '/' from a string
- `inline const std::string removeBlankSpaces(const std::string& userInput)` - removes whitespaces from a string
- `inline const std::string replaceAll(const std::string& input, const char replaced, const char with)` - replaces all occurrences of a char with another one
- `inline const int findNthOccuranceOfChar(const std::string& input, const char& toFind, const int& n)` - finds the n-th occurrence of a character
- `inline const double cutFirstNumberFromStringAsDouble(std::string& input, const char& delimiter)` - Returns the first number surrounded by <delimiter>. Also remove the <delimiters> around the number and the number itself from the string
- `inline const std::string cutFirstSubstringFromString(std::string& input, const char& delimiter)` - Returns the first substring surrounded by <delimiter>. Also remove the <delimiters> around the substring and the substring itself from the string
- `inline const std::string removeFirstSubstringFromString(const std::string& input, const char& delimiter)` - Removes the first substring surrounded by <delimiter>. Does not return it
- `inline const std::string concatenateTwoStrings(const std::string& first, const std::string& second)` - concatenates two strings
- `inline const std::string removeWordFromString(const std::string& wordToRemove, const std::string& from)` - removes a word from a given string 

### SVGContainer (class)

- `static SVGContainer& getInstance()` - because `SVGContainer` is a singleton, this method returns the instance
- `void addShape(BaseShape*)` - adds a `BaseShape` object to the container
- `void printShapes()` - prints all information in the shapes in the container
- `void printShapes(int)` - prints all information about shape at index
- `void eraseShape(const int)` - erases shape at index
- `void translateShape(const int&, const double&, const double&)` - translates shape at index by horizontal and vertical
- `const BaseShape * getItem(const int) const` - gets the shape at index
- `const int getCount() const;` - gets the amount of shapes in the container

### SVGFile (class)

- `static SVGFile& getInstance()` - because `SVGFile` is a singleton, this method returns the instance
- `const int openFile(const std::string &)` - opens the file specified in the path
- `int saveFile(const SVGContainer&);` - saves an SVGContainer to the currently open file
- `int saveAsFile(const std::string&, const SVGContainer&);` - saves an SVGContainer in a new file
- `int closeFile();` - closes the currently open file
- `std::string getFileName() const;` - returns the name of the opened file
- `std::vector<std::string> loadIntoContainer() const;` - returns the commands from the opened file 

## How it works (User point of view)

When the tool is started, the user can enter one of the following commands:

- open - to open a file: open C:\file.svg
- close - to close the file: close
- save - to save the current file: save
- saveas - to save the file in a new place: saveas C:\file.svg
- exit - to exit the program: exit
- print - prints all figures
- create - creates a new figure:
  - create <figure> <points> <additionalPoints> <color>
    - <rectangle> := create rectangle <x> <y> <width> <height> <color>
    - <circle> := create circle <x> <y> <r> <color>
    - <line> := create line <x1> <y1> <x2> <y2> <color>
- erase - erase a figure, by id: erase 2
- translates - translates all or one figure:
  - translate vertical=10 horizontal=100 
  - translate 1 vertical=20 horizontal=200

## How it works (Code point of view)

1. When the tool is started, the user should enter the open command, because the other require a file to opened.
2. When a file is being open, all lines are being read, the ones that the application supports, are being parsed to commands
3. Then those commands are processed by the `CommandLineInterface` 
4. The user can enter new commands that are parsed by the `CommandLineInterface`
5. When saving the file, the shapes in the `SVGContainer` are parsed by the `CommandLineInterface` to create valid SVG and the file is saved. 