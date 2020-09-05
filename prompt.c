#include "headers.h"
#include "macros.h"
#include "prompt.h"
#include "modify_path.h"


void prompt(char *begin) {
	char username[SIZE];
	char hostname[SIZE];
	char str[SIZE];
	char cwd[SIZE];
	getlogin_r(username, SIZE);
	if (errno) {
		perror("username");
		return;
	}
	gethostname(hostname, SIZE);
	if (errno) {
		perror("hostname");
		return;
	}
	getcwd(cwd, SIZE);
	if (errno) {
		perror("working directory");
		return;
	}
	strcpy(str, "<");
	strcat(str, username);
	strcat(str, "@");
	strcat(str,hostname);
	strcat(str, ":");
	modify_path(begin, cwd);
	strcat(str, cwd);
	strcat(str, ">");
	printf("%s", str);
}

// int main(int argc, char const *argv[]) {
// 	prompt("/home/name/Documents/operating");
// 	// printf("%d", SIZE);
// 	return 0;
// }