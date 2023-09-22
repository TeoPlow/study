#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#define _R_            "\x1b[31m"
#define RESET_COLOR    "\x1b[0m"

// Function for solving a task
float foo (char * num) {
    // First number
    long num1_l = strtol(num, NULL, 10);
    float answer = (float)num1_l;

    // Another numbers
    float num2 = 0;
    int flag = 0;
    for (int i = 0; i < strlen(num)+1; ++i) {
        if ((flag == 0) && ((num[i] == ' ') | (num[i] == '\0'))) {    // Missed the first number
            flag = 1;
        }
        else if ((flag == 1) && (num[i] != ' ') && (num[i] != '\0')) {    // 100 26
            num2 = num2*10 + ((int)num[i] - 48); 
        }
        else if ((flag == 1) && ((num[i] == ' ') | (num[i] == '\0'))) {
            answer = answer / num2;
            num2 = 0;
        }
    }

    return answer;
}

int main () {
    char child_numbers[128];
    float child_answer;
    read(STDIN_FILENO, child_numbers, 128);
    int pos = strlen(child_numbers)- 1;
    if ( child_numbers[pos] == '\n') {
        child_numbers[pos]='\0';
    }

    child_answer = foo(child_numbers); // Solving a task

    printf("%f", child_answer);

    return 0;
}