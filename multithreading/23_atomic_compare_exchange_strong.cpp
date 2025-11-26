#include <atomic>
#include <iostream>
#include <thread>

std::atomic<int> counter(0);

void increment_counter() {
    int expected_value = counter.load(); // Загружаем текущее значение

    // Сравниваем и, если совпадает, устанавливаем новое значение
    // Если значение изменилось другим потоком, операция вернет false
    while (!counter.compare_exchange_strong(expected_value, expected_value + 1)) {
        // Ожидаемое значение обновится на фактическое, и мы повторим попытку
    }
}

int main() {
    // Запускаем несколько потоков для инкремента
    std::thread t1(increment_counter);
    std::thread t2(increment_counter);

    t1.join();
    t2.join();

    std::cout << "Итоговое значение: " << counter.load() << std::endl; // Ожидаемый вывод: 2
    return 0;
}
