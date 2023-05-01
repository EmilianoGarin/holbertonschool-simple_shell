#ifndef _SHELL_
#define _SHELL_

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include<signal.h>
#include <sys/wait.h>

extern char **environ;

/* main.c */
void exit_127(char *name, char *name_p, char **av, char **split_p);

/* functions.c */
void free_ar(char **av);
char *buffer(void);
char **split_buff(char *buff, char *spliter);
char **split_path();
char *_getenv(char *name);

/* more_functions.c */
int find_exe(char **av, char **pwd);
int for_exe(char **av, char *dir);

#endif
