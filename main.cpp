//
// Created by Zakaria Abdullahi on 6/13/26.
//
#include "xsh.h"
#include <iostream>
using namespace std;

void printPrompt() {
    cout << "cssc3101% ";
};

string readInput() {
    string input;
    getline(cin,input);
    return input;
};

int main() {
    while (true) {
        printPrompt();
        string input = readInput();

        if (input == "exit") {
            cout << "Goodbye!!!";
            break;
        }
        cout << "You typed: " << input << endl;
    }
    return 0;
}

