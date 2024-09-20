#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

template <typename T>
void printVector(std::vector<T>& vec) {
    for (T ch : vec) {
        std::cout << ch.symb;
    }
    std::cout << std::endl;
    for (T ch : vec) {
        std::cout << ch.ind;
    }
    std::cout << std::endl;
    for (T ch : vec) {
        std::cout << ch.eq;
    }
    std::cout << std::endl;
}

struct Symbol {
    char symb;
    int ind;
    int eq;
    int rank[2];
};

bool TEST_cmp(const Symbol &a, const Symbol &b) {
    return (a.rank[0] == b.rank[0]) ? (a.rank[1] < b.rank[1]) : (a.rank[0] < b.rank[0]);
}

std::vector<Symbol> TEST_suffixArray(const std::string &txt) {
    int n = txt.size();
    std::vector<Symbol> suffixes(n);  // Массив для хранения всех суффиксов

    // Инициализируем суффиксы: присваиваем каждому начальный индекс и ранги
    for (int i = 0; i < n; i++) {
        suffixes[i].ind = i;
        suffixes[i].rank[0] = txt[i] - 'a';  // Ранг по первому символу
        suffixes[i].rank[1] = (i + 1 < n) ? (txt[i + 1] - 'a') : -1;  // Ранг по следующему символу
    }

    // Сортируем суффиксы на основе первых 2 символов
    sort(suffixes.begin(), suffixes.end(), TEST_cmp);

    // Массив для хранения индексов суффиксов
    std::vector<int> ind(n);

    // Удваиваем длину префиксов (сначала 2, потом 4, потом 8 и т.д.)
    for (int k = 4; k < 2 * n; k *= 2) {
        // Присваиваем новый ранг и сохраняем предыдущий индекс суффиксов
        int rank = 0;
        int prev_rank = suffixes[0].rank[0];
        suffixes[0].rank[0] = rank;
        ind[suffixes[0].ind] = 0;

        // Присваиваем ранги для суффиксов
        for (int i = 1; i < n; i++) {
            if (suffixes[i].rank[0] == prev_rank && suffixes[i].rank[1] == suffixes[i - 1].rank[1]) {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank;
            } else {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = ++rank;
            }
            ind[suffixes[i].ind] = i;
        }

        // Обновляем ранги для следующих k символов
        for (int i = 0; i < n; i++) {
            int next_index = suffixes[i].ind + k / 2;
            suffixes[i].rank[1] = (next_index < n) ? suffixes[ind[next_index]].rank[0] : -1;
        }

        // Сортируем суффиксы по обновленным рангам
        sort(suffixes.begin(), suffixes.end(), TEST_cmp);
    }

    // Извлекаем индексы суффиксов для суффиксного массива
    std::vector<Symbol> suffix_array(n);
    for (int i = 0; i < n; i++) {
        suffix_array[i].ind = suffixes[i].ind;
    }

    return suffix_array;
}

std::vector<int> buildLCPArray(const std::string &txt, const std::vector<int> &suffix_array) {
    int n = txt.size();
    std::vector<int> lcp(n, 0);
    std::vector<int> inv_suffix(n, 0);  // Массив для хранения обратных индексов суффиксов

    // Строим массив обратных индексов (rank array)
    for (int i = 0; i < n; i++) {
        inv_suffix[suffix_array[i]] = i;
    }

    int k = 0;  // Длина общего префикса
    for (int i = 0; i < n; i++) {
        if (inv_suffix[i] == n - 1) {
            k = 0;
            continue;
        }

        int j = suffix_array[inv_suffix[i] + 1];  // Следующий суффикс в суффиксном массиве

        // Считаем длину общего префикса
        while (i + k < n && j + k < n && txt[i + k] == txt[j + k]) {
            k++;
        }

        lcp[inv_suffix[i]] = k;  // Сохраняем длину общего префикса для данного суффикса

        // Уменьшаем длину общего префикса для следующего суффикса
        if (k > 0) {
            k--;
        }
    }

    return lcp;
}

void countingSort(std::vector<Symbol>& array) {
    char minValue = std::min_element(array.begin(), array.end(), 
        [](const Symbol& a, const Symbol& b) {
            return a.symb < b.symb;
        })->symb;

    char maxValue = std::max_element(array.begin(), array.end(), 
        [](const Symbol& a, const Symbol& b) {
            return a.symb < b.symb;
        })->symb;
    
    int range = maxValue - minValue + 1;
    std::vector<int> count(range, 0);

    for (Symbol ch : array) {
        count[ch.symb - minValue]++;
    }

    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }

    std::vector<Symbol> sortedArray(array.size());

    for (int i = array.size() - 1; i >= 0; i--) {
        char ch = array[i].symb;
        int pos = count[ch - minValue] - 1;
        sortedArray[pos].symb = ch;
        sortedArray[pos].ind = array[i].ind;
        count[ch - minValue]--;
    }

    array = sortedArray;
}

void suffixArray(std::string& str, std::vector<Symbol>& vec) {
    int c = 0;

    // Добавляем строку в вектор + $
    for (char i : str) {
        Symbol symbol;
        symbol.symb = i;
        symbol.ind = c;
        vec.push_back(symbol);
        c += 1;
    }
    Symbol doll;
        doll.symb = '$';
        doll.ind = c;
    vec.push_back(doll);

    // Сортируем вектор посимвольно
    countingSort(vec);

    // Добавляем эквивалентность
    c = -1;
    int j = 0;
    Symbol old_i;
    for (Symbol i : vec) {
        if (i.symb != old_i.symb) {
            c += 1;
        }
        old_i = i;
        vec[j].eq = c;
        j += 1;
    }

    // Отнимаем 1 у индекса по модулю
    // std::vector<Symbol> vec2;
    // for (Symbol i : vec) {
    //     i.ind - 1
    // }
}

std::string searchSubstr(std::string &text, std::string &pattern, std::vector<Symbol> &suff_arr) {
    std::string answer = "";
    std::vector<int> results;
    int n = text.size();
    int m = pattern.size();
    
    // Бинарный поиск для нахождения нижней границы (первого вхождения)
    int low = 0, high = n - 1;
    while (low < high) {
        int mid = (low + high) / 2;
        int start = suff_arr[mid].ind;
        std::string suffix = text.substr(start, std::min(n - start, m));

        if (suffix < pattern) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    // Проверяем, есть ли вхождение
    std::string suffix = text.substr(suff_arr[low].ind, std::min(n - suff_arr[low].ind, m));
    if (suffix != pattern) {
        return answer;  // Подстрока не найдена
    }

    // Находим диапазон всех вхождений (нижняя и верхняя границы)
    int lower = low;
    high = n - 1;
    while (low < high) {
        int mid = (low + high + 1) / 2;
        int start = suff_arr[mid].ind;
        std::string suffix = text.substr(start, std::min(n - start, m));

        if (suffix > pattern) {
            high = mid - 1;
        } else {
            low = mid;
        }
    }

    // Собираем все индексы в диапазоне [lower, low]
    for (int i = low; i >= lower; i--) {
        results.push_back(suff_arr[i].ind);
    }

    for (size_t i = 0; i < results.size(); ++i) {
        answer += std::to_string(results[i] + 1);
        if (i != results.size() - 1) {  // Если это не последний элемент, добавить запятую
            answer += ", ";
        }
    }
    return answer;
}

int main() {
    std::ifstream file("tests/1.txt");

    if (!file.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл!\n";
        return 1;
    }

    int num = 1;
    std::string string;
    std::string text;
    std::vector<Symbol> vec;

    bool flag = false;
    while (std::getline(file, string)) {
        if (flag == false) {
            text = string;
            // suffixArray(string, vec);
            vec = TEST_suffixArray(string);
            flag = true;
        } else {
            std::cout << num << ": " << searchSubstr(text, string, vec) << std::endl;
            num += 1;
        }
        
    }

    file.close();
}