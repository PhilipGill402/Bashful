#include "input.h"

#define BUF_SIZE 1024

char* read_line(){
    int c;
    char* buffer = malloc(sizeof(char) * BUF_SIZE);
    int position = 0;

    while (1){
        c = getchar();
        if (c == EOF || c == '\n'){
            break;
        }

        if (position == sizeof(buffer)){
            //if buffer fills up, then this adds another 1024 elements to the buffer
            buffer = realloc(buffer, sizeof(buffer) + (sizeof(char) * BUF_SIZE));
        }

         
        buffer[position] = c;
        position++;
    } 
    
    if (position == sizeof(buffer)){
        //if buffer fills up, add one more element for the null terminator
        buffer = realloc(buffer, sizeof(buffer) + sizeof(char));
    }
    
    buffer[position] = '\0';

    return buffer;
}
