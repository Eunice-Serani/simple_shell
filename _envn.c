#include "_v2shell.h"
/**
 * printCurrentEnvironment - Prints the current environment
 * @info: A structure containing potential arguments.
 * Return: Always 0
 */

int printCurrentEnvironment(info_t *info)
{
	printStringList(info->env);
	return (0);
}
/**
 * retrieve_environment_variable - retrieve the value
 * of an environment variable
 * @info: A structure containing potential arguments. Used to maintain
 * @name: The name of the environment variable
 *
 * Return: The value of the environment variable
 */
char *retrieve_environment_variable(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
	p = starts_with(node->str, name);
	if (p && *p)
		return (p);
	node = node->next;
	}
	return (NULL);
}
/**
 * updateEnvironmentVariable - Update the environment variable
 * @data: A structure that might contain the necessary parameters.
 * Return: 0 on success, 1 on failure.
 */
int updateEnvironmentVariable(data_t *data)
{
	if (data->argc != 3)
	{
		_eputs("Invalid number of arguments\n");
		return (1);
	}

	if (_setenv(data, data->argv[1], data->argv[2]))
		return (0);

	return (1);
}
/**
 * unsetEnvironment - Remove environment
 * @data: Structure with relevant arguments.
 * Return: 0 on success, 1 on failure.
 */
int unsetEnvironment(data_t *data)
{
	int i;

	if (data->argc == 1)
	{
		_eputs("Insufficient arguments.\n");
		return (1);
	}

	for (i = 1; i <= data->argc; i++)
	{
		_unsetenv(data, data->argv[i]);
	}

	return (0);
}
/**
 * createEnvList - Create a list of environment
 * with system data
 * @envData: Structure with relevant data.
 * Return: Always 0.
 */
int createEnvList(env_data_t *envData)
{
	list_t *envList = NULL;
	size_t i = 0;

	while (environ[i])
	{
		addNode(&envList, environ[i], 0);
		i++;
	}

	envData->envList = envList;
	return (0);
}
