#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "sys/wait.h"

#define _G_            "\x1b[32m" 
#define RESET_COLOR    "\x1b[0m"  

int create_process() {
    pid_t pid = fork();
    if (-1 == pid)
    {
        perror("fork");
        exit(-1);
    }
    return pid;
}

int main(int argc, char *argv[]) {
    
    int fd[2]; // parent -> child
    if (pipe(fd) == -1) {
        perror("Pipe wasn't created\n");
    }
    int fd2[2]; // child -> parent
    if (pipe(fd2) == -1) {
        perror("Pipe wasn't created\n");
    }

    pid_t pid = create_process();

    if (0 == pid)   // Child
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);

        close(fd[0]);
        dup2(fd2[1], STDOUT_FILENO);

        execvp("./child", argv);
    }
    else    // Parent
    {
        // Enter file path
        printf(_G_"Enter the path to the file\n");
        printf(RESET_COLOR);
        char file_name[128];
        fgets(file_name, 128, stdin);
        int pos = strlen(file_name)- 1;
        if ( file_name[pos] == '\n') {
            file_name[pos]='\0';
        }

        // Open the file
        FILE* file;
        file = fopen(file_name, "r");
        char numbers[128];
        if (file) {
            fgets(numbers, 128, file);
            printf(_G_"The file opened successfully\n");
        }
        else {
            printf(_G_"The file did\'t open\n");
        }

        // Send 'numbers' to the child
        close(fd[0]);
        write(fd[1], numbers, sizeof(numbers));
        printf(_G_"Parent send '%s'\n", numbers);
        close(fd[1]);

        waitpid(pid, NULL, WUNTRACED);

        // Read 'answer' from the child
        close(fd2[1]);
        char answer;
        read(fd2[0], answer, sizeof(answer));
        printf(_G_"Parent gets '%s'\n", answer);

        close(fd2[0]);
    }
    printf(RESET_COLOR);
    return 0;
}