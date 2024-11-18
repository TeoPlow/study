#include <iostream>
#include <string>


const short MAX_SIZE = 100;

void baseSollutions(unsigned long long array[][MAX_SIZE], std::string &str) {
    for(int i = 0; i < str.size(); ++i) {
        int j = i;
        array[i][j] = 1;
        if(i != str.size() - 1) {
            array[i][j + 1] = 2;
            if (str[i] == str[i + 1]) {
                array[i][j + 1] = 3;
            }
        }
    }
}

void dynamicProg(unsigned long long array[][MAX_SIZE], std::string &str) {
    for (int len = 2; len < str.size(); len++) {
        for (int i = 0; i + len < str.size(); i++) {
            int j = i + len;
            if (str[i] == str[j]) {
                array[i][j] = array[i + 1][j] + array[i][j - 1] + 1;
            } else {
                array[i][j] = array[i + 1][j] + array[i][j - 1] - array[i + 1][j - 1];
            }
        }
    }
}

int main() {
    std::string input_str;
    std::cin >> input_str;

    unsigned long long count_subpalindroms[MAX_SIZE][MAX_SIZE];

    baseSollutions(count_subpalindroms, input_str);

    dynamicProg(count_subpalindroms, input_str);

    std::cout << count_subpalindroms[0][input_str.size() - 1] << "\n";

    return 0;
}