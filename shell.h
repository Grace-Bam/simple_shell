#ifndef _SHELL_H_
#define _SHELL_H_

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

/* Constants */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

/* External Variable */
extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/* Structure Declarations */
/**
 * struct data - The passinfo structure contains pseudo-arguments designed
 * for passing into a function,
 * enabling a consistent prototype for a function pointer structure.
 * @arg: A string containing arguments generated from getline.
 * @argv: An array of strings generated from the arg.
 * @path: A string representing the path for the current command.
 * @argc: The count of arguments.
 * @line_count: The count of errors.
 * @err_num: The error code used for the exit() function.
 * @linecount_flag: A flag indicating whether to count this line of input.
 * @fname: The filename of the program.
 * @env: A linked list representing a local copy of the environ variable.
 * @environ: A custom modified copy of the environ variable obtained from the
 * linked list env.
 * @history: The history node.
 * @alias: A linked list representing aliases for commands.
 * @env_changed: A flag that is set to true if the environ variable
 * was changed.
 * @status: The return status of the last executed command.
 * @cmd_buf: The address of the pointer to the cmd_buf used when chaining
 * commands.
 * @cmd_buf_type: Represents the type of command, such as ||, &&, or ;.
 * @readfd: The file descriptor from which the line input is read.
 * @histcount: The count of the history line number.
 */
typedef struct data
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *alias;
	list_t *env;
	list_t *history;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

/* Macros */
#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/* Structure for Built-in Commands */
/**
 * struct builtin - Represents a built-in command and its related function
 * @type: A string that serves as the flag for the built-in command
 * @func: A pointer to the function related to the built-in command,
 * which accepts an info_t pointer and returns an integer
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_t;

/* Function Prototypes */
int main(int ac, char **av);

int safe_free(void **ptr);

int cmd_exe(info_t *info, char *path);
char *_dupchars(char *pathstr, int start, int stop);
char *get_path(info_t *info, char *pathstr, char *cmd);

char *mem_set(char *s, char b, unsigned int n);
void free_f(char **str_array);
void *re_alloc(void *ptr, unsigned int old_size, unsigned int new_size);

int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *starts_with(const char *string, const char *substring);
char *_strcat(char *dest, char *src);

char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char character);

void custom_puts(char *str);
int custom_putchar(char c);
int custom_putfd(char c, int fd);
int custom_putsfd(char *str, int fd);

int _str_to_int(char *s);
void display_error(info_t *info, char *estr);
int display_int(int input, int fd);
char *convert_to_string(long int num, int base, int flags);
void remove_comments(char *buf);

int interactive_mode(info_t *info);
int check_delim(char c, char *delim);
int is_alphabetic(int c);
int convert_to_integer(char *s);

int shell_exit(info_t *info);
int _cd(info_t *info);
int _help(info_t *info);

int _history(info_t *info);
int shell_alias(info_t *info);
int unset_alias(info_t *info, char *str);
int set_alias(info_t *info, char *str);
int print_alias(list_t *node);

void print_list_str(const list_t *h);
int print_env(info_t *info);
char *get_env(info_t *info, const char *name);
int set_env(info_t *info);
int unset_env(info_t *info);
int populate_env(info_t *info);

char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_strchr(char *s, char c);

ssize_t buffer_input(info_t *info, char **buf, size_t *len);
ssize_t get_input_line(info_t *info);
ssize_t read_buffer(info_t *info, char *buf, size_t *i);
int get_line_input(info_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused))int sig_num);

char **get_environ(info_t *info);
int _unsetenv(info_t *info, char *var);
int _setenv(info_t *info, char *var, char *value);

void clear_info(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int all);

char *history_file(info_t *info);
int write_hist(info_t *info);
int read_hist(info_t *info);
int history_list(info_t *info, char *buf, int linecount);
int re_number_hist(info_t *info);

list_t *_addnode(list_t **head, const char *str, int num);
list_t *_addnode_end(list_t **head, const char *str, int num);
size_t list_str(const list_t *h);
int delete_node_at_index(list_t **head, unsigned int index);
void _listfree(list_t **head_ptr);

size_t len_list(const list_t *h);
char **list_strings(list_t *head);
size_t list_print(const list_t *h);
list_t *node_starts_with(list_t *node, char *prefix, char c);
ssize_t node_index(list_t *head, list_t *node);

int detect_chain_delimiter(info_t *info, char *buf, size_t *pos);
void eval_chain(info_t *, char *buf, size_t *pos, size_t start, size_t len);
int substitute_aliases(info_t *info);
int substitute_variables(info_t *info);
int replace_string_content(char **old, char *new_content);

int hsh(info_t *info, char **av);
int get_builtin(info_t *info);
void get_cmd(info_t *info);
void fork_cmd(info_t *info);

char **str_tow(char *str, char *d);
char **str_tow2(char *str, char d);

#endif
