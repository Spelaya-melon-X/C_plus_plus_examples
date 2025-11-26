#include <atomic>
#include <iostream>

int main() {
    // Создаем атомарную переменную с начальным значением 10
    std::atomic<int> counter(10);

    // Выполняем атомарную операцию exchange
    // Новое значение (20) записывается в counter,
    // а старое значение (10) возвращается и присваивается переменной old_value
    int old_value = counter.exchange(20);

    // Выводим старое и новое значение
    std::cout << "Старое значение: " << old_value << std::endl;
    std::cout << "Новое значение: " << counter.load() << std::endl;

    return 0;
}
