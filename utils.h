#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
char **parse_cmd(char *line, char **args, char **path);
void interact_shell(char **line, char *shell);
void non_interact_shell(char **line, char *shell);
void exitOnError(char *shell, char *cmd);
#endif
