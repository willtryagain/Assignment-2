#include "headers.h"
#include "macros.h"
#include "prompt.h"
#include "process_args.h"

void get_begin(char *begin) {
	char cwd[SIZE];
	getcwd(cwd, SIZE);
	if (errno) {
		perror("working directory main");
		return;
	}
	strcpy(begin, cwd);
}

extern bool bg;
int pid = 1;


int main() {
	char begin[SIZE], str[SIZE];
	int wstatus, es;
	pid_t bg_pids[50];
	int total = 0;
 
	get_begin(begin);
	
	while (1) {
		if (pid > 0) {
			printf("a %d\n", getpid());
			prompt(begin);
			fgets(str, SIZE, stdin);
			split_commands(str, begin);
			if (pid) {
				if (bg) {
					printf("%d\n", pid);
					bg_pids[total] = pid;
					total++;
				} else {
					printf("c\n");
					wait(NULL);
				}
			}
		}
	}
			// if (waitpid(parent, &wstatus, WNOHANG) == -1) 
		 //    	perror("waitpid");
		    // waitpid(parent, &wstatus, WNOHANG);
		    // if (WIFEXITED(wstatus)) {
		    // 	es = WEXITSTATUS(wstatus);
		    // 	printf(" with pid %d\n exited normally", parent);
		    // 	printf("Exit status was %d\n", es);
		    // }
		    // if (foreground)
		    // 	wait(NULL);

	return 0;
}