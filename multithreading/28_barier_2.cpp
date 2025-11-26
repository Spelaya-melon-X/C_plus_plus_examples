#include <iostream>
#include <thread>
#include <vector>
#include <barrier>

// Функция, выполняемая каждым потоком
void worker_thread(int id, std::barrier<>& sync_barrier) {
    std::cout << (std::stringstream() << "Поток " << id << " начал работу\n").str();
    // Имитация работы
    std::this_thread::sleep_for(std::chrono::milliseconds(100 * id));

    std::cout << (std::stringstream() << "Поток " << id << " достиг барьера\n").str();

    sync_barrier.arrive_and_wait(); // Ожидание других потоков
    
    std::cout << (std::stringstream() << "Поток " << id << " прошел барьер\n").str();
}

int main() {
    const int num_threads = 5;
    // Создаем барьер, который будет ждать 5 потоков
    std::barrier sync_barrier(num_threads);

    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(worker_thread, i, std::ref(sync_barrier));
    }

    // Собираем все потоки
    for (auto& t : threads) {
        t.join();
    }

    std::cout << (std::stringstream() << "Все потоки завершили работу\n").str();
    return 0;
}
