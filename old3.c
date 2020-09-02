#include "headers.h"

char *built_in_commands[] = {"cd", "ls", "pwd", "pinfo"};

int find_type(int count, char *list[SIZE]) {
	if (count == 1) {
		if (list[0] == 'c' && list[1] == 'd' && list[2] == ' ')
			return 0;
		else if (l)
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
	if (command != NULL) {
		do {
			index = 0;
			
			len = strlen(command);
			char *word = strtok(command, " ");
			while (word != NULL) {
				char token[SIZE];
				// strcpy(token, word);
				strcpy(list[++index], word);
				// printf("%d/", strlen(list[index-1]));
				word = strtok(NULL, " ");
			}
			for (int i = 1; i <= index; ++i)
				printf("%s/", list[i]);	
			printf("\n");
		} while ((command = strtok(command + len + 1, ";")) != NULL);
	

	}
	return 0;
}