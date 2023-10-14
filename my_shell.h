#ifndef MY_SHELL_H
#define MY_SHELL_H

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

/*
This  stores  the prototypes of the inbuilt  elements for the shell 
toem__builtin_elements.c
*/
int exit_shell(shell_info_t *shell_info)
int change_current_directory(info_t *info)
int show_history(info_t *info)
int unset_alias(info_t *info, char *alias)
/this the prototypes pf _built_elementsV2.c/
int define_alias(parameters_t *parameters, char *alias_string)
int display_alias(list_t *alias_node)
int manageAlias(info_t *info)
#endif
