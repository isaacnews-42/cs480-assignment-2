# CS480 Assignment-2
- Zakaria Abdullahi -- cssc3101
- Issac Afram -- cssc3103

# Files #
- main.cpp: Contains the main shell loop.
- parser.cpp: Parses user input into Command and CommandLine objects. Detects commands, arguments, and pipe operators.
- executor.cpp: Executes commands using fork(), exec(), waitpid(), and pipe() system calls.
- xsh.h: Shared structures and function declarations.
- Makefile: Builds the executable xsh.
- README: Project documentation.

# Compilation & Running #
- Compile the project using "make" which produces an executable file "xsh"
- Clean build using "make clean"
- Run the shell using "./xsh"
- Exit shell by typing "exit"

# Description #
In this assignment we implemented an experimental shell (XSH) using POSIX system calls such as fork(), exec(), pipe(), and waitpid(). The shell is capable of executing commands, handling command-line arguments, and supporting piped commands between processes. Throughout our development, we met periodically over Discord to pair program, discuss implementation details, and troubleshoot issues together. We also used the fork() & exec() and other reference materials provided as a guide. Isaac primarily worked on xsh.cpp and parser.h, while Zakaria worked on executor.cpp, parzer.cpp, main.cpp, and xsh.h with both partners involved in testing and integration. Due to main.cpp(Zakaria) and xsh.cpp(Isaac) both containing their own main() functions, were only able to compile one or the other and main.cpp is being compiled in the makefile as of now. Through this assignment we gained experience building a simplified Unix-style shell, understanding process management and inter-process communication.
