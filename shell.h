#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#define PROMPT "$ "
#define ERROR_CODE 70
#define MAX_ARGS 20

/**
 * struct data_s - contains program data for easy access
 * @bytes_read: number of bytes read from getline
 * @process_no: process number
 * @buffer_length: length of the buffer read from getline
 * @cmd_args: command arguments
 * @buffer: string that store input from getline
 */
typedef struct data_s
{
	ssize_t bytes_read;
	size_t process_no;
	size_t buffer_length;
	char **cmd_args;
	char *buffer;
} data_t;

#define DATA_INIT           \
	{                       \
		0, 0, 0, NULL, NULL \
	}

extern char **environ;

/* atoi.c */
int _atoi(const char *str);

/* shell_builtins.c */
int is_builtin(data_t *data, char *pg_name);

/* validate.c */
int check_cmd(data_t *data, char **argv);

/* memory.c */
void free_array(char **args);

/* shell_errors.c */
void _print_error(data_t *data, char *pg_name);
void _print_atoi_error(data_t *data, char *pg_name);

/* stdout.c */
int _write(char *str);
int _ewrite(char *err);

/* string.c */
int _strlen(const char *str);
char *_strdup(const char *src);
void num_to_string(char *str, int num);
int _strncmp(char *str1, char *str2, int n);

/* string2.c */
int _strcmp(char *str1, char *str2);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char **split_string(char *buffer, char *split_con);

/* execute.c */
void exec_cmd(data_t *data, char **argv);

/* get_path.c */
char *search_path(char *cmd);

#endif /* SHELL_H */
