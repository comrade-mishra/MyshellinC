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

#define LSH_RL_BUFSIZE 1024
char *lsh_read_line(){
    int bufsize = LSH_RL_BUFSIZE, position = 0, c;
    char *buffer = malloc(sizeof(char)*bufsize);

    if (!buffer){
        fprintf(stderr, "Memory Allocation error");
        exit ( EXIT_FAILURE );
    }

    while(1){

        // Read character from stdin
        c = getchar(); // getchar takes input as an unsiogned char and returns an int, it does so as to represent EOF which cannot be done in char type.

        if (c == EOF || c == '\n'){
            buffer[position] = '\0';
        } else{
            buffer[position] = c;
        }
        position++;

        // If we exceed the buffersize, reallocate
       if (position >= bufsize) {
            bufsize += LSH_RL_BUFSIZE;
            buffer = realloc (buffer, bufsize);

            if (!buffer){
                fprintf(stderr, "Memory Allocation error");
                exit(EXIT_FAILURE);
            }
       } 



    }


}

void lsh_loop(){

    char *line;
    char **args;
    int status;

    do{
        printf("> ");
        line = lsh_read_line();
        args = lsh_split_line();
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
