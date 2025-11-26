#include <iostream>
#include <mutex>
#include <thread>


// Global mutex to protect shared_data
std::mutex g_mutex; 
// Shared data variable
int g_shared_data = 0;

void increment_data(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        // Создайте объект lock_guard. Это заблокирует g_mutex при создании.
        std::lock_guard<std::mutex> lock(g_mutex); 
        // Критическая секция: безопасное изменение g_shared_data
        g_shared_data++;
        // Мьютекс автоматически освобождается, когда «lock» выходит из области видимости 
        // (в конце итерации цикла или функции, если цикла нет). 
    }

}

int main() {
    std::cout << "Initial g_shared_data: " << g_shared_data << std::endl;

    // Create two threads that run the increment_data function
    std::thread t1(increment_data, 100000);
    std::thread t2(increment_data, 100000);

    // Wait for both threads to finish
    t1.join();
    t2.join();

    std::cout << "Final g_shared_data: " << g_shared_data << std::endl;

    return 0;
}