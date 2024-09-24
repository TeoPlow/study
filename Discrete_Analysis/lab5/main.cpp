#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

struct Symbol {
    char symb;
    int ind;
    int eq[2];
};

bool sort_key(const Symbol &a, const Symbol &b) {
    return (a.eq[0] == b.eq[0]) ? (a.eq[1] < b.eq[1]) : (a.eq[0] < b.eq[0]);
}

std::vector<Symbol> suffixArray(const std::string &txt) {
    int n = txt.size();
    std::vector<Symbol> suff(n);

    for (int i = 0; i < n; i++) {
        suff[i].ind = i;
        suff[i].eq[0] = txt[i] - 'a';
        suff[i].eq[1] = (i + 1 < n) ? (txt[i + 1] - 'a') : -1;
    }

    sort(suff.begin(), suff.end(), sort_key);

    std::vector<int> ind(n);

    for (int k = 4; k < 2 * n; k *= 2) {
        int eq = 0;
        int prev_eq = suff[0].eq[0];
        suff[0].eq[0] = eq;
        ind[suff[0].ind] = 0;

        for (int i = 1; i < n; i++) {
            if (suff[i].eq[0] == prev_eq && suff[i].eq[1] == suff[i - 1].eq[1]) {
                prev_eq = suff[i].eq[0];
                suff[i].eq[0] = eq;
            } else {
                prev_eq = suff[i].eq[0];
                suff[i].eq[0] = ++eq;
            }
            ind[suff[i].ind] = i;
        }

        for (int i = 0; i < n; i++) {
            int next_index = suff[i].ind + k / 2;
            suff[i].eq[1] = (next_index < n) ? suff[ind[next_index]].eq[0] : -1;
        }

        sort(suff.begin(), suff.end(), sort_key);
    }

    std::vector<Symbol> suffix_array(n);
    for (int i = 0; i < n; i++) {
        suffix_array[i].ind = suff[i].ind;
    }

    return suffix_array;
}

std::string searchSubstr(std::string &text, std::string &pattern, std::vector<Symbol> &suff_arr) {
    std::string answer = "";
    std::vector<int> results;
    int n = text.size();
    int m = pattern.size();

    if (pattern == "") {
        return answer;
    }
    
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

    std::string suffix = text.substr(suff_arr[low].ind, std::min(n - suff_arr[low].ind, m));
    if (suffix != pattern) {
        return answer;
    }

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

    for (int i = low; i >= lower; i--) {
        results.push_back(suff_arr[i].ind);
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
    std::ifstream file("tests/1000.txt");

    if (!file.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл!\n";
        return 1;
    }

    int num = 1;
    std::string string;
    std::string text;
    std::vector<Symbol> vec;
    std::string answer;

    bool flag = false;
    while (std::getline(file, string)) {
        if (flag == false) {
            text = string;
            vec = suffixArray(string);
            flag = true;
        } else {
            answer = searchSubstr(text, string, vec);
            if (answer != "") {
                std::cout << num << ": " << searchSubstr(text, string, vec) << std::endl;
            }
        	num += 1;
        }
        
    }

    file.close();
}