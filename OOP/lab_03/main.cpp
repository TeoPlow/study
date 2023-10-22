#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

void add_point(int &x, int &y);

class Figure {
protected:
    std::string name;
public:

};

class Square : public Figure{

public:
    int x1, x2, x3, x4;
    int y1, y2, y3, y4;

    Square(std::string name) {
        this->name = name;
        std::cout << "Введите координаты точек через Enter, например: 5 2" << std::endl;
        add_point(x1, y1);
        add_point(x2, y2);
        add_point(x3, y3);
        add_point(x4, y4);
    }

    void getInfo() {
        float S = abs(sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)) * sqrt(pow((x3 - x1), 2) + pow((y3 - y1), 2)));
        float x_center = float(x1 + x2 + x3 + x4) / 4;
        float y_center = float(y1 + y2 + y3 + y4) / 4;
        std::cout << "Квадрат: "<< name << ". Площадь: " << S << ". Центр фигуры: " << x_center << " " << y_center << std::endl;
        std::cout << "Точки: "<< x1 << " " << y1 << "  " << x2 << " " << y2 << "  " << x3 << " " << y3 << "  " << x4 << " " << y4 << std::endl;
    }
};

class Rectangle : public Figure{

public:
    int x1, x2, x3, x4;
    int y1, y2, y3, y4;

    Rectangle(std::string name) {
        this->name = name;
        std::cout << "Введите координаты точек через Enter, например: 5 2" << std::endl;
        add_point(x1, y1);
        add_point(x2, y2);
        add_point(x3, y3);
        add_point(x4, y4);
    }

    void getInfo() {
        float S = abs(sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)) * sqrt(pow((x3 - x1), 2) + pow((y3 - y1), 2)));
        float x_center = float(x1 + x2 + x3 + x4) / 4;
        float y_center = float(y1 + y2 + y3 + y4) / 4;
        std::cout << "Прямоугольник: "<< name << ". Площадь: " << S << ". Центр фигуры: " << x_center << " " << y_center << std::endl;
        std::cout << "Точки: "<< x1 << " " << y1 << "  " << x2 << " " << y2 << "  " << x3 << " " << y3 << "  " << x4 << " " << y4 << std::endl;
    }
};

class Trapeze : public Figure{

public:
    int x1, x2, x3, x4;
    int y1, y2, y3, y4;

    Trapeze(std::string name) {
        this->name = name;
        std::cout << "Введите координаты точек через Enter, например: 5 2" << std::endl;
        add_point(x1, y1);
        add_point(x2, y2); 
        add_point(x3, y3);
        add_point(x4, y4);
    }

    void getInfo() {
        float S = abs(0.5 * (x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2)));
        float x_center = float(x1 + x2 + x3 + x4) / 4;
        float y_center = float(y1 + y2 + y3 + y4) / 4;
        std::cout << "Трапеция: "<< name << ". Площадь: " << S << ". Центр фигуры: " << x_center << " " << y_center << std::endl;
        std::cout << "Точки: "<< x1 << " " << y1 << "  " << x2 << " " << y2 << "  " << x3 << " " << y3 << "  " << x4 << " " << y4 << std::endl;
    }
};

void add_figure() {
    std::string name;
    bool flag;

    do {
        flag = 1;
        std::cout << "Введите название фигуры: " << std::endl;
        std::cin >> name;

        if (name.find("square") == 0) {
            Square triang(name);
            triang.getInfo();
        } else if (name.find("rectangle") == 0) {
            Rectangle rectang(name);
            rectang.getInfo();
        } else if (name.find("trapeze") == 0) {
            Trapeze trap(name);
            trap.getInfo();
        } else {
            std::cout << "Неправильное название, повторите попытку" << std::endl;
            flag = 0;
        }
    } while (flag == 0);
}

void add_point(int &x, int &y) {
    int* point = new int[2];
    int index = -1;
    
    for ( int i = 0; i < 2; i++ ) {
        std::cin >> point[i];
        if ( point[i] < 0 )
            index = i;
    }
    x = point[0];
    y = point[1];
        
    delete[] point;
}

int main () {
// Input figure
    char answer;
    std::cout << "Существующие фигуры: square, rectangle, trapeze" << std::endl;

    do {
    add_figure();
    std::cout << "Хотите добавить ещё одну фигуру? (y/n)" << std::endl;
    std::cin >> answer;
    } while (answer == 'y' || answer == 'Y');

    return 0;
} 