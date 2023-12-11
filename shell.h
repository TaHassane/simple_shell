#ifndef _SHELL_H_
#define _SHELL_H_

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

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/**
 * struct data - data used by shell during runtime
 * @av: argument vector
 * @input: user's command line
 * @args: tokens from command line
 * @status: last shell execution status
 * @counter: executed command line counter
 * @_environ: environment variables
 * @pid: shell process ID
 */
typedef struct data
{
	char **av, *input, **args;
	int status, counter;
	char **_environ, *pid;
} data_shell;

/**
 * struct sep_list_s - singly linked list
 * @separator: ; | &
 * @next: next node
 * Description: Stores separators in a singly linked list.
 */

typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct r_var_list - singly linked list
 * @len_var: length of variable
 * @val: variable value
 * @len_val: length of value
 * @next: next node
 * Description: Stores variables in a singly linked list.
 */

typedef struct r_var_list
{
	int len_var, len_val;
	char *val;
	struct r_var_list *next;
} r_var;

/**
 * struct line_list_s - singly linked list
 * @line: command line
 * @next: next node
 * Description: Stores command lines in a singly linked list.
 */

typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/* Points to an array of pointers to strings known as the "environment" */
extern char **environ;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: Command builtin name (example exit, env, cd)
 * @f: Pointer to function with specific data type.
 */

typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *datash);
} builtin_t;

/*__lists.c__*/
sep_list *add_sep_node_end(sep_list **head, char sep);
void free_sep_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);
/*____________________________________________*/

/*__lists2.c__*/
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head);
/*____________________________________________*/

/*__pr_str.c__*/
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
/*____________________________________________*/

/*__mem.c__*/
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);
/*____________________________________________*/

/*__pr_str2.c__*/
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);
/*____________________________________________*/

/*__pr_str3.c__*/
void rev_string(char *s);
/*____________________________________________*/

/*__syntax_check.c__*/
int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
void print_syntax_error(data_shell *datash, char *input, int i, int bool);
int check_syntax_error(data_shell *datash, char *input);
/*____________________________________________*/

/*__shell_loop_handler.c__*/
char *without_comment(char *in);
void shell_loop(data_shell *datash);
/*____________________________________________*/

/*__input_handling.c__*/
char *read_line(int *i_eof);
/*____________________________________________*/

/*__command_parser.c__*/
char *swap_char(char *input, int bool);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash);
int split_commands(data_shell *datash, char *input);
char **split_line(char *input);
/*____________________________________________*/

/*__variable_replacement.c__*/
void check_env(r_var **h, char *in, data_shell *data);
int check_vars(r_var **h, char *in, char *st, data_shell *data);
char *replaced_input(r_var **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, data_shell *datash);
/*____________________________________________*/

/*__input_processing.c__*/
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);
/*____________________________________________*/

/*__builins.c__*/
int exec_line(data_shell *datash);
/*____________________________________________*/

/*__exec_cmd.c__*/
int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_executable(data_shell *datash);
int check_error_cmd(char *dir, data_shell *datash);
int cmd_exec(data_shell *datash);
/*____________________________________________*/

/*__env_handling.c__*/
char *_getenv(const char *name, char **_environ);
int _env(data_shell *datash);
/*____________________________________________*/

/*__env_handling2.c__*/
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, data_shell *datash);
int _setenv(data_shell *datash);
int _unsetenv(data_shell *datash);
/*____________________________________________*/

/*__pr_cd.c__*/
void cd_dot(data_shell *datash);
void cd_to(data_shell *datash);
void cd_previous(data_shell *datash);
void cd_to_home(data_shell *datash);
/*____________________________________________*/

/*__pr_shell.c__*/
int cd_shell(data_shell *datash);
/*____________________________________________*/

/*__command_parser.c__*/
int (*get_builtin(char *cmd))(data_shell *datash);
/*____________________________________________*/

/*__exit_handler.c__*/
int exit_shell(data_shell *datash);
/*____________________________________________*/

/*__pr_stdlib.c__*/
int get_len(int n);
char *aux_itoa(int n);
int _atoi(char *s);
/*____________________________________________*/

/* __eror1.c__*/
char *strcat_cd(data_shell *, char *, char *, char *);
char *error_get_cd(data_shell *datash);
char *error_not_found(data_shell *datash);
char *error_exit_shell(data_shell *datash);
/*____________________________________________*/

/*__eror2.c__*/
char *error_get_alias(char **args);
char *error_env(data_shell *datash);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_126(data_shell *datash);
/*____________________________________________*/

/*__error_handling.c__*/
int get_error(data_shell *datash, int eval);
/*____________________________________________*/

/*__signals.c__*/
void get_sigint(int sig);
/*____________________________________________*/

/*__help.c__*/
void aux_help_env(void);
void aux_help_setenv(void);
void aux_help_unsetenv(void);
void aux_help_general(void);
void aux_help_exit(void);
/*____________________________________________*/

/*__help2.c__*/
void aux_help(void);
void aux_help_alias(void);
void aux_help_cd(void);
/*____________________________________________*/

/*__help_functions.c*/
int get_help(data_shell *datash);

#endif

