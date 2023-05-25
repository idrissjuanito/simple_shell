#include <errno.h>
#include "utils.h"
/**
 * exitOnError - exits the current process in case of error
 *
 * @shell: the running shell
 * @cmd: command typed
 *
 * Return: nothing
 */
void exitOnError(char *shell, char *cmd)
{
	if (cmd)
		fprintf(stderr, "%s: %s\n", shell, strerror(errno));
	exit_(EXIT_FAILURE);
}
