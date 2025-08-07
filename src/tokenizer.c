#include "tokenizer.h"

#define TOK_SIZE 64

struct Lexer {
    char* curr_token;
    int curr_token_len;
    char** tokens;
    int position;
    int num_tokens;
    char c;
};

void advance(struct Lexer* lexer, char* line){ 
    lexer->curr_token[lexer->curr_token_len] = lexer->c;
    lexer->curr_token_len++;
    lexer->position++;  
    lexer->c = line[lexer->position];
    //printf("%c\n", lexer->c);
}

void add_token(struct Lexer* lexer){
    lexer->tokens[lexer->num_tokens] = strdup(lexer->curr_token);
    lexer->curr_token_len = 0;
    lexer->num_tokens++;
    free(lexer->curr_token);
    lexer->curr_token = malloc(sizeof(char) * TOK_SIZE);
}

char** tokenize(char* line){
    struct Lexer lexer = {
        .curr_token = malloc(sizeof(char) * TOK_SIZE), 
        .curr_token_len = 0, 
        .tokens = malloc(sizeof(char*) * TOK_SIZE),
        .position = 0,
        .num_tokens = 0,
        .c = line[0]
    };  
    

    while(lexer.c != '\0'){ 
        if (lexer.c == '"'){
            advance(&lexer, line); 
            while (lexer.c != '"' && lexer.c != '\0'){
                advance(&lexer, line);    
            }
            
            if (lexer.c == '"'){
                advance(&lexer, line);
            }

            add_token(&lexer);
        } else if (isspace(lexer.c)) {
            while (isspace(lexer.c)){
                lexer.position++;
                lexer.c = line[lexer.position];     
            } 
        } else {
            advance(&lexer, line);
            while (lexer.c != ' ' && lexer.c != '\0'){
                advance(&lexer, line);
            }
            add_token(&lexer);
        }

    }
    
    free(lexer.curr_token);    

    return lexer.tokens;
}
