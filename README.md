# CS 480-assignment-2
Zakaria Abdullahi -- cssc3101
Issac Afram -- cssc3103

# Files #
main.cpp
Contains the main shell loop.

parser.cpp
Parses user input into Command and CommandLine objects.
Detects commands, arguments, and pipe operators.

executor.cpp
Executes commands using fork(), exec(), waitpid(),
and pipe() system calls.

xsh.h
Shared structures and function declarations.

Makefile
Builds the executable xsh.

README
Project documentation.

# COMPILATION & Running #
- Compile the project using "make" which produces an executable file "xsh"
- Clean build using "make clean"
- Run the shell using "./xsh"
