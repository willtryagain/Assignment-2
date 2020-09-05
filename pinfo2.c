#include "headers.h"
#include "stdio.h"
#include "string.h"

#define SIZE 1024
int VmSize = -1;
char State;
char path[SIZE];
int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

void getValue(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    if (errno) {
      perror("fopen");
      return;
    }
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmSize:", 7) == 0){
            VmSize = parseLine(line);
            break;
        } else if (strncmp(line, "State:", 6) == 0) {
          // printf("%s\n", line);
          State = line[7];
        }

    }
    readlink("/proc/self/exe", path, SIZE);
    if (errno) {
      perror("pinfo");
      return;
    }
    fclose(file);
}

void pinfo() {
  
}

int main() {
  getValue();
  printf("%d %c", VmSize, State);
  printf("%s\n", path);
  return 0;
}