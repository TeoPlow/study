#include <string>
#include <iostream>

#include "four.h"

int main() {
    Four a, b;
    char oper;
    std::cout << "Enter numbers:\n";
    try {
        std::string num1,num2;
        std::cout << "Enter a: \n a = ";
        std::cin >> num1;

        std::cout << "Enter b: \n b = ";
        std::cin >> num2;

        Four a(num1);
        Four b(num2);

        std::cout << "a in decimal = " << a.to_10() << std::endl;
        std::cout << "b in decimal = " << b.to_10() << std::endl;

        std::cout << "a + b = " << (a + b).to_string() << std::endl;
        std::cout << "a - b = " << (a - b).to_string() << std::endl;
        std::cout << "a > b: " << (a > b) << std::endl;
        std::cout << "a < b: " << (a < b) << std::endl;
        std::cout << "a = b: " << (a == b) << std::endl;

        std::cout << "Length a : " << a.size() << std::endl;
        std::cout << "Length b : " << b.size() << std::endl << std::endl;

        std::cout << "String a: " << a.to_string() << std::endl;
        std::cout << "String b: " << b.to_string() << std::endl;

        std::cout << "Copy a = b: " << (a = b).to_string() << std::endl;

        std::cout << "New a: " << a.to_string() << std::endl;
    }
    catch(std::invalid_argument ex) {
        std::cout << "Invalid argument: " << ex.what() << std::endl;
    }
    
    return 0;
}