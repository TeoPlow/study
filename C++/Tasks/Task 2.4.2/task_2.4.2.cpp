#include <iostream>

void strcat(char *to, const char *from) {
    int i = 0;
    while (to[i] != '\0') {
        i++;
    }
    for (int j = 0; from[j] != '\0'; j++) {
        to[i+j] = from[j];
    }
}

int strcmp(const char *str1, const char *str2) {
    while (*str1 == *str2 && *str1)
        str1++;
        str2++;
    return *str1 - *str2;
}

int main() {
    // Test 1
    char to1[100] = "Hello, ";
    char from1[100] = "World!";
    strcat(to1, from1);
    if (strcmp(to1, "Hello, World!") == 0)
        std::cout << "Test 1 passed" << std::endl;
    else std::cout << "Test 1 failed" << std::endl;
    // Test 2
    char to2[100] = "Stepik.org";
    char from2[100] = "";
    strcat(to2, from2);
    if (strcmp(to2, "Stepik.org") == 0)
        std::cout << "Test 2 passed" << std::endl;
    else std::cout << "Test 2 failed" << std::endl;
    // Test 3
    char to3[100] = "Apple, or";
    char from3[100] = "ange";
    strcat(to3, from3);
    if (strcmp(to3, "Apple, orange") == 0)
        std::cout << "Test 3 passed" << std::endl;
    else std::cout << "Test 3 failed" << std::endl;
    // Test 4
    char to4[100] = "";
    char from4[100] = "Russian Federation";
    strcat(to4, from4);
    if (strcmp(to4, "Russian Federation") == 0)
        std::cout << "Test 4 passed" << std::endl;
    else std::cout << "Test 4 failed" << std::endl;
    // Test 5
    char to5[100] = "Alexa";
    char from5[100] = "ndr Pushkin";
    strcat(to5, from5);
    if (strcmp(to5, "Alexandr Pushkin") == 0)
        std::cout << "Test 5 passed" << std::endl;
    else std::cout << "Test 5 failed" << std::endl;
    // Test 6
    char to6[100] = "Harry Potter and the";
    char from6[100] = " Prisoner of Azkaban";
    strcat(to6, from6);
    if (strcmp(to6, "Harry Potter and the Prisoner of Azkaban") == 0)
        std::cout << "Test 6 passed" << std::endl;
    else std::cout << "Test 6 failed" << std::endl;
    return 0;
}