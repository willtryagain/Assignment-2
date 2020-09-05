#include "headers.h"
#include "macros.h"

static char* global_dir = ".";

struct Choices {
	bool has_l;
	bool has_a;
};

static void init_choices(struct Choices* choices) {
	choices -> has_a = false;
	choices -> has_l = false; 
}

struct Choices get_choices(int count, char args[][SIZE]) {
	struct Choices choices;
	init_choices(&choices);
	int opt;
	while ((opt = getopt(count, args, "al")) != -1) {
		switch (opt) {
			case 'a': 
				choices.has_a = true;
				break;
			case 'l':
				choices.has_l = true;
				break;
			case '?':
				exit(EX_USAGE);	
		}
	}
	return choices;	
}

static void out_permissions(mode_t mode) {
	putchar((mode & S_IRUSR) ? 'r' : '-');
	putchar((mode & S_IWUSR) ? 'w' : '-');
	putchar((mode & S_IXUSR) ? 'x' : '-');
	putchar((mode & S_IRGRP) ? 'r' : '-');
	putchar((mode & S_IWGRP) ? 'w' : '-');
	putchar((mode & S_IXGRP) ? 'x' : '-');
	putchar((mode & S_IRUSR) ? 'r' : '-');
	putchar((mode & S_IWUSR) ? 'w' : '-');
	putchar((mode & S_IXUSR) ? 'x' : '-');
}

static void out_filetype(mode_t mode) {
	switch (mode & S_IFMT) {
		case S_IFREG:
			putchar('-');
			break;
		case S_IFDIR:
			putchar('d');
			break;
		case S_IFLNK:
			putchar('l');
			break;
		case S_IFCHR:
			putchar('c');
			break;
		case S_IFBLK:
			putchar('b');
			break;
		case S_IFSOCK:
			putchar('s');
			break;
		case S_IFIFO:
			putchar('f');
			break;
	}
}

void style_fs(double size, char *buf) {
	const char* units[] = {"", "K", "M", "G", "T"};
	int i = 0;
	while (i > 1024) {
		size /= 1024;
		i++;
	}
	sprintf(buf, "%.*f%s", i, size, units[i]);
}

void out_time(time_t mod_time) {
	//get current time with year
	time_t curr_time;
	time(&curr_time);
	struct tm* t = localtime(&curr_time);
	const int curr_mon = t->tm_mon;
	const int curr_yr = 1970 + t->tm_year;

	//get mod time with year
	t = localtime(&mod_time);
	const int mod_mon = t->tm_mon;
	const int mod_yr = 1970 + t->tm_year;

	//determine format
	const char *format = ((mod_yr == curr_yr) &&
		                  (mod_mon >= (curr_mon - 6))) ? 
						  "%b %e %H:%M":
						  "%b %e  %Y";
	char time_buf[256];
	strftime(time_buf, sizeof(time_buf), format, t);
	printf("%s", time_buf);				  
}	

struct stat get_stats(const char *filename) {
	char path[1024];
	sprintf(path, "%s/%s", global_dir, filename);
	struct stat sb;
	if (lstat(path, &sb) < 0) {
		perror(path);
		exit(EX_IOERR);
	}
	return sb;
}	

bool is_dir(const char* filename) {
	struct stat sb = get_stats(filename);

	if (lstat(filename, &sb) < 0) {
		perror(filename);
		return false;
	}

	return (sb.st_mode & S_IFDIR) ? true: false;
}

bool is_in_dir(const char *dir, const char *filename) {
	DIR *dfd = opendir(dir);
	
	if (!dfd) {
		perror(dir);
		return false;
	}
	
	struct dirent* dp = readdir(dfd);

	while (dp) {

		if (strcmp(filename, dp->d_name) == 0) {
			closedir(dfd);
			return true;
		}

		dp = readdir(dfd);
	}

	fprintf(stderr, "not found \'%s\'\n", filename);

	closedir(dfd);

	return false;
}

void out_name_link(const char* filename, struct Choices choices, mode_t mode) {
	if (mode & S_IFLNK) {
		char link_buf[512];
		int count = readlink(filename, link_buf, sizeof(link_buf));

		if (count >= 0) {
			link_buf[count] = '\0';
			printf("%s -> %s \n", filename, link_buf);
			return;
		}
	}	

	printf(" %s", filename);

	putchar('\n');
}

void display_stats(char *dir, char *filename, struct Choices choices) {
	if (!is_in_dir(dir, filename))
		return;
	if (!choices.has_l) {
		printf("%s\n", filename);
		return;
	}
	global_dir = dir;

	struct stat sb = get_stats(filename);

	out_filetype(sb.st_mode);
	out_permissions(sb.st_mode);
	printf(" %ld ", sb.st_nlink);
	printf("%10s ", getpwuid(sb.st_uid)->pw_name);
	printf("%10s", getgrgid(sb.st_gid)->gr_name);
	printf("%10ld ", (long)sb.st_size);

	out_time(sb.st_mtime);
	out_name_link(filename, choices, sb.st_mode);
}

bool can_recurse_dir(const char *parent, char *curr) {
	if (!strcmp(".", curr) || !strcmp("..", curr))
		return false;
	char path[2048];
	sprintf(path, "%s/%s", parent, curr);
	struct stat sb;

	if (lstat(path, &sb) < 0) {
		perror(path);
		exit(EX_IOERR);
	}

	return S_ISDIR(sb.st_mode);
}

void recurse_dirs(char *dir, struct Choices choices) {
	DIR *dfd = opendir(dir);
	struct dirent* dp = readdir(dfd);

	printf("\n%s:\n", dir);

	while ((dp = readdir(dfd))) {
		const bool omit_hidden = !choices.has_a && dp->d_name[0] == '.';

		if (!omit_hidden) {
			if (choices.has_l)
				display_stats(dir, dp->d_name, choices);
			else
				printf("%s\n", dp->d_name);
		}

		if (can_recurse_dir(dir, dp->d_name)) {
			char next[1024];
			sprintf(next, "%s/%s", dir, dp->d_name);
			recurse_dirs(next, choices);
		}
	}
	closedir(dfd);
}

static int cmp_lex(const void* p1, const void* p2) {
	const char* str1 = *(const void**)p1;
	const char* str2 = *(const void**)p2;

	return strcasecmp(str1, str2);
}

static int cmp_time(const void* p1, const void* p2) {
	const char* str1 = *(const void**)p1;
	const char* str2 = *(const void**)p2;

	time_t time1 = get_stats(str1).st_mtime;
	time_t time2 = get_stats(str2).st_mtime;

	return time1 < time2;
}

static int cmp_size(const void* p1, const void* p2) {
	const char* str1 = *(const void**)p1;
	const char* str2 = *(const void**)p2;

	long int size1 = get_stats(str1).st_size;
	long int size2 = get_stats(str2).st_size;

	return size1 < size2;
}

void display_dir(char *dir, struct Choices choices) {
	long int count = 0;
	DIR *dfd = opendir(dir);
	struct dirent* dp = readdir(dfd);
	long curr_alloc_amt = 30000;
	char **dir_arr = malloc(curr_alloc_amt * sizeof(char*));

	if (!dir_arr) 
		abort();

	while (dp) {
		const bool omit_hidden = !choices.has_a && dp->d_name[0] == '.';
		if (!omit_hidden) {
			if (count >= curr_alloc_amt) {
				curr_alloc_amt *= 2;
				dir_arr = realloc(dir_arr, curr_alloc_amt*sizeof(char*));
				if (!dir_arr)
					abort();		
			}
			dir_arr[count] = dp->d_name;
			count++;
		}		
		dp = readdir(dfd);
	}

	global_dir = dir;
	qsort(dir_arr, count, sizeof(char*), cmp_lex);
	
	for (long i = 0; i < count; ++i)
		display_stats(dir, dir_arr[i], choices);	
	closedir(dfd);
	free(dir_arr);
}	

void scan_dirs(int count, char* args[], struct Choices choices) {
	if (optind == count)
		display_dir(".", choices);
	const bool multiple_dirs = (count - optind) >= 2;
	// loop through the directories
	for (int i = optind; i < count; ++i) {
		printf("%s\n", args[i]);
		if (!is_dir(args[i])) {
			display_stats(".", args[i], choices);
			continue;
		} 
		//display dir name for multiple dirs
		if (multiple_dirs)
			printf("\n%s:\n", args[i]);
		// if (!is_in_dir(".", args[i]))
		// 	continue;
		display_dir(args[i], choices);
	}
}

void ls(int argc, char* argv[]) {
	
	scan_dirs(argc, argv, get_choices(argc, argv));
}
