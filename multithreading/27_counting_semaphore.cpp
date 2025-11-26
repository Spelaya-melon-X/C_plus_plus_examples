#include <iostream>
#include <sstream>
#include <thread>
#include <vector>
#include <semaphore>
#include <chrono>

// Глобальный семафор для ограничения доступа к ресурсу
std::counting_semaphore<5> semaphore(3); // Изначально доступно 3 ресурса

void worker(int id) {

    std::cout << (std::stringstream() <<  "Поток " << id << " пытается получить ресурс...\n").str()  << std::endl;
    semaphore.acquire(); // Ждем, пока ресурс не станет доступен
    std::cout << (std::stringstream() << "Поток " << id << " \x1b[32m получил \x1b[0m ресурс. Работает...\n").str() << std::endl;
    
    // Имитация работы с ресурсом
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    std::cout << (std::stringstream() << "Поток " << id << "\x1b[31m отпустил \x1b[0m ресурс. \n").str() << std::endl;
    semaphore.release(); // Освобождаем ресурс
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(worker, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
