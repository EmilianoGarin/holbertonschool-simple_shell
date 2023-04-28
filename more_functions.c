#include "main.h"


/*******************************************************/
int find_exe(char **av, char**pwd)
{
	int ac, i = 0;
	char *token = NULL;

	if (strcmp(av[0], "exit") == 0)
	{
		free_ar(pwd);
		free_ar(av);
		exit(0);
	}
	while ( pwd[i] != NULL)
	{
		token = malloc(strlen(pwd[i]) + strlen(av[0]) + 2);
		if (token == NULL)
		{
			free(pwd);
			return (1);
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
		i++;
		token = NULL;
	}
	return (1);
}

/*******************************************************/

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
		execve(dir, av, NULL);
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

