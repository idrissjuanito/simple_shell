#include "utils.h"
#include <errno.h>

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
 * _setenv - sets an environment variable
 *
 * @args: cmd and its arguments if any
 * @shell: running shell for error handling
 *
 * Return: 1 on success
 */
int _setenv(char **args, char *shell)
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
/**
 * _unsetenv - sets an environment variable
 *
 * @args: cmd and its arguments if any
 * @shell: running shell for error handling
 *
 * Return: 1 on success
 */
int _unsetenv(char **args, char *shell)
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
/**
 * change_dir - changes the current working directory
 *
 * @args: command and its arguments
 * @shell: the running shell for errors
 *
 * Return: 1 on success
 */
int change_dir(char **args, char *shell)
{
	char cwdir_buf[PATH_MAX];
	char *dest, *err;

	if (!args[1])
		dest = getenv("HOME");
	else if (strcmp(args[1], "-") == 0)
		dest = getenv("OLDPWD");
	else
		dest = args[1];
	setenv("OLDPWD", getcwd(cwdir_buf, PATH_MAX), 1);
	if (chdir(dest) != 0)
	{
		err = strerror(errno);
		fprintf(stderr, "%s: %s: %s: %s\n", shell, args[0], args[1], err);
		return (1);
	}
	setenv("PWD", getcwd(cwdir_buf, PATH_MAX), 1);
	return (1);
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
		return (_setenv(args, shell));
	if (strcmp("unsetenv", args[0]) ==  0)
		return (_unsetenv(args, shell));
	if (strcmp("cd", args[0]) == 0)
		return (change_dir(args, shell));
	return (0);
}
