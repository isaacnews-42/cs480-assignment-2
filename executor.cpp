//
// Created by Zakaria Abdullahi on 6/15/26.
//
#include "xsh.h"

void executeCommand(const CommandLine& commandLine) {
    cout << "Number of commands: " << commandLine.commands.size() << endl;

    for (int i = 0; i < commandLine.commands.size(); i++) {
        cout << "Command: " << i + 1 << ": "
             << commandLine.commands[i].program << endl;
    }
}