/* Поразрядная сортировка

Сложность: О(K*(N+M))

Идея:

Сначала сортируем по последней цифре в числе, потом по предпоследней и т.д.

Массив чисел:   [234, 123, 789, 201, 107]

Сорт. по последней цифре:   [201, 123, 234, 107, 789]
Сорт. по предпоследней цифре (устойчивой сортировкой):   [201, 107, 123, 234, 789]
Сорт. по первой цифре (устойчивой сортировкой):   [107, 123, 201, 234, 789]


Как кодить:

1. Подсчитаем, сколько чисел в массиве оканчивается на 1, 2, 3, 4...
    Один - 1, Три - 1, Четыре - 1, Семь - 1, Девять - 1

2. Создаём массив и резервируем место в памяти под все числа, оканчивающиеся на 1, на 2, на 3... 
    [1][3][4][7][9]

3. Записываем в эти ячейки наши числа.
    [201][123][234][107][789]

4. Подсчитаем, сколько чисел в массиве имеют предпоследней цифрой 1, 2, 3, 4...
    Ноль - 2, Два - 1, Три - 1, Восемь - 1

5. Создаём второй массив и резервируем место в памяти под все эти числа
    [0|0][2][3][8]

6. Записываем в эти ячейки наши числа из первого массива во второй.
    [201][107][123][234][789]

И так далее...

*/ 

#include <iostream>

int getMax(int array[], int length) {
    int max = array[0];
    for (int i = 1; i < length; i++) {
        if (max < array[i]) {
            max = array[i];
        }
    }
    return max;
}

void countSort(int array[], int length, int exp) {
    int output[length];
    int i;
    int count[10] = { 0 };
 
    for (i = 0; i < length; i++) {
        count[(array[i] / exp) % 10]++;
    }
 
    for (i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
 
    for (i = length - 1; i >= 0; i--) {
        output[count[(array[i] / exp) % 10] - 1] = array[i];
        count[(array[i] / exp) % 10]--;
    }
 
    for (i = 0; i < length; i++) {
        array[i] = output[i];
    }
}

void razr_sort(int array[], int length) {
    int array_max = getMax(array, length);

    for (int exp = 1; array_max / exp > 0; exp *= 10) {
        countSort(array, length, exp);
    }
}

void print(int array[], int length) {
    for (int i = 0; i < length; i++)
        std::cout << array[i] << " ";
}

int main() {
    int array[] = {12, 234, 1, 782, 13};
    int length = sizeof(array) / sizeof(array[0]);

    razr_sort(array, length);
    print(array, length);

    return 0;
}