#include "main.h"


/**
 * find_exe - filter the input to run the correct command
 * @av: commands entered by the user
 * @pwd: addresses saved in PATH
 * Return: 1 all good and 2 command not found
 */
int find_exe(char **av, char **pwd)
{
	int ac, i = 0;
	char *token = NULL;
	char **envp = NULL;

	if (strcmp(av[0], "exit") == 0)
	{
		free_ar(pwd);
		free_ar(av);
		exit(EXIT_SUCCESS);
	}
	if (strcmp(av[0], "env") == 0)
	{
		envp = environ;
		for (; envp[i] != NULL; i++)
			printf("%s\n", envp[i]);
		return (1);
	}
	for (; pwd[i] != NULL; i++)
	{
		token = malloc(strlen(pwd[i]) + strlen(av[0]) + 2);
		if (token == NULL)
		{
			free(pwd);
			exit(EXIT_FAILURE);
		}
		sprintf(token, "%s/%s", pwd[i], av[0]);
		ac = access(token, X_OK);
		if (ac == 0)
		{
			for_exe(av, token);
			free(token);
			return (1);
		}
		free(token);
		token = NULL;
	}
	return (2);
}

/**
 * for_exe - creates a child process and executes the requested program
 * @av: commands entered by the user
 * @dir: requested program address
 * Return: 1 all good
 */

int for_exe(char **av, char *dir)
{
	pid_t pid = fork();


	if (pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(dir, av, environ);
		perror("execve failed");
		free_ar(av);
		exit(EXIT_FAILURE);

	}
	else
	{
		wait(NULL);
	}
	return (1);
}

