#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono> // Для измерения времени
#define fast_io std::ios::sync_with_stdio(false); std::cin.tie(0); std::cout.tie(0) // Ускорялка

std::vector<int> z_function (std::string s) {
	int n = (int) s.length();
	std::vector<int> z (n);
	for (int i=1, l=0, r=0; i<n; ++i) {
		if (i <= r)
			z[i] = std::min(r-i+1, z[i-l]);
		while (i+z[i] < n && s[z[i]] == s[i+z[i]])
			++z[i];
		if (i+z[i]-1 > r)
			l = i,  r = i+z[i]-1;
	}
	return z;
}

void find (std::string &text, std::string &sample) {
    std::string concat = sample + '^' + text;
	std::vector<int> z = z_function(concat);
	int sample_len = sample.length();
    for (int i = 0; i < z.size(); ++i) {
        if (z[i] == sample_len) {
            std::cout << i - sample_len - 1 << std::endl;
        }
    }
}

int main () {
	fast_io;
    std::string text;
    std::string sample;
    
    std::ifstream input_file("tests/10000000.txt"); // Открытие файла для чтения
    if (!input_file.is_open()) {
        std::cerr << "Failed to open input file." << std::endl;
        return 1;
    }

    std::getline(input_file, text);
    std::getline(input_file, sample);
    input_file.close(); // Закрытие файла

    auto start = std::chrono::high_resolution_clock::now(); // Начало замера времени

    //find(text, sample);

    auto end = std::chrono::high_resolution_clock::now(); // Конец замера времени
    std::chrono::duration<double> duration = end - start; // Расчет продолжительности

    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

	return 0;
}