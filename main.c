void lsh_loop(){

    char *line;
    char **args;
    int status;

    do{
        print("> ");
        line = lsh_read_line();
        args = lsh_split_line();
        status = lsh_execute(args);

        free(line);
        free(args);


    }while(status)
} 

int main(int argc, char **argv){

    // load configm files if any

    //RUn command loop;
    lsh_loop()

    //Perform shutdown / cleanup


    return EXIT_SUCESS;
}
