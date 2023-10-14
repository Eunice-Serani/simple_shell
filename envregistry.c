#include "_v2shell.h"

/**
 * copyEnv - Copy environment variables.
 * @info: Argument structure.
 *
 * Return: Pointer to the environment variables.
 */
char **copyEnv(info_t *info)
{
       	if (!info->environ || info->env_changed)
	{
		info->environ = listToStrings(info->env);
		info->env_changed = 0;
	}
	return info->environ;
}

/**
 * unsetEnv - Delete an environment variable.
 * @i: Argument structure.
 * @v: Variable to delete.
 *
 * Return: 1 if successfully deleted, 0 otherwise.
 */
int unsetEnv(info_t *i, char *v)
{
	list_t *n = i->env;
	char *p;

	if (!n || !v)
		return 0;

	for (size_t j = 0; n; j++)
	{
		p = startsWith(n->str, v);
		if (p && *p == '=')
		{
			i->env_changed = deleteNodeAtIndex(&(i->env), j);
			j = -1;  // Reset j for the next iteration
			n = i->env;
		}
		n = n->next;
	}
	return i->env_changed;
}
/**
 * setEnv - Add or update an environment variable.
 * @i: Argument structure.
 * @var: Name of the variable.
 * @value: Value of the variable.
 *
 * Return: 0 on success, 1 on failure.
 */
int setEnv(info_t *i, char *var, char *value)
{
	char *buf = NULL, *p;

	if (!var || !value)
		return 1;

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return 1;

	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);

	for (list_t *node = i->env; node; node = node->next)
	{
		p = startsWith(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			i->env_changed = 1;
			return 0;
		}
	}

	addNodeEnd(i->env, buf, 0);
	free(buf);
	i->env_changed = 1;
	return 0;
}
