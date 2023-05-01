#include "main.h"

/**
 * exit_127 - exits the program when
 * the program requested by the user is not found
 * @name: current program name
 * @name_p: name of the program requested by the user
 * @av: array to free
 * @split_p: array to free
 * Return: exits with error number 127
 */

void exit_127(char *name, char *name_p, char **av, char **split_p)
{
	fprintf(stderr, "%s: 1: %s: not found\n", name, name_p);
	free_ar(av);
	free_ar(split_p);
	exit(127);
}

/**
 * sig_handler - captures when ctrl + c is entered
 * Return: nothing
 */
void sig_handler(__attribute__((unused)) int signum)
{
	printf("\n");
}

/**
 * main - a simple SHELL
 * @argc: size of argv
 * @argv: array with argument
 * Return: 0 all good, 1 an error occurred and 127 when the program
 * requested by the user is not found
 */

int main(__attribute__((unused)) int argc, char *argv[])
{
	char *buff = NULL;
	char **av = NULL, **split_p = NULL;
	int ac = 0, status = 1;

	signal(SIGINT, sig_handler);
	split_p = split_path();
	do {
		isatty(0) == 1 ? printf("$ ") : 0;

		buff = buffer();
		if (buff == NULL)
		{
			free_ar(split_p);
			exit(EXIT_SUCCESS);
		}
		else
		{
			av = split_buff(buff, " \n\t");
			if (av == NULL)
				continue;
			free(buff);
			if (strchr(av[0], '/') != NULL)
			{
				ac = access(av[0], X_OK);
				if (ac == 0)
					for_exe(av, av[0]);
				else
					exit_127(argv[0], av[0], split_p, av);
			}
			else
				status = find_exe(av, split_p);
			if (status == 2)
				exit_127(argv[0], av[0], split_p, av);
			free_ar(av);
		}
	} while (status);
	free_ar(split_p);
	return (0);
}
