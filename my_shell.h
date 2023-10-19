#ifndef _MY_SHELL_H_
#define _MY_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Constants for read/write buffers */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/* Constants for command chaining */
#define COMMAND_NORMAL	0
#define COMMAND_OR		1
#define COMMAND_AND		2
#define COMMAND_CHAIN	3

/* Constants for convert_number() */
#define CONVERT_TO_LOWERCASE	1
#define CONVERT_TO_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0


/*
@data: Data structure.
@str: Alias string to remove
@node: Alias node to print.
@info: Structure containing potential arguments.
@var: Environment variable to set
@value: Value to assign to the environment variable.
@head: A pointer to the head node.
@num: The node index used for history.
@h: A pointer to the first node
@index: The index of the node to delete.
@head_ptr: A pointer to the head node.
@pathStr: The PATH string.
@start: Starting index.
@stop: Stopping index
@command: The command to find.
@i: Argument structure
@v: Variable to delete.
@value: Value of the variable.
@c: The character to print
@fd: The file descriptor to write to
@s: The string to be converted
@error_str: String containing the specific error type
@base: The base for conversion
@flags: Flags for formatting
@buffer: Address of the string to modify
@av: argument vector
@all: true if freeing all fields
@character: The character to check.
@delimiter: The delimiter string.
@c: The character to check
@s: The string to be converted.
@dest: A pointer to the memory area.
@value: The byte to be used for filling.
@size: The number of bytes to be filled.
@str_array: The string array to be freed.
@ptr: A pointer to the previously allocated block.
@old_size: The size (in bytes) of the old block.
@new_size: The size (in bytes) of the new block.
@ptrAddress: Address of the pointer to deallocate
@buf: address of buffer
@len: address of len var
@i: size
@length: size of preallocated ptr buffer if not NUL
@ptr: address of pointer to buffer, preallocated or NULL
@sig_num: the signal number
@s: String to measure.
@s1: First string.
@s2: Second string.
@h: String to search.
@n: Substring to find.
@d: Destination buffer.
@s: Source buffer.
*/

/*
This  stores  the prototypes of the inbuilt  elements for the shell
_builtin_elements.c
*/
int my_exit(info_t *info)
int my_cd(info_t *info)
int _help(info_t *info)

/*this the prototypes pf _built_elementsV2.c*/
int history(info_t *data)
int remove_alias(info_t *data, char *str)
int set_alias(info_t *data, char *str)
int print_alias(list_t *node)
int alias_command(info_t *data)
/* this is the prototypes for _envn.c*/
char **get_environment(info_t *info)
int unset_environment_var(info_t *info, char *var)
int set_environment_var(info_t *info, char *var, char *value)
/*this the prototypes for alist.c*/
list_t *add_node_at_start(list_t **head, const char *str, int num)
list_t *add_node_at_end(list_t **head, const char *str, int num)
size_t print_list_strings(const list_t *h)
int delete_node_at_index(list_t **head, unsigned int index)
void free_entire_list(list_t **head_ptr)
/*this are prototypes for alist2.c*/
size_t calculate_list_length(const list_t *h)
char **convert_list_to_string_array(list_t *head)
size_t display_list_elements(const list_t *h)
list_t *find_node_with_prefix(list_t *node, char *prefix, char c)
ssize_t find_node_position(list_t *head, list_t *node)

/* this is the prototypes for data_parser.c*/
int isExecutableCommand(info_t *info, char *path)
char *duplicateSubstring(char *pathStr, int start, int stop)
char *findCommandInPath(info_t *info, char *pathStr, char *command)

/* this is the prototypes for envregistry.c */
char **copyEnv(info_t *info)
int unsetEnv(info_t *i, char *v)
int setEnv(info_t *i, char *var, char *value)
/* this is the prototypes for error_ops.c */
void print_to_stderr(char *str)
int write_char_to_stderr(char c)
int write_char_to_fd(char c, int fd)
int print_string_to_fd(char *str, int fd)

/* this is the prototypes for error_ops2.c */
int string_to_int(char *s)
void print_error_message(info_t *info, char *error_str)
int print_integer(int input, int fd)
char *convert_to_string(long int num, int base, int flags)
void remove_comment(char *buffer)
/*this are the prototypes for initinfo.c */
void resetInfo(info_t *info)
void initInfo(info_t *info, char **av)
void freeRes(info_t *info, int all)

/* this is the prototypes for ishell.c */
int is_interactive(info_t *info)
int is_delimiter(char character, char *delimiter)
int is_alphabetic(int c)
int string_to_integer(char *s)
/* this is the prototype for mainsh.c*/
int shell_loop(info_t *info, char **av)
int find_builtin_command(info_t *info)
void find_executable_command(info_t *info)
void fork_executable_command(info_t *info)
/* this is the prototype for mem_extend.c*/
char *my_memset(char *dest, char value, unsigned int size)
void string_array_free(char **str_array)
void *my_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
/* this the prototype for mem_util.c*/
int freeAndNull(void **ptrAddress)
/* this is the prototypes readline.c */
ssize_t _buf(info_t *info, char **buf, size_t *len)
ssize_t _input(info_t *info)
ssize_t readbuf(info_t *info, char *buf, size_t *i)
int readline(info_t *info, char **ptr, size_t *length)
void sigintHandler(__attribute__((unused))int sig_num)
/*this are the prototypes of str_ops.c */
int my_strlen(char *s)
int my_strcmp(char *s1, char *s2)
char *starts_with(const char *h, const char *n)
char *my_strcat(char *d, char *s)
/* this is the prototypes for str_ops2.c */
char *my_copy_string(char *destination, char *source)
char *my_string_duplicate(const char *str)
void my_print_string(char *str)
int my_putchar(char c)
/*this are the prototypes of  str_util.c*/
char *my_copy_string(char *destination, char *source, int max_chars)
char *my_concatenate_strings(char *first, char *second, int max_bytes)
char *my_find_character(char *input_string, char target_character)

/* this is the prototypes for  strtoken.c*/
char **split_string(char *str, char *d)
char **split_string_by_char(char *str, char d)

/* this is the prototypes for  var_ops.c*/
int is_chain_delimiter(info_t *info, char *buf, size_t *p)
void check_chain_cont(info_t *info, char *buf, size_t *p, size_t i, size_t len)
int handle_aliases(info_t *info)
int handle_variables(info_t *info)
int update_string(char **old, char *new)
#endif
