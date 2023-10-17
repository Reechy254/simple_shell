#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

void prompt(void);
void to_print(const char *strng);
void read_string(char *strng, size_t size);
void exec_command(const char *strng);

#endif /* SHELL_H */
