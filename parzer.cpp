//
// Created by Zakaria Abdullahi on 6/15/26.
// Zakaria Abdullahi -- Cssc3101
// Isaac Afram  --  Cssc3103
//
#include "xsh.h"
#include <sstream>

CommandLine parseInput(const string& input) {
    CommandLine commandLine;

    stringstream ss(input);
    string word;
    vector<string> words;

    while (ss >> word) {
        words.push_back(word);
    }

    if (words.empty()) {
        commandLine.valid = false;
        return commandLine;
    }

    Command command;

    for (int i = 0; i < words.size(); i++) {
        // If current word is a pipe, check to see if commandline is empty.
        // If empty, trigger invalid command. If not empty, add command to
        // commands and update hasPipe flag. //

        if (words[i] == "|") {
            if (command.program.empty()) {
                commandLine.valid = false;
                return commandLine;
            }
            commandLine.commands.push_back(command);
            command = Command();
            commandLine.hasPipe = true;
        }
        else {
            // If command line is currently empty, add
            // current word as a program //
            if (command.program.empty()) {
                command.program = words[i];
            }
            // If command doesn't have argument or pipe, add
            // current word as program argument //
            else if (!command.hasArgument && !commandLine.hasPipe) {
                command.argument = words[i];
                command.hasArgument = true;
            }
            else {
                commandLine.valid = false;
                return commandLine;
            }
        }
    }


    if (command.program.empty()) {
        commandLine.valid = false;
        return commandLine;
    }

    commandLine.commands.push_back(command);

    return commandLine;

    // while (ss >> word) {
    //     words.push_back(word);
    //     Command command;
    //     command.program = word;
    //     commandLine.commands.push_back(command);
    // }
    // return commandLine;

}