//
// Created by Zakaria Abdullahi on 6/15/26.
//
#include "xsh.h"
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>


void executePipedCommand(const vector<Command>& commands) {
    int numCommands = commands.size();
    int numPipes = numCommands - 1;
}


void executeCommand(const CommandLine& commandLine) {
    if (commandLine.commands.empty()) {
        return;
    }
    if (commandLine.hasPipe) {
        executePipedCommand(commandLine.commands);
    }

    Command command = commandLine.commands[0];

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        return;
    }
    if (pid == 0) {
        if (command.hasArgument) {
            execlp(command.program.c_str(),
                command.program.c_str(),
                command.argument.c_str(),
                nullptr);
        }
        else {
            execlp(command.program.c_str(),
                command.program.c_str(),
                nullptr);
        }
        perror("exec failed");
        exit(1);
    }
    else {
        waitpid(pid, nullptr, 0);
    }
}

