#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

template <typename T>
void printVector(std::vector<T>& vec) {
    for (T ch : vec) {
        std::cout << ch;
    }
    std::cout << std::endl;
}

void countingSort(std::vector<char>& array, std::vector<int>& index) {
    char minValue = *std::min_element(array.begin(), array.end());
    char maxValue = *std::max_element(array.begin(), array.end());
    
    int range = maxValue - minValue + 1;
    std::vector<int> count(range, 0);

    for (char ch : array) {
        count[ch - minValue]++;
    }

    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }

    std::vector<char> sortedArray(array.size());
    std::vector<int> sortedIndex(array.size());

    for (int i = array.size() - 1; i >= 0; i--) {
        char ch = array[i];
        int pos = count[ch - minValue] - 1;
        sortedArray[pos] = ch;
        sortedIndex[pos] = index[i];
        count[ch - minValue]--;
    }

    array = sortedArray;
    index = sortedIndex;
}

void suffixArray(std::string& str, std::vector<char>& vec, std::vector<int>& ind, std::vector<int>& eq) {
    int c = 0;

    for (char symb : str) {
        vec.push_back(symb);
        ind.push_back(c);
        c += 1;
    }
    vec.push_back('$');
    ind.push_back(c + 1);

    countingSort(vec, ind);

    c = -1;
    char old_symb;
    for (char symb : vec) {
        if (symb != old_symb) {
            c += 1;
        }
        old_symb = symb;
        eq.push_back(c);
    }
}

int main() {
    std::ifstream file("tests/1.txt");

    if (!file.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл!\n";
        return 1;
    }

    std::string string;
    std::vector<char> vec;
    std::vector<int> ind;
    std::vector<int> eq;

    if (std::getline(file, string)) {
        suffixArray(string, vec, ind, eq);
    }


    printVector(vec);
    printVector(ind);
    printVector(eq);

    file.close();
}