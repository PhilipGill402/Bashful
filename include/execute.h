#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


int shell_cd (char** args);
int shell_help (char** args);
int shell_exit (char** args);

int launch(char** args);
int execute(char** args);
