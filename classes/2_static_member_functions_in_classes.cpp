#include <iostream>

class Calculator {
public:
    static int add(int a, int b) {
        return a + b;
    }
    static int subtract(int a, int b) {
        return a - b;
    }
};

int main() {
    int sum = Calculator::add(5, 3); // можно вызывать методы класса , без создания объекта
    int difference = Calculator::subtract(10, 4);

    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Difference: " << difference << std::endl;
    return 0;
}