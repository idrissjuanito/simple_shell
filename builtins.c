#include "utils.h"
/**
 * builtin - checks if a command is built in
 *
 * @cmd: buffer with command and arguments
 * 
 * Return: 1 if builtin and 0 if not
 */
int builtin(char *cmd)
{
	if (strcmp("exit", cmd) == 0)
		exit(EXIT_SUCCESS);
	return (0);
}
