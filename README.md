# FamilyTreeBuilder
 CLI-based family tree program in C++ with modular structure, dynamic memory management, and comprehensive relationship queries.
 
# Repository Name: FamilyTreeExplorer

Description: This project implements a family tree management system that allows users to explore family relationships, such as children, siblings, cousins, and grandparents. It includes command-line commands for users to interact with and visualize the relationships between family members, utilizing modular code to separate core functionality from utilities and command-line interactions.

# README.md Content
FamilyTreeExplorer
Overview
This project is an implementation of a family tree structure where users can load family data from a file, manage relationships, and search for specific familial connections. Using C++ pointers and dynamic memory management, this project emphasizes modular design principles and effective use of classes and data structures.

# Goal
The goal of this project is to practice code reading and modularity while gaining deeper insight into pointers and dynamic memory management in C++. The project is divided into multiple modules, each handling a specific aspect of the family tree system.

# Features
Load Family Data: Reads a CSV file containing family data.
Manage Relationships: Defines parent-child, sibling, and cousin relationships.
CLI Commands: Offers multiple command-line commands to explore family relationships.
Modular Structure: Divides functionality across multiple modules, promoting code readability and maintainability.
# Modules
Main: Handles input file processing and program initiation.
Cli: Manages command-line parsing and executes commands.
Utils: Contains utility functions for processing and helper functionalities.
FamilyTree: Core module, storing family member data, managing relationships, and implementing search functionality.
Setup Instructions
Prerequisites
C++ Compiler: GCC or Clang with C++11 or later support.
CMake: Version 3.15 or newer.
Setting Up the Project
Clone the repository:

# bash
git clone https://github.com/salmansystech/FamilyTreeExplorer.git
cd FamilyTreeExplorer
# Configure and build with QTcreator:



Run the program:
Usage
Loading Family Data
The program requires a CSV file with the format:

<ID>;<Height>;<Parent1>;<Parent2>
# Example file:
csv
Quagmire McDuck;120;-;-
'Dirty' Dingus McDuck;120;-;-
Molly Mallard;120;-;-
Angus 'Pothole' McDuck;122;'Dirty' Dingus McDuck;Molly Mallard
Fergus McDuck;122;'Dirty' Dingus McDuck;Molly Mallard
Jake McDuck;122;'Dirty' Dingus McDuck;Molly Mallard
Downy O'Drake;122;-;-
Scrooge McDuck;124;Fergus McDuck;Downy O'Drake
Matilda McDuck;124;Fergus McDuck;Downy O'Drake
Hortense McDuck;124;Fergus McDuck;Downy O'Drake
Gus Goose;125;-;-
Luke Goose;123;-;-
Grandma Duck;121;-;-
Daphne Duck;123;-;Grandma Duck
Quackmore Duck;123;-;Grandma Duck
Gladstone Gander;125;Luke Goose;Daphne Duck
Daisy Duck;126;-;-
Donald Duck;126;Quackmore Duck;Hortense McDuck
Thelma Duck;126;Quackmore Duck;Hortense McDuck
Huey;100;-;Thelma Duck
Dewey;100;-;Thelma Duck
Louie;100;-;Thelma Duck

# Commands
The program supports the following commands:

PRINT - Displays all family members and their heights.
CHILDREN <ID> - Displays children of the specified person.
SIBLINGS <ID> - Displays siblings of the specified person.
PARENTS <ID> - Displays parents of the specified person.
COUSINS <ID> - Displays cousins of the specified person.
TALLEST <ID> - Finds and displays the tallest person in the family tree starting from a specific ID.
GRANDCHILDREN <ID> <N> - Displays grandchildren up to level N.
GRANDPARENTS <ID> <N> - Displays grandparents up to level N.
EXIT - Closes the program.
Example usage:

PRINT
CHILDREN "Thelma Duck"
PARENTS Dewey
COUSINS Dewey
TALLEST "Thelma Duck"
Code Structure and Functionality
Class: FamilyTree
The FamilyTree class stores and manages all information about family members and their relationships.

Methods:
addNewPerson: Creates a new person in the family tree.
addRelation: Adds a parent-child relationship between two family members.
printPersons: Displays all family members.
printChildren: Displays the children of a specific family member.
printSiblings: Displays the siblings of a specific family member.
printCousins: Displays the cousins of a specific family member.
printParents: Displays the parents of a specific family member.
printTallestInLineage: Finds and displays the tallest person in a specific lineage.
Additional methods to manage grandparents, grandchildren, etc.
Modular Implementation
Each feature is implemented in a function within the FamilyTree class, with function pointers used for some operations. All functions within FamilyTree are accessible through the Cli interface, which processes commands and calls relevant functions.

Error Handling
The program provides informative error messages for common issues:

If a person is not found in the data: "Error. <ID> not found."
If no matches are found for a command: "<ID> has no <group to be printed>."
For invalid input on grandparent or grandchild levels: "Error. Level can't be less than 1."
Development Notes
Implementation Tips
Memory Management: Ensure that each family member’s data is dynamically allocated, and properly free memory to avoid leaks.
Modular Design: Each feature should be isolated in a separate function within FamilyTree.
Error Handling: Implement robust error checking in functions handling relationships.
Additional Requirements
Parent Linking: Use the provided Person struct and ensure relationships are linked by pointers.
Dynamic Allocation: All Person instances must be dynamically allocated, with pointers stored in an STL container, such as std::map or std::unordered_map.
Testing
To ensure correctness, test the program with a variety of family trees, including cases where:

Individuals have no parents listed.
Different levels of lineage queries return accurate relationships.
Height comparisons accurately reflect the tallest in the lineage.
Future Enhancements
Add support for optional features such as printShortestInLineage.
Extend handling of additional complex family structures for advanced scenarios.
# License
This project is for educational use and does not include any license for commercial deployment. For further information, please contact the project author.
