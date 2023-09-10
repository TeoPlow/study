#include <iostream>

void rotate(int * m, unsigned size, int shift) {
    while (shift > 0) {
        for (int i = 0; i < size - 1; ++i) {
            int t = m[i];
            m[i] = m[i + 1];
            m[i + 1] = t;
        }
        shift = shift - 1;
    }
}


int main () {
    unsigned size = 5;
    int shift = 3%size;
    int m[size] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    rotate(m, size, shift);

    for (int i : m) {
        std::cout << i << ' ';
    }

    std::cout << std::endl;
    return 0;
}

// 3 4 5 2 1