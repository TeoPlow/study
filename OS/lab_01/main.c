#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "sys/wait.h"

#define _R_            "\x1b[31m" 
#define _G_            "\x1b[32m" 
#define RESET_COLOR    "\x1b[0m"  
int create_process();

int main() {
    // Pipe 1
    int pipe_fd[2]; 
    int err = pipe(pipe_fd); 
    if (err == -1) 
    {
        perror("pipe");
        return -1;
    }

    // Pipe 2
    int pipe_fd_2[2]; 
    int err2 = pipe(pipe_fd_2); 
    if (err2 == -1) 
    {
        perror("pipe");
        return -1;
    }

    pid_t pid = create_process();

    if (0 == pid)   // Child
    {
        char child_numbers[128];
        int child_answer;
        read(pipe_fd[0], &child_numbers, sizeof(child_numbers));
        printf(_R_"Child gets '%s'\n", child_numbers);

        // Function (***) 
        child_answer = strlen(child_numbers);

        printf(_R_"Child transform '%s' to '%d'\n", child_numbers, child_answer);

        // Send 'child_answer' to the parent
        write(pipe_fd_2[1], &child_answer, sizeof(child_answer));
        printf(_R_"Child send '%d'\n", child_answer);

        close(pipe_fd[0]);
        close(pipe_fd_2[1]);

    }
    else    // Parent
    {
        char file_name[128];
        fgets(file_name, 128, stdin);
        int pos = strlen(file_name)- 1;
        if ( file_name[pos] == '\n') {
            file_name[pos]='\0';
        }
        FILE* file;
        file = fopen(file_name, "r");
        printf(_G_"Opening file '%s'\n", file_name);
        char numbers[128];
        if (file) {
            fgets(numbers, 128, file);
            printf(_G_"File '%s' opened successfully\n", file_name);
        }

        // Send 'numbers' to the child
        write(pipe_fd[1], &numbers, sizeof(numbers));
        printf(_G_"Parent send '%s'\n", numbers);
        

        wait(NULL);

        // Read 'answer' from the child
        int answer;
        read(pipe_fd_2[0], &answer, sizeof(answer));
        printf(_G_"Parent gets '%d'\n", answer);

        close(pipe_fd[1]);
        close(pipe_fd_2[0]);
    }
    printf(RESET_COLOR);
    return 0;
}

int create_process() {
    pid_t pid = fork();
    if (-1 == pid)
    {
        perror("fork");
        exit(-1);
    }
    return pid;
}