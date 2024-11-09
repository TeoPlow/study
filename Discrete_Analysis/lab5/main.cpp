#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <unordered_map>

struct Symbol {
    char symb;
    int ind;
    int eq[2];
};

void printVector(const std::vector<int>& vec) {
    for (int num : vec) {
        std::cout << num;
    }
    std::cout << std::endl;
}

void symbCountingSort(std::vector<Symbol>& arr, char max_symb) {
    max_symb = max_symb;
    int size = arr.size();
    std::vector<int> count(max_symb + 1, 0);
    std::vector<Symbol> output(size);

    for (int i = 0; i < size; i++) {
        count[arr[i].symb]++;
    }

    for (int i = 1; i <= max_symb; i++) {
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        output[count[arr[i].symb] - 1] = arr[i];
        count[arr[i].symb]--;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = output[i];
    }
}

void eqCountingSort(std::vector<Symbol>& arr, int max_eq) {
    int size = arr.size();
    std::vector<int> count(max_eq + 1, 0);
    std::vector<Symbol> output(size);

    for (int i = 0; i < size; i++) {
        count[arr[i].eq[0]]++;
    }

    for (int i = 1; i <= max_eq; i++) {
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        output[count[arr[i].eq[0]] - 1] = arr[i];
        count[arr[i].eq[0]]--;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = output[i];
    }
}

std::vector<int> suffixArray(const std::string &txt) {
    int size = txt.size();
    std::vector<Symbol> text_arr(size);

    // Раставляем индексы
    char max_symb = '$';
    for (int i = 0; i < size; i++) {
        if (i >= size) {
            text_arr[i].symb = '$';
            text_arr[i].ind = i;
        } else {
            if (txt[i] > max_symb) {
                max_symb = txt[i];
            }
            text_arr[i].symb = txt[i];
            text_arr[i].ind = i;
        }
    }

    // Сортируем подсчётом посимвольно
    symbCountingSort(text_arr, max_symb);

    // Добавляем эквиваленты
    char old_symb = '$';
    int eq = 0;
    for (int i = 0; i < size; i++) {
        if (text_arr[i].symb != old_symb) {
            old_symb = text_arr[i].symb;
            eq++;
        }
        text_arr[i].eq[0] = eq;
        text_arr[i].eq[1] = 0;
    }

    // Шараварим
    for (int k = 1; k < size; k *= 2) {

        // Добавялем в словарик индексы и их номер
        std::unordered_map<int, int> map;
        for (int i = 0; i < size; i++) {
            map[text_arr[i].ind] = i;
        }

        // Добавляем эквиваленты
        int old_eq = 0;
        int old_eq2 = text_arr[0].eq[1];
        eq = 0;
        for (int i = 0; i < size; i++) {
            if (text_arr[i].eq[0] != old_eq) {
                old_eq = text_arr[i].eq[0];
                eq++;
            } else {
                if (text_arr[i].eq[1] != old_eq2) {
                    eq++;
                }
            }
            old_eq2 = text_arr[i].eq[1];
            text_arr[i].eq[0] = eq;
            text_arr[i].eq[1] = 0;
        }

        // Отнимаем степень двойки у индексов по модулю
        std::vector<Symbol> temp_text_arr(size);
        for (int i = 0; i < size; i++) {
            temp_text_arr[i] = text_arr[map[(text_arr[i].ind - k + size) % size]];
            temp_text_arr[i].eq[1] = text_arr[i].eq[0];
        }
        for (int i = 0; i < size; i++) {
            text_arr[i] = temp_text_arr[i];
        }

        // Сортируем подсчётом по эквивалентам
        eqCountingSort(text_arr, eq);

        // Проверяем, когда закончить шаравар
        if (eq == (size - 1)) {
            break;
        }
    }

    // Возвращаем суф.массив
    std::vector<int> suff_arr(size);
    for (int i = 0; i < size; i++) {
        suff_arr[i] = text_arr[i].ind;
    }
    return suff_arr;
}

std::string searchSubstr(std::string &text, std::string &pattern, std::vector<int> &suff_arr) {
    std::string answer = "";
    std::vector<int> results;
    int n = suff_arr.size();
    int m = pattern.size();

    if (pattern == "") {
        return answer;
    }
    
    int low = 0, high = n - 1;
    while (low < high) {
        int mid = (low + high) / 2;
        int start = suff_arr[mid];
        std::string suffix = text.substr(start, std::min(n - start, m));

        if (suffix < pattern) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    std::string suffix = text.substr(suff_arr[low], std::min(n - suff_arr[low], m));
    if (suffix != pattern) {
        return answer;
    }

    int lower = low;
    high = n - 1;
    while (low < high) {
        int mid = (low + high + 1) / 2;
        int start = suff_arr[mid];
        std::string suffix = text.substr(start, std::min(n - start, m));

        if (suffix > pattern) {
            high = mid - 1;
        } else {
            low = mid;
        }
    }

    for (int i = low; i >= lower; i--) {
        results.push_back(suff_arr[i]);
    }

    sort(results.begin(), results.end());

    for (size_t i = 0; i < results.size(); ++i) {
        answer += std::to_string(results[i] + 1);
        if (i != results.size() - 1) {
            answer += ", ";
        }
    }
    return answer;
}

int main() {

    std::ifstream file("tests/wrong.txt");

    if (!file.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл!\n";
        return 1;
    }

    int num = 1;
    std::string string;
    std::string text;
    std::vector<int> suff_arr;
    std::string answer;

    bool flag = false;
    while (std::getline(file, string)) {
        if (flag == false) {
            int size = 1;
            int size2 = string.size();
            if (size2 > 0 && (size2 & (size2 - 1)) == 0) {
                string += '$';
            }
            while (size < size2) {
                size *= 2;
            }
            for (int i = 0; i < (size - size2); i++) {
                string += '$';
            }
            
            text = string;
            suff_arr = suffixArray(string);
            printVector(suff_arr);
            flag = true;
        } else {
            answer = searchSubstr(text, string, suff_arr);
            if (answer != "") {
                std::cout << num << ": " << answer << std::endl;
            }
        	num += 1;
        }
        
    }

    file.close();
}