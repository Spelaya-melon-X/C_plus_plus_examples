#include <iostream>
#include <thread>
#include <semaphore>
#include <vector>

// Глобальный бинарный семафор
std::binary_semaphore data_ready{0}; // Начальное состояние - 0, то есть данные не готовы

void producer(const std::vector<int>& data) { // прозводитель
    for (int value : data) {
        // Моделируем работу по созданию данных
        std::cout << "Производитель: создаем данные " << value << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        // Сигнализируем потребителю, что данные готовы
        data_ready.release();
    }
}

void consumer(int count) { // потребитель
    for (int i = 0; i < count; ++i) {
        // Ожидаем, пока семафор не станет доступным (то есть данные будут готовы)
        data_ready.acquire();

        // Получаем и обрабатываем данные
        std::cout << "Потребитель: получил данные." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

int main() {
    std::vector<int> producer_data = {1, 2, 3};

    std::thread prod_thread(producer, producer_data);
    std::thread cons_thread(consumer, producer_data.size());

    prod_thread.join();
    cons_thread.join();

    std::cout << "Готово!" << std::endl;
    return 0;
}
