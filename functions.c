#include "main.h"

/****************************************************************/
void free_ar(char **av)
{
	int x = 0;

	for (; av[x] != NULL; x++)
		free(av[x]);
	free(av);
}

/****************************************************************/

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


/****************************************************************/
char **split_buff(char *buff, char *spliter)
{
	int size = 0, posi = 0;
	char **av = NULL;
	char *token = NULL, *cpbuff = strdup(buff);

	if (cpbuff == NULL)
		exit(0);
	token = strtok(buff, spliter);
	while (token != NULL)
	{
		size++;
		token = strtok(NULL, spliter);
	}
	if (size == 0)
	{
		free(buff);
		free(cpbuff);
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
			exit(0);
		}
		token = strtok(NULL, spliter);
	}
	av[posi] = NULL;
	free(cpbuff);
	return (av);
}

/****************************************************************/

char **splitpath(void)
{
        char *ubi = _getenv("PATH");
        char **pwd = NULL;
        int i = 0, size = 0;

        if (ubi == NULL)
                exit(EXIT_FAILURE);
        for (i = 0; ubi[i] != '\0'; i++)
                if (ubi[i] == ':')
                        size++;

        pwd = malloc(sizeof(char*) * (size + 2));
        if (pwd == NULL)
                exit(0);
        pwd[0] = strdup(strtok(ubi, ":"));

        for (i = 1; i < size; i++)
        {
                pwd[i] = strdup(strtok(NULL, ":"));

        }
        pwd[++i] = NULL;

        return (pwd);
}

/*******************************************************/

char *_getenv(char *name) /** ingresar "PATH" en name*/
{
    char **env = environ;
    int i, name_len = strlen(name);

    for (i = 0; env[i] != NULL; i++) 
    {
        if (strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=') 
	{
            return &env[i][name_len + 1];
        }
    }

    return NULL;
}
