#define _GNU_SOURCE
#include <limits.h>
#include <sys/wait.h>
#include "utils.h"

extern char **environ;

/**
 * trim_strin - trims out whitespace and end of line char from string
 *
 * @str: string to trim
 *
 * Return: address of new string without spaces
 */
char *trim_string(char *str)
{
	char *str_end;

	str = strsep(&str,"\n");
	while (*str == ' ')
		str++;
	str_end = str + strlen(str)-1;
	while (*str_end == ' ')
		str_end--;
	str_end[1] = '\0';
	return (str);
}

/**
 * parse_scmd - parse a command with no arguments
 *
 * @line: command to parse
 * @args: arguments pointer
 *
 * Return: pointer to arguments
 */
void parse_scmd(char *line, char **args, char **path)
{
	*path = trim_string(line);
	args[0] = *path;
	args[1] = NULL;
}
/**
 * parse_cmd - parses a string into command line format
 *
 * @line: line of commands
 * @args: command line arguments passed
 * @path: path to the command executable
 *
 * Return: array of chars with command and its arguments
 */
char **parse_cmd(char *line, char **args, char **path)
{
	char *token = NULL;
	char *pathdirs[20];
	char tmp[100];
	int i = 0;

	token = strtok(trim_string(line), " ");
	args[i] = token;
	while ((token = strtok(NULL, " ")))
		args[++i] = trim_string(token);
	args[++i] = NULL;
	strcpy(tmp, args[0]);
	*path = tmp;
	token = strtok(args[0], "/");
	i = 0;
	while ((token = strtok(NULL, "/")))
	{
		pathdirs[i] = token;
		i++;
	}
	if (i)
		args[0] = pathdirs[--i];
	return (args);
}

/**
 * non_interact_shell - run shell in interactive mode
 *
 * @line: address of the command to run
 * @path: path of the command
 * @shell: shell program to run the command
 *
 * Return: nothing
 */
void non_interact_shell(char **line, char *shell)
{
	size_t len = 0;
	ssize_t cread = 0;
	char *args[100], *path;
	char **const envp = environ;
	int status = 0;

	while ((cread = getline(line, &len, stdin)) > 0)
	{
		parse_cmd(*line, args, &path);
		switch (fork())
		{
			case -1:
				exitOnError(shell, args[0]);
				break;
			case 0:
				execve(path, args, envp);
				exitOnError(shell, args[0]);
				break;
			default:
				wait(&status);
				exit(status);
				break;
		}
	}
}

/**
 * interact_shell - run shell in non interactive mode
 *
 * @line: command to run
 * @path: address to hold path of command
 * @shell: shell to program to use
 *
 * Return: nothing
 */
void interact_shell(char **line, char *shell)
{
	size_t len = 0;
	ssize_t cread;
	char *args[100];
	char *path;
	pid_t chid;
	int status = 0;

	while (1)
	{
		printf("($) ");
		cread = getline(line, &len, stdin);
		if (cread <= 0)
		{
			clearerr(stdin);
			fprintf(stderr, "%s: No such Directory\n", shell);
			continue;
		}
		parse_cmd(*line, args, &path);
		chid = fork();
		switch (chid)
		{
			case -1:
				exitOnError(shell, args[0]);
				break;
			case 0:
				execve(path, args, environ);
				exitOnError(shell, args[0]);
				break;
			default:
				wait(&status);
				break;
		}
	}
}
