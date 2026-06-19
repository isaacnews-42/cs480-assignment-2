//
// Created by Zakaria Abdullahi on 6/15/26.
// Zakaria Abdullahi -- Cssc3101
// Isaac Afram  --  Cssc3103
//
#include "xsh.h"
#include <unistd.h>
#include <sys/wait.h>


void executePipedCommand(const CommandLine& commandLine) {
    int pipefd[2];
    pipe(pipefd);

    pid_t firstPid = fork();
    if (firstPid == 0) {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);

        execlp(commandLine.commands[0].program.c_str(),
            commandLine.commands[0].program.c_str(),
            nullptr);
        perror("exec failed");
        exit(1);
    }

    pid_t secondPid = fork();
    if (secondPid == 0) {
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);

        execlp(commandLine.commands[1].program.c_str(),
            commandLine.commands[1].program.c_str(),
            nullptr);
        perror("exec failed");
        exit(1);
    }
    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(firstPid,nullptr,0);
    waitpid(secondPid,nullptr,0);
}


void executeCommand(const CommandLine& commandLine) {
    if (commandLine.commands.empty()) {
        return;
    }
    if (commandLine.hasPipe) {
        executePipedCommand(commandLine);
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

