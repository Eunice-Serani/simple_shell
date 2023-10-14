#include "_v2shell.h"
/**
 * resetInfo - Reset info_t fields to defaults.
 * @info: Pointer to info_t struct.
 */
void resetInfo(info_t *info)
{
	info->arguments = info->argumentValues = info->path = NULL;
	info->argumentCount = 0;
}
/**
 * initInfo - Initialize info_t struct.
 * @info: Pointer to info_t structure.
 * @av: Argument vector.
 */
void initInfo(info_t *info, char **av)
{
	info->name = av[0];
	char *arg = info->arg;
	if (arg)
	{
		char **args = (info->args) ? strtow(arg, " \t") : malloc(sizeof(char *) * 2);
		if (args)
		{
			if (!arg) args[0] = _strdup(arg);
			args[1] = NULL;
			info->count = 0;
			while (args && args[info->count]) info->count++;
			replaceAliasesAndVars(info);
		}
	}
}

/**
 * freeRes - Frees allocated resources in the info_t struct.
 * @info: Pointer to the info_t structure.
 * @freeAll: 1 to free all resources, 0 otherwise.
 */
void freeRes(info_t *info, int freeAll)
{
	ffree(info->argv);
	info->argv = info->path = NULL;

	if (freeAll)
	{
		if (!info->cmd_buf) free(info->arg);
		list_t *lists[] = {&(info->env), &(info->history), &(info->alias)};
		for (int i = 0; i < 3; i++)
		{
			freeLst(lists[i]);
		}
		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2) close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
