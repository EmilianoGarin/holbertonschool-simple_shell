#include "main.h"

/**
 * free_ar - free all the array
 * @av: array to free
 * Return: nothing
 */
void free_ar(char **av)
{
	int x = 0;

	for (; av[x] != NULL; x++)
		free(av[x]);
	free(av);
}

/**
 * buffer - takes the commands entered by the user
 * Return: returns the address of the memory with commands
 */

char *buffer(void)
{
	char *buff = NULL;
	size_t len = 0;

	fflush(stdin);
	if (getline(&buff, &len, stdin) == -1)
	{
		free(buff);
		return (NULL);
	}
	return (buff);
}


/**
 * split_buff - split the commands entered by the user
 * @buff: commands entered by the user
 * @spliter: string with separator characters
 * Return: returns the address of the array where the partitioned of buff
 */
char **split_buff(char *buff, char *spliter)
{
	int size = 0, posi = 0;
	char **av = NULL;
	char *token = NULL, *cpbuff = strdup(buff);

	if (cpbuff == NULL)
		free(buff), exit(EXIT_FAILURE);
	token = strtok(buff, spliter);
	while (token != NULL)
	{
		size++;
		token = strtok(NULL, spliter);
	}
	if (size == 0)
	{
		free(cpbuff);
		free(buff);
		return (NULL);
	}


	av = malloc(sizeof(char *) * (size + 1));
	if (av == NULL)
		exit(EXIT_FAILURE);

	token = strtok(cpbuff, spliter);
	for (; posi < size; posi++)
	{
		av[posi] = strdup(token);
		if (av[posi] == NULL)
		{
			free_ar(av);
			free(buff);
			exit(EXIT_FAILURE);
		}
		token = strtok(NULL, spliter);
	}
	av[posi] = NULL;
	free(cpbuff);
	return (av);
}
/**
 * split_path - split the addresses in the PATH environment variable
 * Return: returns the address of the array where
 * the partitioned PATH is stored
 */
char **split_path(void)
{
	char *cpubi = NULL, *ubi = _getenv("PATH");
	char **pwd = NULL;
	int i = 0, size = 0;

	if (ubi == NULL)
		exit(EXIT_FAILURE);
	for (i = 0; ubi[i] != '\0'; i++)
		if (ubi[i] == ':')
			size++;

	pwd = malloc(sizeof(char *) * (size + 2));
	if (pwd == NULL)
		exit(EXIT_FAILURE);

	for (i = 0; i < (size + 2); i++)
		pwd[i] = NULL;

	cpubi = strdup(ubi);
	if (cpubi == NULL)
		exit(EXIT_FAILURE);
	free(ubi);
	pwd[0] = strdup(strtok(cpubi, ":"));
	if (pwd[0] == NULL)
	{
		free(pwd);
		exit(EXIT_FAILURE);
	}
	for (i = 1; i < size; i++)
	{
		pwd[i] = strdup(strtok(NULL, ":"));
		if (pwd[i] == NULL)
		{
			free_ar(pwd);
			exit(EXIT_FAILURE);
		}
	}
	free(cpubi);

	return (pwd);
}

/**
 * _getenv - search among the environment variables for the one called "name"
 * @name: name of the environment variable that is prompted
 * Return: returns the address of the memory with the environment variable or
 * NULL if not found
 */

char *_getenv(char *name)
{
	char *path = NULL;
	char **env = environ;
	int t = 0, j, i, name_len = strlen(name), k = 0;

	if (name == NULL)
	{
		free(name);
		fprintf(stderr, "Error: no se pudo asignar memoria\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; env[i] != NULL; i++)
	{
		if (strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
		{
			k = name_len + 1;
			t = strlen(env[i]);

			k = t - (name_len + 1);
			path = (char *) malloc(sizeof(char) * k + 1);
			if (name == NULL)
			{
				free(path);
				fprintf(stderr, "Error: no se pudo asignar memoria\n");
				exit(EXIT_FAILURE);
			}
			j = 0;
			path[j] = '\0';
			for (k = name_len + 1; env[i][k] != '\0'; k++)
			{
				path[j] = env[i][k];
				j++;
			}
			path[j] = '\0';
			return (path);
		}
	}
	return (NULL);
}


