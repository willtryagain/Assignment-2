#ifndef __LSALL_C
#define __LSALL_C

struct Choices {
	bool has_l;
	bool has_a;
};

// static void init_choices(struct Choices* choices);
// struct Choices get_choices(int count, char args[][SIZE]);
// static void out_permissions(mode_t mode);
// static void out_filetype(mode_t mode);
// void style_fs(double size, char *buf);
// void out_time(time_t mod_time);
// struct stat get_stats(const char *filename);
// bool is_dir(const char* filename);
// bool is_in_dir(const char *dir, const char *filename);
// void out_name_link(const char* filename, struct Choices choices, mode_t mode);
// void display_stats(char *dir, char *filename, struct Choices choices);
// bool can_recurse_dir(const char *parent, char *curr);
// void recurse_dirs(char *dir, struct Choices choices);
// static int cmp_lex(const void* p1, const void* p2);
// static int cmp_time(const void* p1, const void* p2);
// static int cmp_size(const void* p1, const void* p2);
// void display_dir(char *dir, struct Choices choices);
// void scan_dirs(int count, char args[][SIZE], struct Choices choices);
// void ls(int argc, char const argv[][SIZE]);
void ls(int argc, char* argv[]);
#endif