#include "utils.h"
/**
 * builtin - checks if a command is built in
 *
 * @cmd: buffer with command and arguments
 * @args: for storing arguments of the command
 * @shell: running shell
 *
 * Return: 1 if builtin and 0 if not
 */
int builtin(char *cmd, char **args, char *shell)
{
	int i = 0;
	int status = 0;
	char *err = "Illegal number";

	if (strcmp("exit", args[0]) == 0)
	{
		if (args[1])
		{
			status = atoi(args[1]);
			if (!status || status < 0)
			{
				fprintf(stderr, "%s: 1: %s: %s: %s\n", shell, args[0], err, args[1]);
				exit(2);
			}
		}
		exit(status);
	}
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
