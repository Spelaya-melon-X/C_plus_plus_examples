#include <thread>
#include <iostream>
#include <iostream>

using namespace std;


int main() {
    // Лямбда функции
    auto myLambdaFunction1 = []() {
        std::cout << "Поток 1 с лямбда-функцией без аргументов\n";
    };
    auto myLambdaFunction2 = [](int i, double d) {
        std::cout << "Поток 2 с лямбда-функцией с аргументами: " << i << ' ' << d << '\n';
    };

    // Создаем потоки, выполняющие лямбда-функции
    std::thread myThread1(myLambdaFunction1);
    myThread1.join();

    std::thread myThread2(myLambdaFunction2, 1, 2.34);
    myThread2.join();

    std::thread myThread3([]() {
        std::cout << "Поток 3 с лямбда-функцией без аргументов\n";
    }); // myThread3
    myThread3.join();

    std::thread myThread4([](int i, double d) { // Лямбда-функция с параметрами
        std::cout << "Поток 4 с лямбда-функцией с аргументами: " << i << ' ' << d << '\n';
    }, 
    1, 2.34); // myThread4
    myThread4.join();

    return 0;
}