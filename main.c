#include <sys/wait.h>
// waitpid() and associated macros

#include <unistd.h>
//chdir()
//fork()
//exec()
//pid_t
#include <stdlib.h>
//malloc()
//realloc()
//free()
//exit()
//execvp()
//EXIT_SUCCESS, EXIT_FAILUIRE
#include <stdio.h>
// fprintf
// printf()
// stderr
// getcharr()
// perror()
#include <string.h>
// strcmp()
// strtok()

#define LSH_LINE_BUFFER 1024
char *lsh_read_line(){
    int bufsize = LSH_LINE_BUFFER;
    int position = 0;
    int c;
    char *buffer = malloc(sizeof(char)*bufsize);

    if(!buffer){
        fprintf(stderr, "Memory allocation error \n");
        exit(EXIT_FAILURE);
    }

    while(1){
        c = getchar();
        // getchar takes inputn as an unsigned char and cats it to int, in order to represent EOF;
        if (c == EOF || c == '\n'){
            buffer[position] = '\0';
            return buffer;
        }else{
            buffer[position] = c;
        }
        position++;

        // If the command exceeds bufsize, we reallocate
        if ( position >= bufsize ){
            bufsize += LSH_LINE_BUFFER;
            buffer = realloc(buffer, bufsize);

            if (!buffer){
                fprintf(stderr, "Memory Allocation error \n");
                exit (EXIT_FAILURE);
            }

        }


    }

}

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\n\r\a"
char **lsh_split_line(char *line){
    int bufsize = LSH_TOK_BUFSIZE;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens){
        fprintf(stderr, "Memory allocation error \n");
        exit (EXIT_FAILURE);
    }

    token = strtok(line, LSH_TOK_DELIM);
    while (token != NULL){
        tokens[position] = token;
        position++;

        if (position >= bufsize){
            bufsize += LSH_TOK_BUFSIZE;
            tokens = realloc (tokens, bufsize * sizeof(char*));

            if (!tokens){
                fprintf(stderr, "Memory Allocation error \n");
                exit (EXIT_FAILURE);
            }
                
        }
        token = strtok(NULL, LSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;

}


void lsh_loop(){

    char *line;
    char **args;
    int status;

    do{
        printf("> ");
        line = lsh_read_line();
        args = lsh_split_line(line);
        status = lsh_execute(args);

        free(line);
        free(args);


    }while(status);
} 

int main(int argc, char **argv){

    // load configm files if any

    //RUn command loop;
    lsh_loop();

    //Perform shutdown / cleanup


    return EXIT_SUCCESS;
}
