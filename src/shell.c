#include "shell.h"

int main(){
    char* line; 
    char** args;
    int status;
    do{
        char cwd[100];
        printf("%s >> ", getcwd(cwd, 100));
        line = read_line();
        args = tokenize(line);
        status = execute(args);
    } while (status > 0);

    free(line);
    free(args);
    return EXIT_SUCCESS;
}
