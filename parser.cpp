#include "parser.h"
#include <sstream>

vector<string> parse_command(const string &line) {
    vector<string> tokens;
    stringstream ss(line);
    string word;

    while (ss >> word) {
        tokens.push_back(word);
    }

    return tokens;
}
