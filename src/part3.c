#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "string_parser.h"

void alarm_handler(int signum){
}

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
    int max_children = 30;
    int num_children = 1;

    // Create an array to store child process PIDs
    pid_t* pid_ary = malloc(max_children * sizeof(pid_t));
    sigset_t sigset;
    int sig;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGCONT);
    sigprocmask(SIG_BLOCK, &sigset, NULL);

    signal(SIGALRM, alarm_handler);

    
    printf("------------------------------------------------------------------------------\n");
    printf("Creating Child Processes From Your File.\n");

    while (getline (&line_buf, &len, file) != -1){   
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
            sigwait(&sigset, &sig);
            if(execvp(arguments.command_list[0], arguments.command_list) == -1){
                printf("Failed to execute the command %s from line %d\n", line_buf, num_children);
                exit(0);
            }
        }else{
            printf("Failed to fork");
            exit(-1);
        }
        
        free(line_copy);
        free_command_line(&arguments);
    }

    int* sig_ary = (int *)malloc(num_children * sizeof(int));
    for (int i = 1; i < num_children; i++) {
        sig_ary[i] = 0;
    }

    int check = 1;
    int complete_process = 1;
    while(check){
        for(int i = 1; i < num_children; i++){
            if(sig_ary[i] != 1){
                printf("\nStart child process %d (pid: %d)\n", i, pid_ary[i]);
                kill(pid_ary[i], SIGCONT);
                alarm(3);
                pause();
                printf("Stop child process %d (pid: %d)\n", i, pid_ary[i]);
                kill(pid_ary[i], SIGSTOP);

                int status;
                pid_t result = waitpid(pid_ary[i], &status,WNOHANG);
    
                if(result != 0){
                    complete_process += 1;
                    printf("Child process %d completed (pid: %d)\n", i, pid_ary[i]);
                    sig_ary[i] = 1;
                }
            }
            if(complete_process == num_children){
                printf("All child process completed!\n");
                check = 0;
                break;
            }    
        }
    }

    fclose(file);
    free(sig_ary);
    free(line_buf);
    free(pid_ary);
    return 0;
    
}