#include <iostream>
#include <string.h>
#include <cmath>

std::string get_max(std::string array[], int len) {
    std::string max = array[0];
    for (int i = 0; i < len; i++) {
        if (max.length() < array[i].length()) {
            max = array[i];
        }
    }
    return max;
}

void count_sort(std::string array[], int len, int exp) {
    std::string output[len];
    int i;
    int count[52] = { };
    int symb;
 
    for (i = 0; i < len; i++) {
        symb = static_cast<int>(array[i][exp - 1]);
        if (symb <= 90 && symb >= 65) { // при строчных
            symb -= 64;
        } else if (symb < 65) { // при #
            symb -= 10;
        } else {    // при больших
            symb -= 70;
        }
        count[symb - 1]++;   
    }
 
    for (i = 1; i < 52; i++) {
        count[i] += count[i - 1];
    }
 
    for (i = len - 1; i >= 0; i--) {
        symb = static_cast<int>(array[i][exp - 1]);
        if (symb <= 90 && symb >= 65) {   // при строчных
            symb -= 64;
        } else if (symb < 65) { // при #
            symb -= 10;
        } else {    // при больших
            symb -= 70;
        }
        output[count[symb - 1] - 1] = array[i];
        count[symb - 1]--;
    }
 
    for (i = 0; i < len; i++) {
        array[i] = output[i];
    }
}

void razr_sort(std::string array[], int len, int len_max_arr) {

    for (int i = 0; len_max_arr > i; i += 1) {
        int exp = len_max_arr - i;
        count_sort(array, len, exp);
    }
}

void print(std::string array[], int len) {
    for (int i = 0; i < len; i++)
        std::cout << array[i] << " ";
}

void uravnilovka(std::string array[], int len, int len_max_arr) {
    for (int i = 0; i < len ; i++) {
        if (len_max_arr > array[i].length()) {
            int count_symb = len_max_arr - array[i].length();
            array[i].insert(0, count_symb, '#');
        }
    }
}

int main() {
    std::string array[] = {"AAAAxtkTfff", "fff", "gppD", "abaS", "bczZZZDDA", "abc"};

    int len = sizeof(array) / sizeof(array[0]);

    std::string max_arr = get_max(array, len);
    int len_max_arr = max_arr.length();

    uravnilovka(array, len, len_max_arr);
    razr_sort(array, len, len_max_arr);
    print(array, len);

    return 0;

}