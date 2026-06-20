/*
 Created by Isaac Afram on 6/15/26. 
 Zakaria Abdullahi -- Cssc3101
 Isaac Afram  --  Cssc3103
*/


#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sstream>
#include <array>
#include "parser.h"

int main() {
    string line;

    while (true) {
        const char* user = getenv("USER");
	if (!user) user = "xsh";
		cout << user << "% ";
        if (!getline(cin, line)) {
            break;
        }

        if (line == "exit") {
            break;
        }

	if (line.find('|') != string::npos) {

    	vector<string> segments;
    	stringstream ss(line);
    	string part;

    	while (getline(ss, part, '|')) {
        	while (!part.empty() && part[0] == ' ')
            	part.erase(0, 1);

        	while (!part.empty() && part.back() == ' ')
            	part.pop_back();

        	segments.push_back(part);
    	}

	vector<vector<string>> cmds;

	for (auto &seg : segments) {
    	vector<string> t = parse_command(seg);

    	if (t.empty()) {
        	cerr << "Invalid null command\n";
        	continue;
    	}

    	if (t.size() > 2) {
        	cerr << "Too many arguments\n";
        	continue;
    	}

	if (t[0].find('/') != string::npos) {
    	if (access(t[0].c_str(), X_OK) != 0) {
        	cerr << "Command not found\n";
        	continue;
    	}
	}

    	cmds.push_back(t);
}

	vector<vector<char*>> argv_list;

	for (auto &cmd : cmds) {
    		vector<char*> arr;
    	for (auto &s : cmd)
        	arr.push_back((char*)s.c_str());
    		arr.push_back(NULL);
    		argv_list.push_back(arr);
	}

	int n = cmds.size();
	vector<array<int,2>> pipes(n - 1);

	for (int i = 0; i < n - 1; i++) {
    	if (pipe(pipes[i].data()) < 0) {
        	perror("pipe");
        	continue;
   	}
   }
vector<pid_t> pids;

for (int i = 0; i < n; i++) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        continue;
    }

    if (pid == 0) {

        if (i > 0) {
            dup2(pipes[i-1][0], 0);
        }

        if (i < n - 1) {
            dup2(pipes[i][1], 1);
        }

        for (int j = 0; j < n - 1; j++) {
            close(pipes[j][0]);
            close(pipes[j][1]);
        }

        execvp(argv_list[i][0], argv_list[i].data());
        perror("execvp");
        exit(1);
    }

    pids.push_back(pid);
}

for (int i = 0; i < n - 1; i++) {
    close(pipes[i][0]);
    close(pipes[i][1]);
}

for (pid_t pid : pids) {
    waitpid(pid, NULL, 0);
}
	continue;
	} else{
		

        vector<string> tokens = parse_command(line);

	if(tokens.empty()){
	    continue;
	}

	if (tokens.size() > 2) {
    		cerr << "Too many arguments\n";
    		continue;
	}

	if (tokens[0].find('/') != string::npos) {
    	if (access(tokens[0].c_str(), X_OK) != 0) {
        	cerr << "Command not found\n";
        	continue;
    	}
	}

	vector<char*> args;
	for(auto &t : tokens){
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
	continue;

    }
    return 0;
}
