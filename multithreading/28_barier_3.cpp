#include <iostream>
#include <barrier>
#include <thread>

int main() {
    int phase = 0;
    
    // Барьер на 3 потока с функцией завершения
    std::barrier barrier{3, [&phase]() noexcept {
        std::cout << (std::stringstream() << "Фаза " << phase << " завершена\n").str();
        phase++;
    }};
    
    auto work = [&](int id) {
        for (int i = 0; i < 2; i++) {
            std::cout << (std::stringstream() << "Поток " << id << " начал работу\n").str();
            barrier.arrive_and_wait(); // Синхронизация
        }
    };
    
    std::thread t1(work, 1);
    std::thread t2(work, 2);
    std::thread t3(work, 3);
    
    t1.join(); t2.join(); t3.join();
}