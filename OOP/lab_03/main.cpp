#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class Figure {
protected:
    std::string name;
    float S;
    float x_center;
    float y_center;
public:

};

class Triangle : public Figure{

public:
    int x1, x2, x3;
    int y1, y2, y3;

    void getInfo() {
        std::cout << "Треугольник: "<< name << ". Площадь: " << S << ". Центр фигуры: " << x_center << y_center << std::endl;
    }

    void add_point() {
    int* point = new int[2];
    int index = -1;
 
    for ( int i = 0; i < 2; i++ ) {
        std::cin >> point[i];
        if ( point[i] < 0 )
            index = i;
    }
    x1 = point[0];
    y1 = point[1];
    
    delete[] point;
}
};

class Rectangle : public Figure{

public:
    int x1, x2, x3, x4;
    int y1, y2, y3, y4;

    void getInfo() {
        std::cout << "Прямоугольник: "<< name << ". Площадь: " << S << ". Центр фигуры: " << x_center << y_center << std::endl;
    }
};

class Trapeze : public Figure{

public:
    int x1, x2, x3, x4;
    int y1, y2, y3, y4;

    void getInfo() {
        std::cout << "Трапеция: "<< name << ". Площадь: " << S << ". Центр фигуры: " << x_center << y_center << std::endl;
    }
};

int main () {
// Input figure
    std::string figure_name; 
    std::cout << "Существующие фигуры: triangle, rectangle, trapeze";
    std::cout << "Введите название фигуры: ";
    std::cin >> figure_name;
    if (figure_name == "triangle") {
        for (int i = 0; i <= 3; i++) {
            add_point();
        }
    } else if (figure_name == "triangle") {

    } else if (figure_name == "triangle") {
        
    }
    std::cout << "Введите координаты точек через Enter, например: 5 2";
    
    return 0;
} 