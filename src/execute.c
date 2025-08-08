#include "execute.h"

char* builtin_str[] = {
    "cd",
    "help",
    "exit"
};

int (*builtin_functions[]) (char**) = {
    &shell_cd,
    &shell_help,
    &shell_exit
};

int shell_cd(char** args){
    if (args[1] == NULL){
        fprintf(stderr, "'cd' requires 1 argument, none were given\n");
        return -1;
    } 

    int status = chdir(args[1]);

    if (status < 0){
        fprintf(stderr, "shell ran into an error when trying to run 'cd'\n");
        return -1;
    }

    return 1;
}

int shell_help(char** args){
    printf("Bashful - Built-in Commands:\n");
    
    int num_builtin_functions = sizeof(builtin_functions) / sizeof(builtin_functions[0]);
    for (int i = 0; i < num_builtin_functions; i++){
        printf("    %s\n", builtin_str[i]);
    }

    printf("Use man <command> for information on external commands.\n");
    
    return 1;
}

int shell_exit(char** args){
    return 0;
}



int launch(char** args){ 
    pid_t pid = fork();
    int child_status;
    int parent_status;

    //child process
    if (pid == 0){
        child_status = execvp(args[0], args);
        if (child_status == -1){
            fprintf(stderr, "shell failed to run %s command\n", args[0]);
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0){
        fprintf(stderr, "shell failed to fork %s\n", args[0]);
        exit(EXIT_FAILURE);
    } else {
        //parent process
        waitpid(pid, &parent_status, 0);
        
        if (!WIFEXITED(parent_status)){
            fprintf(stderr, "shell failed to run %s command\n", args[0]);
            return -1;
        }
    }

    return 1;
}

int execute(char** args){
    if (args[0] == NULL){
        return 1;
    }
    
    int num_builtin_functions = sizeof(builtin_functions) / sizeof(builtin_functions[0]);
    char* cmd = args[0];
   
    //checks if the command is a builtin function
    for (int i = 0; i < num_builtin_functions; i++){
        if (strcmp(builtin_str[i], cmd) == 0){
            return builtin_functions[i](args);
        }
    }

    return launch(args);
}
