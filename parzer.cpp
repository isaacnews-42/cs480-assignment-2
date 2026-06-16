//
// Created by Zakaria Abdullahi on 6/15/26.
//
#include "xsh.h"
#include <iostream>
#include <sstream>

CommandLine parseInput(const string& input) {
    CommandLine commandLine;

    stringstream ss(input);
    string word;
    vector<string> words;

    while (ss >> word) {
        words.push_back(word);
        if (words.empty()) {
            cout << "Invalid command... ";
            continue;
        }
        Command command;
        command.program = word;
        commandLine.commands.push_back(command);

    }

    return commandLine;
}