#include "my_shell.h"
/**
 * my_memset - Fills memory with a specified byte value.
 * @dest: A pointer to the memory area.
 * @value: The byte to be used for filling.
 * @size: The number of bytes to be filled.
 * Return: A pointer to the modified memory area (dest).
 */
char *my_memset(char *dest, char value, unsigned int size)
{
	unsigned int i;

	for (i = 0; i < size; i++)
		dest[i] = value;
	return (dest);
}

/**
 * string_array_free - Frees a string array.
 * @str_array: The string array to be freed.
 */
void string_array_free(char **str_array)
{
	char **temp = str_array;

	if (!str_array)
		return;
	while (*str_array)
		free(*str_array++);
	free(temp);
}

/**
 * my_realloc - Reallocates a block of memory with a new size.
 * @ptr: A pointer to the previously allocated block.
 * @old_size: The size (in bytes) of the old block.
 * @new_size: The size (in bytes) of the new block.
 * Return: A pointer to the reallocated memory block.
 */
void *my_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (new_ptr);
}

