#include "main.h"
/*:void free_ar(char **av)
{
        int x = 0;

        for (; av[x] != NULL; x++)
                free(av[x]);
        free(av);
}*/
char **_strtok(char *path)
{
        char **cortado;
        int a = 0, i, c = 0, d = 0, l, t = 0, j = 0, len = 0;

        len = strlen(path);
        for (i = 0; path[i]!= '\0'; i++)
        {
                if (path[i] == ':')
                        a++;
        }
        a = a + 2;
        cortado = (char **)malloc(a * sizeof(char *));
        if (cortado == NULL)
                return NULL;
        for (i = 0; i <= len; i++)
        {
                c++;
                if (path[i] == ':' || path[i] == '\0')
                {
                        cortado[d] = (char *)malloc((c) * sizeof(char));
			c = 0;
                        if (cortado[d] == NULL)
                        {
                                free_ar(cortado);
                                exit(0);
                        }
                        d++;
                }
        }
        j = 0;
        t = 0;
        for (l = 0; l < len; l++)
        {
		cortado[t][j] = path[l];
                j++;
                if (path[l] == ':')
                {
                        j = 0;
                        t++;
                }
        }
        j = 0;
        t = 0;
        for (l = 0; l <= len; l++)
        {
                j++;
                if (path[l] == ':' || path[l] == '\0')
                {
                        cortado[t][j - 1] = '\0';
                        t++;
                        j = 0;
                }
        }
        return (cortado);
}
char *_getenv(char *name)
{
      	char **split_path;
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
			path = (char*) malloc(sizeof(char) * k + 1);
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
        return NULL;
}
char **_split_p1(void)
{
        char *ubi = _getenv("PATH");
        char **pwd;
	int i;
	 pwd = _strtok(ubi);
	 free(ubi);
        return (pwd);
}
