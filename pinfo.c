#include "headers.h"

#define SIZE 1024

int VmSize = -1;
char State = '\0';
char path[SIZE], ex_path[SIZE] = "NULL";

int parse_line(char *line) {
	//for kb
	int n = strlen(line);
	const char* p = line;
	while (*p < '0' || *p > '9')
		*p++;
	line[n-3] = '\0';
	return atoi(p);
}

void get_vmsize_state(char *path) {
	FILE *file = fopen(path, "r");
	if (errno) {
      perror("pinfo fopen");
      return;
    }
    char line[SIZE];
    while (fgets(line, 128, file) != NULL) {
    	if (strncmp(line, "VmSize", 6) == 0) 
    		VmSize = parse_line(line);
    	else if (strncmp(line, "State", 5) == 0) 
    		State = line[7];
    }
}

void get_ex_path(char *path) {
	readlink(path, ex_path, SIZE);
	if (errno) 
      perror("pinfo");
}

void pinfo(int count, char *args[]) {
	char path_v[SIZE], path_e[SIZE];
	strcpy(path_v, "/proc/");
	strcpy(path_e, "/proc/");
	if (count == 2) {
		strcat(path_v, args[1]);
		strcat(path_e, args[1]);
	} else if (count == 1) {
		strcat(path_v, "self");
		strcat(path_e, "self");
	} else {
		printf("pinfo: too many arguments\n");
		return;
	}
	strcat(path_v, "/status");
	strcat(path_e, "/exe");
	get_vmsize_state(path_v);
	get_ex_path(path_e);
	printf("\n");
	printf("pid -- %d\n", getpid());
	printf("Process Status -- %c\n", State);
	printf("memory -- %d\n", VmSize);
	modify_path(ex_path);
	printf("Executable Path -- %s\n", ex_path);
}