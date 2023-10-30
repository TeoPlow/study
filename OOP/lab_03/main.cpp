#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

void add_point(int &x, int &y);

class Figure {
protected:
    std::string name;
public:
    virtual void getInfo() = 0;
};

class Square : public Figure{

public:
    int x1, x2, x3, x4;
    int y1, y2, y3, y4;

    friend inline std::istream& operator>> (std::istream& in, Square &square) {
        return in >> square.x1 >> square.y1 >> square.x2 >> square.y2 >> square.x3 >> square.y3 >> square.x4 >> square.y4;
    }

    Square() {
        x1 = x2 = x3 = x4 = y1 = y2 = y3 = y4 = 0;
    }

    // Square(std::string name) {
    //     this->name = name;
    //     std::cout << "Введите координаты точек через Enter, например: 5 2" << std::endl;
    //     add_point(x1, y1);
    //     add_point(x2, y2);
    //     add_point(x3, y3);
    //     add_point(x4, y4);
    // }

    void getInfo() override{
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

    friend inline std::istream& operator>> (std::istream& in, Rectangle &rectangle) {
        return in >> rectangle.x1 >> rectangle.y1 >> rectangle.x2 >> rectangle.y2 >> rectangle.x3 >> rectangle.y3 >> rectangle.x4 >> rectangle.y4;
    }

    // Rectangle(std::string name) {
    //     this->name = name;
    //     // std::cout << "Введите координаты точек через Enter, например: 5 2" << std::endl;
    //     // add_point(x1, y1);
    //     // add_point(x2, y2);
    //     // add_point(x3, y3);
    //     // add_point(x4, y4);
    // }

    Rectangle() {
        x1 = x2 = x3 = x4 = y1 = y2 = y3 = y4 = 0;
    }
    float area() {
        float S = abs(sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)) * sqrt(pow((x3 - x1), 2) + pow((y3 - y1), 2)));
        return S;
    }

    std::pair<float, float> Huinia () {
        float x_center = float(x1 + x2 + x3 + x4) / 4;
        float y_center = float(y1 + y2 + y3 + y4) / 4;
        return {x_center, y_center};
    }

    void getInfo() override{
        std::cout << "Прямоугольник: "<< name << ". Площадь: " << S << ". Центр фигуры: " << x_center << " " << y_center << std::endl;
        std::cout << "Точки: "<< x1 << " " << y1 << "  " << x2 << " " << y2 << "  " << x3 << " " << y3 << "  " << x4 << " " << y4 << std::endl;
    }
};

class Trapeze : public Figure{

public:
    int x1, x2, x3, x4;
    int y1, y2, y3, y4;

    friend inline std::istream& operator>> (std::istream& in, Trapeze &trapeze) {
        return in >> trapeze.x1 >> trapeze.y1 >> trapeze.x2 >> trapeze.y2 >> trapeze.x3 >> trapeze.y3 >> trapeze.x4 >> trapeze.y4;
    }

    Trapeze() {
        x1 = x2 = x3 = x4 = y1 = y2 = y3 = y4 = 0;
    }

    // Trapeze(std::string name) {
    //     this->name = name;
    //     std::cout << "Введите координаты точек через Enter, например: 5 2" << std::endl;
    //     add_point(x1, y1);
    //     add_point(x2, y2); 
    //     add_point(x3, y3);
    //     add_point(x4, y4);
    // }

    void getInfo() override{
        float S = abs(0.5 * (x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2)));
        float x_center = float(x1 + x2 + x3 + x4) / 4;
        float y_center = float(y1 + y2 + y3 + y4) / 4;
        std::cout << "Трапеция: "<< name << ". Площадь: " << S << ". Центр фигуры: " << x_center << " " << y_center << std::endl;
        std::cout << "Точки: "<< x1 << " " << y1 << "  " << x2 << " " << y2 << "  " << x3 << " " << y3 << "  " << x4 << " " << y4 << std::endl;
    }
};

class Array {
private:
    Figure ** arr;
    size_t size_arr;
    Array () {
        arr = new Figure * [0];
    }

    void increase_arr () {
        Figure ** arr2 = new Figure * [size_arr + 1];
        for (int i = 0; i < size_arr; i++) {
            arr2[i] = arr[i];
        }
        delete[] arr;
        arr = arr2;
        ++size_arr;
    }

public:
    void add_figure_to_arr(Figure * figure_name) {
        increase_arr();
        arr[size_arr - 1] = figure_name;
    }

    Figure * operator[] (size_t i) {
        return arr[i];
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
            Square square;
            std::cin >> square;
            // square.getInfo();
        } else if (name.find("rectangle") == 0) {
            Rectangle rectang;
            std::cin >> rectang;
            rectang.getInfo();
        } else if (name.find("trapeze") == 0) {
            Trapeze trap;
            std::cin >> trap;
            trap.getInfo();
        } else {
            std::cout << "Неправильное название, повторите попытку" << std::endl;
            flag = 0;
        }
    } while (flag == 0);
}

// void add_point(int &x, int &y) {
//     int* point = new int[2];
//     int index = -1;
    
//     for ( int i = 0; i < 2; i++ ) {
//         std::cin >> point[i];
//         if ( point[i] < 0 )
//             index = i;
//     }
//     x = point[0];
//     y = point[1];
        
//     delete[] point;
// }

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