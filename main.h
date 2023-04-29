#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include<signal.h>
#include <sys/wait.h>

extern char **environ;

char *buffer(void);
char **split_buff(char *buff, char *spliter);
int for_exe(char **av, char *dir);
char **splitpath();
int find_exe(char **av, char**pwd);
void free_ar(char ** av);
char *_getenv(char *name);
char **_split_p1(void);
char **_strtok(char *path);
