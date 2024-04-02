#include <iostream>
#include <vector>
#include <string>

// Функция для нахождения максимального числа в массиве
unsigned long long getMax(std::vector<std::pair<unsigned long long, int>>& array) {
    unsigned long long max = array[0].first;
    for (int i = 1; i < array.size(); i++) {
        if (array[i].first > max) {
            max = array[i].first;
        }
    }
    return max;
}

// Функция ввода значений из терминала в вектор
void input(std::vector<std::pair<std::string, std::string>>& array) {
    std::string input;
    std::string num;
    std::string key;

    while (std::getline(std::cin, input)) {
        if (input.find('\t') <= input.size()) {
            size_t pos = input.find('\t');
            num = input.substr(0, pos);
            key = input.substr(pos + 1);
        } else {
            num = input.substr(0);
            key = "";
        }

        // Добавляем ключ-значение в вектор
        if (num != "" && key != "") {
            array.push_back(std::make_pair(num, key));
        }
    }
}

// Функция перевода std::string в unsigned long long
unsigned long long to_ull(std::string s) {
    unsigned long long num = 0;
    for (auto elem : s) {
        if (isdigit(elem)) {
            num = num * 10 + (elem - '0');
        }
    }
    return num;
}

// Функция для сортировки массива по указанному разряду
void countSort(std::vector<std::pair<unsigned long long, int>>& array, unsigned long long exp) {
    int n = array.size();
    std::vector<std::pair<unsigned long long, int>> output(n);
    std::vector<int> count(10, 0);

    for (int i = 0; i < n; i++) {
        count[(array[i].first / exp) % 10]++;
    }

    for (unsigned short int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        output[count[(array[i].first / exp) % 10] - 1] = array[i];
        count[(array[i].first / exp) % 10]--;
    }

    for (int i = 0; i < n; i++) {
        array[i] = output[i];
    }
}

// Функция для поразрядной сортировки
void razr_sort(std::vector<std::pair<unsigned long long, int>>& arr) {
    unsigned long long arr_max = getMax(arr);

    for (unsigned long long exp = 1; arr_max / exp > 0; exp *= 10) {
        countSort(arr, exp);
    }
}

int main() {

    // Ускорялка ввода-вывода
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    // Изначальный вектор
    std::vector<std::pair<std::string, std::string>> array;

    // Вводим значения в вектор и проверяем, не пустой ли он
    input(array);
    if (array.empty()) {
        return 0;
    }

    int len = array.size();

    // Дополнительный вектор для сортирвки
    std::vector<std::pair<unsigned long long, int>> arr_to_sort(len);

    // Заполняем дополнительный вектор
    for (int i = 0; i < len; i++) {
        arr_to_sort[i].first = to_ull(array[i].first);
        arr_to_sort[i].second = i;
    }

    // Выполняем поразрядную сортировку
    razr_sort(arr_to_sort);

    // Вывод отсортированного вектора
    for (int i = 0; i < len; i++){
        std::cout << array[arr_to_sort[i].second].first << '\t' << array[arr_to_sort[i].second].second << '\n';
    }
}