#include "utils.h"

/*exit_func_t *exit_function[10];*/
/**
 * handle_exit - runs when the exit function is called
 *
 * @status: status sent by exit function
 * @line: memory address to be freed
 *
 * Return: nothing
 */
void handle_exit(int status, void *line)
{
	if (status >= 0)
		free(*(char **)line);
}
