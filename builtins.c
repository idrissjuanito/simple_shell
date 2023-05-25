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
	int i = 0;

	if (!trim_string(cmd))
		return (1);
	if (strcmp("exit", cmd) == 0)
		exit(EXIT_SUCCESS);
	if (strcmp("env", cmd) == 0)
	{
		while (environ[i])
		{
			printf("%s\n", environ[i]);
			i++;
		}
		return (1);
	}
	return (0);
}
