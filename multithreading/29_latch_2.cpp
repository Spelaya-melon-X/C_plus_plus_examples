#include <iostream>
#include <thread>
#include <vector>
#include <latch>

// Количество поваров (потоков-производителей)
const int NUM_CHEFS = 3;

// Создаем объект latch с начальным счетчиком, равным количеству поваров
std::latch chef_completion_latch(NUM_CHEFS);

void chef_task(int id) {
    std::cout << (std::stringstream() << "Повар " << id << " начал готовить блюдо\n").str();
    // Имитация работы повара
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << (std::stringstream() << "Повар " << id << " закончил готовить блюдо\n").str();
    
    // Уменьшаем счетчик, сигнализируя о завершении работы
    chef_completion_latch.count_down();
}

int main() {
    std::cout << (std::stringstream() << "Добро пожаловать в ресторан!\n").str();
    
    // Создаем и запускаем потоки для каждого повара
    std::vector<std::thread> chefs;
    for (int i = 0; i < NUM_CHEFS; ++i) {
        chefs.emplace_back(chef_task, i + 1);
    }
    
    // Официант (main поток) ожидает, пока все повара не закончат работу
    std::cout << (std::stringstream() << "Официант ожидает завершения работы всех поваров\n").str();
    chef_completion_latch.wait();
    
    std::cout << (std::stringstream() << "Все повары закончили работу\n").str();
    
    // Ждем завершения всех потоков поваров
    for (auto& chef : chefs) {
        chef.join();
    }
    
    return 0;
}
