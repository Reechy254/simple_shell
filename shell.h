#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for con_num() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **env;
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/* toem_shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* toem_parser.c */
int _cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *get_path(info_t *, char *, char *);

/* toem_string.c */
int strlen_(char *);
int strcmp_(char *, char *);
char *starts_with(const char *, const char *);
char *strg_concat(char *, char *);

/* toem_string1.c */
char *cp_strg(char *, char *);
char *strdup_(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *cp_strg(char *, char *, int);
char *strg_concat(char *, char *, int);
char *strgchr(char *, char);

/* toem_realloc.c */
char *mem_fill(char *, char, unsigned int);
void free_strg(char **);
void *mem_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int setfree(void **);

/* toem_atoi.c */
int usage(info_t *);
int the_delim(char, char *);
int _alpha(int);
int to_int(char *);

/* toem_string.c */
int strlen_(char *);
int strcmp_(char *, char *);
char *starts_with(const char *, const char *);
char *strg_concat(char *, char *)

/* toem_parser.c */
int _cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *get_path(info_t *, char *, char *);

/* toem_errors1.c */
int strg_to_int(char *);
void print_error(info_t *, char *);
int print_deci(int, int);
char *conv_num(long int, int, int);
void rem_comments(char *);

/* toem_builtin.c */
int _exit(info_t *);
int _cd(info_t *);
int _change(info_t *);

/* toem_builtin1.c */
int _history(info_t *);
int _alias(info_t *);

/*toem_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* toem_environ.c */
char *_getenv(info_t *, const char *);
int _env(info_t *);
int _setenv(info_t *);
int _unsetenv(info_t *);
int populate_env_list(info_t *);

/* toem_getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void release_info(info_t *, int);

/* toem_getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* toem_history.c */
char *get_history_file(info_t *info);
int write_histo(info_t *info);
int read_histo(info_t *info);
int histo_ls_entry(info_t *info, char *buf, int linecount);
int renum_histo(info_t *info);

/* toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int del_indexnode(list_t **, unsigned int);
void free_list(list_t **);

/* toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *prefix_node(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif /* SHELL_H */
