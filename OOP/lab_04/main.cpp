#include <iostream>
#include <cmath>
#include <memory>

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
    Array<std::shared_ptr<Figure<double>>> q(3);
    std::cout << "(Вводите точки так: 0 0, 1 0, 0 1, 1 1)" << std::endl;
    std::cout << "Существующие фигуры: square, rectangle, trapeze" << std::endl;

    do {
        do {
            flag = 1;
            std::cout << "Введите название фигуры: " << std::endl;
            std::cin >> name;
            if (name.find("square") == 0) {
                std::cout << "Введите 4 точки X и Y" << std::endl;
                std::shared_ptr<Square<double>> sq (new Square<double>);
                std::cin >> *sq;
                std::shared_ptr<Figure<double>> ptr = sq;
                q.add_figure(i, ptr);
                
            } else if (name.find("rectangle") == 0) {
                std::cout << "Введите 4 точки X и Y" << std::endl;
                std::shared_ptr<Rectangle<double>> rec (new Rectangle<double>);
                std::cin >> *rec;
                std::shared_ptr<Figure<double>> ptr2 = rec;
                q.add_figure(i, ptr2);

            } else if (name.find("trapeze") == 0) {
                std::cout << "Введите 4 точки X и Y" << std::endl;
                std::shared_ptr<Trapeze<double>> tr (new Trapeze<double>);
                std::cin >> *tr;
                std::shared_ptr<Figure<double>> ptr3 = tr;
                q.add_figure(i, ptr3);

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
        const std::shared_ptr<Figure<double>> figur = q[j];
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
            q.del_figure();
            std::cout << "Последняя фигура удалена" << std::endl;
        }
        else if (name.find("total_area") == 0) {
            double avg = 0;
            for (int j = 0; j < i && j < q.get_size(); j++) {
                const std::shared_ptr<Figure<double>> figur = q[j];
                avg += figur->area();
            }
            avg /= i;
            std::cout << "Средняя площадь: " << avg << std::endl;
        }
        else if (name.find("getInfo") == 0) {
            std::cout << "Номер фигуры?" << std::endl;
            std::cin >> fig1;
            const std::shared_ptr<Figure<double>> figur = q[fig1 - 1];
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
