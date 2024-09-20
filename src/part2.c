#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "string_parser.h"

void signaler(pid_t* pid_ary, int size, int signal, char* name);

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

    printf("MCP system is now running and will execute commands from your file.\n");

    //declear line_buffer
	size_t len = 128;
	char* line_buf = malloc (len);

    command_line arguments;
    int num_children = 1;
    int max_children = 30;

    // Create an array to store child process PIDs
    pid_t* pid_ary = malloc(max_children * sizeof(pid_t));
    // initialize sigset
	sigset_t sigset;
	char* sig_name = NULL;

    // create an empty sigset_t
	sigemptyset(&sigset);

	// use sigaddset() to add the SIGUSR1 signal to the set
	sigaddset(&sigset, SIGUSR1);
    sigprocmask(SIG_BLOCK, &sigset, NULL);
    
    printf("------------------------------------------------------------------------------\n");
    printf("Creating Child Processes From Your File.\n");

    while (getline (&line_buf, &len, file) != -1)
	{   
        // Remove the trailing newline character if it exists
        size_t line_len = strlen(line_buf);
        if (line_len > 0 && line_buf[line_len - 1] == '\n') {
            line_buf[line_len - 1] = '\0';}
        char *line_copy = strdup(line_buf);
        
        arguments = str_filler (line_copy, " ");
    
        //Create a child process
        pid_t child_pid = fork();
        
        if(child_pid > 0){
            pid_ary[num_children++] = child_pid;
            if (num_children >= max_children - 1) {
                max_children += 10;
                pid_ary = realloc(pid_ary, max_children*sizeof(pid_t));
               
            }
        }else if(child_pid == 0){
            printf("Child Process %d created for line %d, command: %s. (child_pid: %d)\n", num_children, num_children, line_buf, getpid());
            printf("Child Process %d - Waiting for SIGUSR1... (child_pid: %d)\n", num_children, getpid());
            int sig;
            sigwait(&sigset, &sig);
            printf("Child Process %d - Received SIGUSR1 - Calling exec().\n", num_children);
            if(execvp(arguments.command_list[0], arguments.command_list) == -1){
                printf("Failed to execute the command %s from line %d\n", line_buf, num_children);
                exit(-1);
            }
            }else{
            printf("Failed to fork");
            exit(-1);
        }
        
        free(line_copy);
        free_command_line(&arguments);
    }

    // send SIGUSR1
    sig_name = "SIGUSR1";
	signaler(pid_ary, num_children, SIGUSR1, sig_name);
	// send SIGSTOP 
    sig_name = "SIGSTOP";
	signaler(pid_ary, num_children, SIGSTOP, sig_name);
	// send SIGCONT
    sig_name = "SIGCONT";
	signaler(pid_ary, num_children, SIGCONT, sig_name);

    // Wait for all child processes to finish
    for(int i = 1; i < num_children; i++){
        waitpid(pid_ary[i], NULL, 0);
    }

    
    fclose(file);
    free(line_buf);
    free(pid_ary);
    exit(0);
    
}

void signaler(pid_t* pid_ary, int size, int signal, char* name)
{
	sleep(5);
    printf("------------------------------------------------------------------------------\n");
    printf("SEND SIGNAL %s\n", name);

	for(int i = 1; i < size; i++)
	{
		// print: Parent process: <pid> - Sending signal: <signal> to child process: <pid>
		printf("Parent process send %s to child process %d (parent_pid: %d, child_pid: %d)\n", name, i, getpid(), pid_ary[i]);
		// send the signal
		kill(pid_ary[i], signal);
	}
}