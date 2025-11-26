#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

std::atomic<int> counter(0);

void increment() {
    int expected = counter.load(); // Загружаем текущее значение
    int desired = expected + 1;

    // Пытаемся заменить значение.
    // Если значение counter было изменено другим потоком,
    // compare_exchange_weak вернет false, а expected будет обновлено до нового значения.
    while (!counter.compare_exchange_weak(expected, desired)) {
        desired = expected + 1; // Пересчитываем желаемое значение
    }
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(increment);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Final counter value: " << counter.load() << std::endl; // Ожидаемый вывод: 10

    return 0;
}
