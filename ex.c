#include "headers.h"
#include "macros.h"
#include "cd.h"
#include "lsall.h"
#include "pinfo.h"
#include "pwd.h"

bool bg;

void format(char *word) {
	int n = strlen(word);
	if (word[n-1] == '\n')
		word[n-1] = 0;
}

bool is_fg(int argc, char* argv[]) {
	bool res = true;
	for (int i = 0; i < argc; ++i) {
		if (strcmp(argv[i], "&") == 0)
			res = false;
	}
	return res;
}

int ex(int argc, char* begin, char* argv[], char *command) {
	extern int pid;
	if (argc == 0)
			return false;
		// for (int i = 1; i <= argc; ++i) 
	// 	printf("%s/", argv[i]);
	// for (int i = ; i <= argc; ++i) 
	// 	format(argv[i]);
	// for (int i = 0; i < argc; ++i) 
	// 	printf("%s/", argv[i]);
	// printf("\n");
	if (strcmp(argv[0], "exit") == 0) {
		exit(0);
	}
	else if (strcmp(argv[0], "cd") == 0) {
		cd(argc, begin, argv);
		return true;
	}
	else if (strcmp(argv[0], "ls") == 0) {
		ls(argc, argv);
		return true;
	}
	else if (strcmp(argv[0], "pwd") == 0) {
		pwd(argc, argv);
		return true;
	} 
	else if (strcmp(argv[0], "pinfo") == 0) {
		// printf("%d\n", argc);
		pinfo(argc, argv);
		return true;
	} else if (strcmp(argv[0], "echo") == 0) {
		for (int i = 1; i < argc; ++i)
			printf("%s ", argv[i]);
		return true;
	}
	else { 
		char* edit[argc+1];
		for (int i = 0; i < argc; ++i){
			printf("%s\n", argv[i]);
			edit[i] = argv[i];
		}
		bg = !is_fg(argc, argv);
		if (bg) 
			edit[argc-1] = NULL;
		edit[argc] = NULL;
		printf("b %d\n", getpid());
		pid = fork();
		if (!pid) {
			// if (!foreground) 
			// 	setsid();
			printf("%d\n", getpid());
			execvp(edit[0], edit);
			if (errno)
				perror("ex: execvp");
			// printf("c %d\n", getpid());
		}
		// else {
		// 	if (!foreground) 
		// 		wait(NULL);
		// 	// else
		// 	printf("d %d\n", getpid());
		// 		return true;
		// }
	}
	
}