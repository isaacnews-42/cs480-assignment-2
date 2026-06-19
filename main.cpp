//
// Created by Zakaria Abdullahi on 6/13/26.
// Zakaria Abdullahi -- Cssc3101
// Isaac Afram  --  Cssc3103
//
#include "xsh.h"
#include <iostream>
#include <string>
using namespace std;

void printPrompt() {
    char* user = getenv("USER");
    if (user != nullptr) {
        cout << user << "% ";
    }
    else { cout << "xsh% ";}
}

string readInput() {
    string input;
    getline(cin, input);
    return input;
}

int main() {
    while (true) {
        printPrompt();
        string input = readInput();
        if (input == "exit") {
            cout << "Goodbye!" << endl;
            break;
        }
        CommandLine commandLine = parseInput(input);
        if (!commandLine.valid) {
            cout << "Invalid command..." << endl;
            continue;
        }
        executeCommand(commandLine);
    }
    return 0;
}
