//
// Created by Zakaria Abdullahi on 6/13/26.
//
#include <iostream>
#include <string>

using namespace std;

void printPrompt() {
    char* user = getenv("USER");
    if (user != nullptr) {
        cout << user << "% ";
    }
    else {
        cout << "xsh% ";
    }
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
        cout << "You typed: " << input << endl;
    }
    return 0;
}
