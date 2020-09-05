#include "macros.h"

#ifndef __PROCESS_ARGS_H
#define __PROCESS_ARGS_H

void format(char *word); 
void get_args(char *command, int *count, char args[][SIZE]);
void split_commands(char *commands, char *begin);

#endif