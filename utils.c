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

	while (*str == ' ' && *str != '\n')
		str++;
	if (*str == '\n')
		return (NULL);
	str = strsep(&str, "\n");
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

	if (stat(p, &file_struct) != 0)
		return (NULL);
	pathname = malloc(100 * sizeof(char));
	if (!pathname)
		return (NULL);
	strcpy(pathname, p);
	return (pathname);
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
	char *path_env, pathname[300], *paths, *path = NULL;

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
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
 * break_cmd - spilts a command into arguments
 *
 * @args: array of strings to store arguments
 * @cmd: command to slipt
 * @delim: delimiter characters
 *
 * Return: nothing
 */
int break_cmd(char **args, char *cmd, char *delim)
{
	char *token, *nosp_cmd;
	int i = 0;

	nosp_cmd = trim_string(cmd);
	if (!nosp_cmd)
		return (1);
	token = strtok(nosp_cmd, delim);
	if (!token)
		return (1);
	args[i] = token;
	while ((token = strtok(NULL, delim)))
		args[++i] = token;
	args[++i] = NULL;
	return (0);
}
