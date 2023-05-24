#define _GNU_SOURCE
#include <limits.h>
#include <sys/stat.h>
#include "utils.h"

/**
 * trim_string - trims out whitespace and end of line char from string
 *
 * @str: string to trim
 *
 * Return: address of new string without spaces
 */
char *trim_string(char *str)
{
	char *str_end;

	str = strsep(&str, "\n");
	while (*str == ' ')
		str++;
	str_end = str + strlen(str) - 1;
	while (*str_end == ' ')
		str_end--;
	str_end[1] = '\0';
	return (str);
}

/**
 * check_path - validates a path
 *
 * @p: path to validate
 *
 * Return: pointer to the valid path or NULL if not valid
 */
char *check_path(char *p)
{
	char *pathname;
	struct stat file_struct;

	if (stat(p, &file_struct) == 0)
	{
		pathname = malloc(100 * sizeof(char));
		if (!pathname)
			return (NULL);
		strcpy(pathname, p);
		return (pathname);
	}
	return (NULL);
}

/**
 * find_path - finds the path of a command
 *
 * @cmd: command to find
 *
 * Return: the path of the command executable
 */
char *find_path(char *cmd)
{
	char *path_env, pathname[100], *paths, *path = NULL;

	path_env = getenv("PATH");
	paths = malloc(300 * sizeof(char));
	if (!paths)
		return (NULL);
	path_env = strcpy(paths, path_env);
	while (paths)
	{
		strcpy(pathname, strsep(&paths, ":"));
		strcat(strcat(pathname, "/"), cmd);
		path = check_path(pathname);
		if (path)
			break;
	}
	free(path_env);
	return (path);
}

/**
 * parse_cmd - parses a string into command line format
 *
 * @line: line of commands
 * @args: command line arguments passed
 *
 * Return: array of chars with command and its arguments
 */
char *parse_cmd(char *line, char **args)
{
	char *token = NULL, *path = NULL;
	char *pathdirs, cmd[80];
	int i = 0;

	token = strtok(trim_string(line), " ");
	args[i] = token;
	while ((token = strtok(NULL, " ")))
		args[++i] = trim_string(token);
	args[++i] = NULL;
	strcpy(cmd, args[0]);
	token = strtok(args[0], "/");
	i = 0;
	while ((token = strtok(NULL, "/")))
	{
		pathdirs = token;
		i++;
	}
	if (i)
	{
		path = check_path(cmd);
		args[0] = pathdirs;
	}
	else
		path = find_path(cmd);
	return (path);
}
