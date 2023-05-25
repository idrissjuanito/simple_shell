#include "utils.h"

/**
 * builtin_exit - exits process with status
 *
 * @args: the command and its argments
 * @shell: running shell
 *
 * Return: nothing
 */
void builtin_exit(char **args, char *shell)
{
	int status = 0;
	char *err = "Illegal number";

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
/**
 * builtin - checks if a command is built in
 *
 * @args: for storing arguments of the command
 * @shell: running shell
 *
 * Return: 1 if builtin and 0 if not
 */
int builtin(char **args, char *shell)
{
	int i = 0;

	if (strcmp("exit", args[0]) == 0)
		builtin_exit(args, shell);
	if (strcmp("env", args[0]) == 0)
	{
		while (environ[i])
		{
			printf("%s\n", environ[i]);
			i++;
		}
		return (1);
	}
	if (strcmp("setenv", args[0]) == 0)
	{
		if (!args[1] || !args[2])
		{
			fprintf(stderr, "%s: 1: %s: Missing Argument\n", shell, args[0]);
			return (1);
		}
		if (setenv(args[1], args[2], 1) != 0)
			perror(shell);
		return (1);
	}
	if (strcmp("unsetenv", args[0]) ==  0)
	{
		if  (!args[1])
		{
			fprintf(stderr, "%s: 1: %s: Missing Argument\n", shell, args[0]);
			return (1);
		}
		if (unsetenv(args[1]) != 0)
			perror(shell);
		return (1);
	}
	return (0);
}
