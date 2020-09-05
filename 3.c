#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/utsname.h>

#define true 1
#define SIZE 1024
#define DELIMS " \t\r\n"

char invoke_dir[SIZE], name[SIZE];
char *vector[SIZE];
char *semi = ";";

void get_name() {
  char ps[SIZE], cwd[SIZE], hostname[SIZE];
  struct utsname uts;
  strcpy(name, "<");
  getlogin_r(ps, SIZE);
  if(gethostname(hostname, SIZE)) {
    perror("gethostname");
    return;
  }
  strcat(ps, "@");
  strcat(ps, hostname);
  strcat(ps, ":");
  if (getcwd(cwd, SIZE) != NULL) {
    if (strcmp(cwd, invoke_dir)==0)
      strcpy(cwd, "~");
    strcat(ps, cwd);
    strcat(ps, ">");
    strcat(name, ps);
  } else {
     perror("getcwd() error");
     return;
  } 
  strcat(name, " ");
}

void echo(int index) {
  for (int i = 1; i < index; ++i)
    printf("%s ", vector[i]);
}

void end_str(char *str) {
  char *temp; 
  for (int i = strlen(str)-1; i >= 0; --i) {
    if (str[i] != ' ') {
      str[i+1] = '\0';
      break;
    }
  }
}

void cd(int index) {
  if (index > 2) {
    printf("Atleast one ");
    return;
  }
  end_str(vector[1]);
  printf("%s/%s\n", vector[1], "..");
  chdir("..");
  if (errno)
    perror("cd");
}

int main(int argc, char const *argv[]) {
  int len = 0;
  int count = 1;
  char line[SIZE], str[SIZE];

  getcwd(invoke_dir, SIZE);
  while (true) {
    get_name();
    printf("%s", name);
    fgets(str, SIZE, stdin);
    char *token = strtok(str, semi), *token2;
    // printf("%s\n", token);
    if (token != NULL) {
    do {
        int index = 0;
        len = strlen(token);
        printf("%s\n", token);

    //     token2 = strtok(token, " ");
    //     while (token2 != NULL) {
    //       end_str(token2);
    //       vector[index] = token2;
    //       printf("%s/%s\n", token2, vector[index]);
    //       index++;
    //       token2 = strtok(NULL, " ");
    //     }
    //     // printf("%s", name);
    //     if (strcmp(vector[0], "echo")==0) 
    //       echo(index);
    //     else if (strcmp(vector[0], "cd")==0) 
    //       cd(index);
    //     else if (strcmp(vector[0], "exit") == 0)
    //       break;
    //     // else {
    //     //   char *args[] = {vector[0], NULL};
    //     //   execvp(args[0], args);
    //     //   if (errno) {
    //     //     perror("execvp");
    //     //   }
    //     // }
    //     for (int i = 0; i < index; ++i)
    //         printf("%s ", vector[i]);
    //     printf("\n");
  
      } while ((token = strtok(token + len + 1, semi)) != NULL);
    //   if (strcmp(vector[0], "exit") == 0)
    //     break;
    }
  }
  return 0;
}