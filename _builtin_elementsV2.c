#include "myshell.h"
/**
 * define_alias - Define an alias within the shell.
 * @parameters: A structure holding relevant information.
 * @alias_string: The string to be defined as an alias.
 *
 * Returns: 0 upon success, 1 on error.
 */
int define_alias(parameters_t *parameters, char *alias_string)
{
    char *equal_position = _find_char(alias_string, '=');
    if (!equal_position) return 1;
    if (!*++equal_position) return forget_alias(parameters, alias_string);
    forget_alias(parameters, alias_string);
    return (append_to_aliases(&(parameters->aliases), alias_string, 0) == NULL);
}
/**
 * display_alias - Display an alias string.
 * @alias_node: The alias node containing the string to be displayed.
 *
 * Return: 0 on success, 1 on error.
 */
int display_alias(list_t *alias_node)
{
    char *equal_sign = NULL, *alias_str = NULL;

    if (alias_node) {
        equal_sign = _strchr(alias_node->str, '=');
        for (alias_str = alias_node->str; alias_str <= equal_sign; alias_str++)
            _putchar(*alias_str);
        _putchar('\'');
        _puts(equal_sign + 1);
        _puts("'\n");
        return 0;
    }
    return 1;
}
/**
 * Manage alias settings, similar to the 'alias' command.
 *
 * @param info A structure containing potential arguments.
 *
 * @return Always 0.
 */
int manageAlias(info_t *info)
{
    char *equalSign;
    int i = 0;
    list_t *node = NULL;

    if (info->argc == 1)
    {
        // Display all aliases
        node = info->alias;
        while (node)
        {
            displayAlias(node);
            node = node->next;
        }
        return 0;
    }

    for (i = 1; info->argv[i]; i++)
    {
        equalSign = _strchr(info->argv[i], '=');
        if (equalSign)
            setAlias(info, info->argv[i]);
        else
            displayAlias(nodeStartsWith(info->alias, info->argv[i], '='));
    }

    return 0;
}
