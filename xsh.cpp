#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "parser.h"
using namespace std;

int main() {
    string line;

    while (true) {
        cout << "xsh% ";
        if (!getline(cin, line)) {
            break;
        }

        if (line == "exit") {
            break;
        }

        vector<string> tokens = parse_command(line);

	if(tokens.empty()){
	    continue;
	}

	vector<char*> args;
	for(auto &t tokens){
	    args.push_back(const_cast<char*>(t.c_str()));
	}
	args.push_back(NULL);

	pid_t pid = fork();

	if (pid == 0){
            execvp(args[0], args.data());
            perror("execvp");
            _exit(1);
        }
	else if (pid > 0){
            waitpid(pid, nullptr, 0);
        }
	else{
            perror("fork");
        }
    }

    return 0;
}
