#include <iostream>
#include <cmath>

#include "array.h"
#include "figure.h"
#include "trapeze.h"
#include "square.h"
#include "rectangle.h"

int main() {
    bool flag;
    std::string name;
    char answer;
    int i = 0;
    Array q = Array(3);
    std::cout << "Существующие фигуры: square, rectangle, trapeze" << std::endl;

    do {
        do {
            flag = 1;
            std::cout << "Введите название фигуры: " << std::endl;
            std::cin >> name;
            if (name.find("square") == 0) {
                std::cout << "Введите 4 точки X и Y" << std::endl;
                Square* sq = new Square;
                std::cin >> *sq;
                q.add_figure(i, sq);
                
            } else if (name.find("rectangle") == 0) {
                Rectangle rectang;
                std::cout << "Введите 4 точки X и Y" << std::endl;
                Rectangle* rec = new Rectangle;
                std::cin >> *rec;
                q.add_figure(i, rec);

            } else if (name.find("trapeze") == 0) {
                Trapeze trap;
                std::cout << "Введите 4 точки X и Y" << std::endl;
                Trapeze* tr = new Trapeze;
                std::cin >> *tr;
                q.add_figure(i, tr);

            } else {
                std::cout << "Неправильное название, повторите попытку" << std::endl;
                flag = 0;
            }
        } while (flag == 0);
        std::cout << "Хотите добавить ещё одну фигуру? (y/n)" << std::endl;
        std::cin >> answer;
        i += 1;
    } while (answer == 'y' || answer == 'Y');

    /* Проверка на добавление фигур в массив*/
    for(int j = 0; j <= i - 1; j++) {
        const Figure* figur = q[i];
        if (q[j] == nullptr) {
            std::cout << "The figure has been deleted" << std::endl;
        } else {
            std::cout << "Фигура: " << j + 1 << "\n";
            std::cout << "Площадь: " << figur->area() << std::endl;
            std::cout << "Центр: " << figur->center().first << ' ' << figur->center().second << std::endl;
        }
    }
    return 0;
}