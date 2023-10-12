#include "four.h"

int main() {
    Four a, b;
    char op;
    std::cout << "Enter a expression like: a + b:\n";
    try {
        std::cin >> a >> op >> b;

        switch (op)
        {
        case '+':
            std::cout << a + b << std::endl;
            std::cout << a.to_decimal() << ' ' << op << ' ' << b.to_decimal() << std::endl;
            break;
        case '-':
            std::cout << a - b << std::endl;
            std::cout << a.to_decimal() << ' ' << op << ' ' << b.to_decimal() << std::endl;
            break;
        case '=':
            std::cout << (a == b) << std::endl;
            std::cout << a.to_decimal() << ' ' << op << ' ' << b.to_decimal() << std::endl;
            break;
        case '>':
            std::cout << (a > b) << std::endl;
            std::cout << a.to_decimal() << ' ' << op << ' ' << b.to_decimal() << std::endl;
            break;
        case '<':
            std::cout << (a < b) << std::endl;
            std::cout << a.to_decimal() << ' ' << op << ' ' << b.to_decimal() << std::endl;
            break;
        default:
            throw std::invalid_argument("There's no such operation for Four");
            break;
        }
    }
    catch(std::invalid_argument ex) {
        std::cout << "Invalid argument: " << ex.what() << std::endl;
    }
    catch(std::underflow_error ex) {
        std::cout << "Underflow error: " << ex.what() << std::endl;
    }

    return 0;
}