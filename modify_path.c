#include "headers.h"
#include "macros.h"
#include "modify_path.h"

void modify_path(char *begin, char *cwd) {
	int flag = 0;
	int n = strlen(begin);
	int m = strlen(cwd);
	if (n <= m) {
		for (int i = 0; i < n; ++i) {
			if (begin[i] != cwd[i]) {
				flag = 1;
				break;
			}
		}
		if (!flag) {
			char path[SIZE];
			path[0] = '~';
			for (int i = n; i <= m; ++i)
				path[i-n+1] = cwd[i];
			strcpy(cwd, path);
		}
	}
}