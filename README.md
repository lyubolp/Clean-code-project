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