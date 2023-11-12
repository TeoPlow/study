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
    int fig1, fig2;
    char answer;
    int i = 0;
    Array q = Array(3);
    std::cout << "(Вводите точки так: 0 0, 1 0, 0 1, 1 1)" << std::endl;
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


    for(int j = 0; j < i; j++) {
        const Figure* figur = q[j];
        std::cout << "Фигура: " << j + 1 << "\n";
        std::cout << "Площадь: " << figur->area() << std::endl;
        std::cout << "Центр: " << figur->center().first << ' ' << figur->center().second << std::endl;
        std::cout << std::endl;
    }

    do {
        std::cout << std::endl;
        std::cout << "Что желаете сделать с фигурами?" << std::endl;
        std::cout << "Функции: delete, total_area, getInfo, end" << std::endl;
        std::cin >> name;

        if (name.find("delete") == 0) {
            std::cout << "Какую фигуру удалить?" << std::endl;
            std::cin >> fig1;
            if (q[fig1 - 1] == nullptr) {
                std::cout << "Фигуры и так небыло в массиве" << std::endl;
            } else {
                q.del_figure(fig1 - 1);
                i -= 1;
                std::cout << "Фигура удалена" << std::endl;
            }
        }
        else if (name.find("total_area") == 0) {
            double avg = 0;
            for (int j = 0; j < i; j++) {
                const Figure* figur = q[j];
                avg += figur->area();
            }
            avg /= i;
            std::cout << "Средняя площадь: " << avg << std::endl;
        }
        else if (name.find("getInfo") == 0) {
            std::cout << "Номер фигуры?" << std::endl;
            std::cin >> fig1;
            const Figure* figur = q[fig1 - 1];
            if (q[fig1 - 1] == nullptr) {
                std::cout << "Фигуры нет в массиве..." << std::endl;
            } else {
                std::cout << "Площадь: " << figur->area() << std::endl;
                std::cout << "Центр: " << figur->center().first << ' ' << figur->center().second << std::endl;
            }
        }
        else if ((name.find("end") == 0)) {
            return 0;
        }
        else {
            std::cout << "Неправильная функция, повторите попытку" << std::endl;
            flag = 0;
        }
    } while ((name.find("end") != 0));
    return 0;
}