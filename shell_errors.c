#include "shell.h"

/**
 * _print_error - prints errors to stdout
 * @pg_name: program name
 * @data: contains program info
 */
void _print_error(data_t *data, char *pg_name)
{
	char process[4];

	num_to_string(process, data->process_no);
	_ewrite(pg_name);
	_ewrite(": ");
	_ewrite(process);
	_ewrite(": ");
	_ewrite(data->cmd_args[0]);
	_ewrite(": not found\n");
}

/**
 * _print_atoi_error - prints errors to stdin
 * @data: contains program info
 * @pg_name: program name
 */
void _print_atoi_error(data_t *data, char *pg_name)
{
	char process[4];

	num_to_string(process, data->process_no);
	_ewrite(pg_name);
	_ewrite(": ");
	_ewrite(process);
	_ewrite(": ");
	_ewrite(data->cmd_args[0]);
	_ewrite(": Illegal number: ");
	_ewrite(data->cmd_args[1]);
	_ewrite("\n");
}
