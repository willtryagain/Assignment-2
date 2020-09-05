#include "headers.h"
#include "macros.h"
#include "ex.h"
#include "pwd.h"

void get_args(char *command, int *count, char args[][SIZE]) {
	int cnt = 0;
	char *word = strtok(command, " ");
	while (word != NULL) {
		// printf("%s/", word);
		format(word);
		// printf("%s/", word);
		strcpy(args[++cnt], word);
		word = strtok(NULL, " ");
	}
	*count = cnt;
	// printf("\n");
}


void split_commands(char *commands, char *begin) {
	int type = -1;
	int len, index1=0, index2=0;
	int count;
	//assuming max 100 words in one command
	char *args1[SIZE]; 
	char *args2[SIZE];
	//command 1 ; command 2;  
	char *command = strtok(commands, ";");
	while (command != NULL) {
		// printf("%s/", command);
		args1[index1++] = command;
		command = strtok(NULL, ";");
	}
	int n = strlen(args1[index1-1]);	
	args1[index1-1][n-1] = 0;
	// ls/-a ... 
	for (int i = 0; i < index1; ++i) {
		char *word = strtok(args1[i], " ");
		while (word != NULL) {
			// printf("%s/", word);
			args2[index2++] = word;
			word = strtok(NULL, " ");		
		}
		ex(index2, begin, args2);
	}
	
}