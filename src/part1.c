#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "string_parser.h"

int main(int argc, char*argv[]){
    if(argc != 2){
        printf("Please enter a file name!\n");
        exit(1);
    }

    char *filename = argv[1];
    FILE *file = fopen(filename, "r");

    if(file == NULL){
        perror("Error opening file");
        exit(1);
    }

    printf("MCP system is now running and will execute commands from the file.\n");

    //declear line_buffer
	size_t len = 128;
	char* line_buf = malloc (len);

    command_line arguments;
    int line_num = 0;
    int num_children = 0;
    int max_children = 30;

    // Create an array to store child process PIDs
    pid_t* pid_array = malloc(max_children * sizeof(pid_t));

    while (getline (&line_buf, &len, file) != -1)
	{   
        // Remove the trailing newline character if it exists
        size_t line_len = strlen(line_buf);
        if (line_len > 0 && line_buf[line_len - 1] == '\n') {
            line_buf[line_len - 1] = '\0';}
        printf("The MCP is currently running line %d, %s\n", ++line_num, line_buf);
        
        arguments = str_filler (line_buf, " ");
        
        //Create a child process
        pid_t child_pid = fork();
        
        if(child_pid > 0){
            pid_array[num_children++] = child_pid;
            if (num_children >= max_children - 1) {
                max_children += 10;
                pid_array = realloc(pid_array, max_children*sizeof(pid_t));
               
            }
        }else if(child_pid == 0){
            if(execvp(arguments.command_list[0], arguments.command_list) == -1){
                printf("Failed to execute the command from line %d, start with %s\n", line_num, line_buf);
                exit(-1);
            }
        }else{
            printf("Failed to fork");
            exit(-1);
        }
        
        free_command_line(&arguments);
    }

    // Wait for all child processes to finish
    for(int i = 0; i < num_children; i++){
        waitpid(pid_array[i], NULL, 0);
    }

    
    fclose(file);
    free(line_buf);
    free(pid_array);
    exit(0);
    
}