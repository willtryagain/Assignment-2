#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char *argv[]) {
	DIR *dir;
	struct dirent *f;
	struct stat s;
	struct passwd *p;
	struct group *g;
	int SIZE = 1024;
	char buf[SIZE];
	dir = opendir(argv[1]);
	while ((f = readdir(dir)) != NULL) {
		sprintf(buf, "%s/%s", argv[1], f->d_name);
		stat(buf, &s);
		switch (s.st_mode & S_IFMT) {
			case S_IFBLK:
				printf("b");
				break;
			case S_IFCHR:
				printf("c");
				break;
			case S_IFDIR:
				printf("d");
				break;
			case S_IFIFO:
				printf("p");
				break;
			case S_IFLNK:
				printf("l");
				break;
			case S_IFSOCK:
				printf("s");
				break;
			default:
				printf("-");
				break;		
		}

		printf((s.st_mode & S_IRUSR) ? "r" : "-");
		printf((s.st_mode & S_IWUSR) ? "w" : "-");
		printf((s.st_mode & S_IXUSR) ? "x" : "-");
		printf((s.st_mode & S_IRGRP) ? "r" : "-");
		printf((s.st_mode & S_IWGRP) ? "w" : "-");
		printf((s.st_mode & S_IXGRP) ? "x" : "-");
		printf((s.st_mode & S_IROTH) ? "r" : "-");
		printf((s.st_mode & S_IWOTH) ? "w" : "-");
		printf((s.st_mode & S_IXOTH) ? "x" : "-");
	
		printf("  %d", s.st_nlink);

		p = getpwuid(s.st_uid);
		printf(" %s ", p->pw_name);

		g = getgrgid(s.st_gid);
		printf(" %s ", g->gr_name);

		printf("%zu", s.st_size);
		printf(" %s", ctime(&s.st_mtime));
		printf(" %s", f->d_name);
	}	
	close(dir);

}