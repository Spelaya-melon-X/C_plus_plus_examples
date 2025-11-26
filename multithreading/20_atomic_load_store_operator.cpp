#include <iostream>
#include <atomic>
using namespace std;

int main() {
    std::atomic<int> a(10); // Инициализация значением 10
    std::cout << "a: " << a << " ref a : " << &a << std::endl;

    int value = a.load();   // Чтение
    std::cout << "Value: " << value << " ref Value : " << &value <<  std::endl;

    a.store(20);            // Запись без возврата значения
    std::cout << "a: " << a << " ref a: " << &a << std::endl;

    a = 30;                 // Ещё один способ записи с возвратом копии значения
    std::cout << "a: " << a << " ref a: " << &a << std::endl;

    value = a;              // Ещё один способ чтения
    std::cout << "Value: " << value << " ref Value: " << &value <<  std::endl;

    return 0;
}