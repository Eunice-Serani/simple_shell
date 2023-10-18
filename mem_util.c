#include "my_shell.h"

/**
 * freeAndNull - Deallocates memory associated with a pointer
 *               and sets it to NULL.
 *
 * @ptrAddress: Address of the pointer to deallocate.
 *
 * Return: 1 if memory was deallocated, otherwise 0.
 */
int freeAndNull(void **ptrAddress)
{
	if (ptrAddress && *ptrAddress)
	{
		free(*ptrAddress);
		*ptrAddress = NULL;
		return (1);
	}
	return (0);
}

