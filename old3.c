#include "headers.h"
#include "macros.h"

char *built_in_commands[] = {"cd", "ls", "pwd", "pinfo"};

int find_type(char *command) {
	switch (strlen(command)) {
		case 2:
			if (strcmp(command, "cd") == 0)
				return 0;
			if (strcmp(command, "ls") == 0)
				return 1;
			break;
		case 3:
			if (strcmp(command, "pwd") == 0)
				return 2;
			break;
		case 5:
			if (strcmp(command, "pinfo") == 0)
				return 3;
			break;
	}
	return 5;
}

void format(char *word) {
	int n = strlen(word);
	if (word[n-1] == ' ') {
		for (int i = 0; i < n; ++i) {
			if (word[i] == ' ') {
				word[i] = '\0';
				break;
			}
		}
	}
}




int main(int argc, char const *argv[]) {
	int SIZE = 1024;
	int len;
	int index;
	char str[SIZE], *args[2];
	char list[10][SIZE];
	fgets(str, SIZE, stdin);
	char *command = strtok(str, ";");
	if (command != NULL) {+
		do {
			index = 0;
			
			len = strlen(command);
			char *word = strtok(command, " ");
			while (word != NULL) {
				format(word);
				printf("%d\n", find_type(word));
				strcpy(list[++index], word);
				// printf("%d/", strlen(list[index-1]));
				word = strtok(NULL, " ");
			}
			// printf("%d\n", find_type(0, list));
			// for (int i = 1; i <= index; ++i)
			// 	printf("%s/", list[i]);	
			// printf("\n");
		} while ((command = strtok(command + len + 1, ";")) != NULL);
		

	}
	return 0;
}