#ifndef V2_SHELL_H
#define V2_SHELL_H

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

/_envn.c prototypes/
int printCurrentEnvironment(info_t *info)
char *retrieve_environment_variable(info_t *info, const char *name)
int updateEnvironmentVariable(data_t *data)
int unsetEnvironment(data_t *data)
int createEnvList(env_data_t *envData)

/* This are prototypes for readline.c*/
ssize_t readAndBufferInput(data_t *data, char **buffer, size_t *length)
ssize_t processInput(data_t *data)
ssize_t readBuffer(data_t *d, char *b, size_t *n)
void sigintHandler(int sig)
int readLine(data_t *d, char **b, size_t *n)

/this are the prototypes of the envregistry.c/
char **copyEnv(info_t *info)
int unsetEnv(info_t *i, char *v)
int setEnv(info_t *i, char *var, char *value)
 /* this are the prototypes of initinfo.c*/
void resetInfo(info_t *info)
void initInfo(info_t *info, char **av)
void freeRes(info_t *info, int freeAll)

/*this is to store the prototypes of history_handler.c.*/
char *historyFilePath(info_t *info)
int saveHistory(info_t *info)
int _rdhistory(info_t *info)
int add_history_entry(info_t *info, char *entry, int linecount)
int update_history_numbers(info_t *info)
