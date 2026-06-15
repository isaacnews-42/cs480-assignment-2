//
// Created by Zakaria Abdullahi on 6/15/26.
//

#ifndef CS480_ASSIGNMENT_2_Z_XSH_H
#define CS480_ASSIGNMENT_2_Z_XSH_H

#endif //CS480_ASSIGNMENT_2_Z_XSH_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Command {
    string program;
    string argument;
    bool hasArgument = false;
};

struct CommandLine {
    vector<Command> commands;
    bool hasPipe = false;
    bool valid = true;
};

void printPrompt();
string readInput();

