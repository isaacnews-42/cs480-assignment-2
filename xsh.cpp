#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
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
        	goto next_loop;
    	}

    	if (t.size() > 2) {
        	cerr << "Too many arguments\n";
        	goto next_loop;
    	}

	if (access(t[0].c_str(), X_OK) != 0) {
    	cerr << "Command not found\n";
    	goto next_loop;
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
        	goto next_loop;
   	}
   }
vector<pid_t> pids;

for (int i = 0; i < n; i++) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        goto next_loop;
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

        vector<string> tokens = parse_command(line);

	if(tokens.empty()){
	    continue;
	}

	if (tokens.size() > 2) {
    		cerr << "Too many arguments\n";
    		continue;
	}

	if (access(tokens[0].c_str(), X_OK) != 0) {
    		cerr << "Command not found\n";
    		continue;
	}

	size_t pos = line.find('|');
	if (pos != string::npos) {
    	string Ls = line.substr(0, pos);
    	string Rs = line.substr(pos + 1);

    	vector<string> L = parse_command(Ls);
    	vector<string> R = parse_command(Rs);

	if (L.size() > 2 || R.size() > 2) {
    		cerr << "Too many arguments\n";
    		continue;
	}



    	vector<char*> LA, RA;
    	for (auto &t : L) LA.push_back((char*)t.c_str());
    	for (auto &t : R) RA.push_back((char*)t.c_str());
    	LA.push_back(NULL);
    	RA.push_back(NULL);

    	int fd[2]; pipe(fd);

    	if (fork() == 0) {
        	dup2(fd[1], 1);
        	close(fd[0]);
        	execvp(LA[0], LA.data());
        	_exit(1);
    	}

    	if (fork() == 0) {
        	dup2(fd[0], 0);
        	close(fd[1]);
        	execvp(RA[0], RA.data());
        	_exit(1);
    	}

    	close(fd[0]); close(fd[1]);
    	wait(NULL); wait(NULL);
    	continue;
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

	next_loop:
        continue;
    }



    return 0;
}
