# Plan for the project

## Defensive programming. Exceptions. Optimizations (28) 

### Expect incorrect input and handle it correctly

### Check the values of all routine input parameters

### Decide how to handle bad inputs 

### Assertion

### Exceptions

### Use descriptive error messages

## Source code – formating and (self-)documentation (28)

### THE FORMATTING of the source code should disclose its logical structure

### Brackets in the method declaration should be formated as follows: private static long fact(int num) (no spaces)

### Use an empty line to separate logically related sequences of lines: 

### Use the following order of definitions: 

### 	Constants, inner types, fields, constructors, get/set, methods 

### 	Static members, public members, protected members, default/internal members, private members 

### External documentation

- At a higher level compared to code
- Problem definition, requirements, architecture, design, project plans, test plans. etc. 

### Internal documentation

- Lower-level – explains a class, method or  a piece of code

### Classes –Does the class’s interface present a consistent abstraction? 

- Does the class’s interface make obvious how you should use the class? 
- Is the class well named and does its name describe its purpose? 
- Can you treat the class as a black box? –Do you reuse instead of repeating code? 

### Methods 

- Does each routine’s name describe exactly what the method does? 
- Does each method perform one well-defined task with minimal dependencies? 

### Type Names

- Are type names descriptive enough to help document data declarations?  
- Are variables used only for the purpose for which they’re named? 
- Do naming conventions distinguish among type names, enumerated types,  named constants, local variables, class variables, and global variables?

### Others

- Are data types simple so that they minimize complexity?  
- Are related statements grouped together?  

### Effective comments do not repeat the code 

### Comment the code intent, not implementation details 

### Focus paragraph comments on the why rather than the how

### Comment anything that gets around an error or an undocumented feature

### Describe the design approach to the class 

### Describe limitations, usage assumptions, and so on 

### Comment the class interface (public methods / properties / events / constructors) 

### Don’t document implementation details in the class interface 

### Describe the purpose and contents of each file  

### Give the file a name related to its contents 



## SVGContainer & SVGFile should be Singleton (29)

## Support for non-hex colors (29)

## Fix the bug with Circle/Rectangle (29)

## Migrate from .h to .hpp (29)

## Rewrite Polygon support (Maybe remove it if there is no time) (29)

## Comments in the SVG file (How are they handeled) (29)

## Unit testing (30)