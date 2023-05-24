#ifndef MAIN_H
#define MAIN_H

#define PROMPT "#csisfun$ "

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

extern char **environ;

/**
 * struct data - holds the main data.
 * @av: Array of tokens to pass for execve
 * @cmd: The user input, the command line
 * @shell_name: The name of the shell program
 * @last_exit_status: last exit status of last command executed
 * @flag_setenv: 1 if user did exec setenv (use it to free memory)
 */


typedef struct data
{
	char **av;
	char *cmd;
	const char *shell_name;
	int last_exit_status;
	int flag_setenv;
} data;

/**
 * struct builtin - holds the main data.
 * @cmd: built in cmd
 * @f: function of builtin cmd
 */
typedef struct builtin
{
	const char *cmd;
	void (*f)(data *d);
} builtin;



/* shell_builtin.c */
int execute_builtin(data *data)
void exit_builtin(data *d);
void env_builtin(data *d);
void builtin_setenv(data *d);
void unsetenv_builtin(data *d);
/* shell_builtin2.c */
void builtin_change_directory(data *data)

/* shell_utils.c */
void print_string(const char *str)
void deallocate_array(char **array)
void split_string(data *data, const char *delimiter)
void initialize_data(data *data, const char *shell_name)
void read_command(data *data)
/* shell_utils2.c */
void display_error(const char *program_name, const char *error_msg)
void remove_whitespace(char *str_input)
void *resize_memory(void *ptr_input, unsigned int new_size)

/* shell_exec.c */
void launch_process(data *data_struct)
void signal_handler(int signal_num)
void execute_command(data *data_struct)

/* shell_path.c */
char *getenvValue(char *name)
int locateExecutable(data *d)
int setEnv(data *d, char *name, char *value)

/* string_utils.c */
unsigned int stringLength(char *str)
int stringCompare(const char *s1, const char *s2)
int stringCompareN(const char *s1, const char *s2, int n)
char *stringCopy(char *dest, const char *src)
char *stringConcatenate(char *dest, const char *src)

/* string_utils2.c */
char *stringDuplicate(const char *str)
int isNumber(const char *status)
int isDigit(int c)

/* shell_GetLine.c */
#define READ_BUF_SIZE 1024
ssize_t GetLine(char **line, size_t *size, FILE *stream);

#endif
