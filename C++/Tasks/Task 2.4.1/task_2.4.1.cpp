#include <iostream>

unsigned strlen(const char *str) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

int main () {
    std::cout << strlen("sadasdas") << std::endl;
}