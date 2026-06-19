//
// Created by Zakaria Abdullahi on 6/15/26.
// Zakaria Abdullahi -- Cssc3101
// Isaac Afram  --  Cssc3103
//
#ifndef CS480_ASSIGNMENT_2_Z_XSH_H
#define CS480_ASSIGNMENT_2_Z_XSH_H

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

CommandLine parseInput(const string& input);
void executeCommand(const CommandLine& commandLine);

#endif //CS480_ASSIGNMENT_2_Z_XSH_H