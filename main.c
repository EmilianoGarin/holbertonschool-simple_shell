#include "main.h"
void sig_handler()
{
	printf("received EXIT\n");
}

int main(void)
{
	char *buff = NULL;
	char **av = NULL, **split_p = NULL;
	int ac = 0, status = 1;

	signal(SIGINT, sig_handler);

	split_p = splitpath();

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
					printf("The file '%s' was not found.", av[0]);
			}
			else
				find_exe(av, split_p);
			free_ar(av);
		}
		status = isatty(0);
	} while (status);
	free_ar(split_p);
	return (0);
}
