#include <iostream>
#include <sstream>
#include <thread>
#include <latch>

#define N_THREADS 5

std::latch latch(N_THREADS); // Создаем латч, ожидающий 5 участников

void worker(int id){
    std::cout << (std::stringstream() << "Поток " << id << " начал работу\n").str();
    std::this_thread::sleep_for(std::chrono::milliseconds(400 * (id + 1))); // Симуляция работы

    std::cout << (std::stringstream() << "Поток " << id << " закончил свою работу и ждет остальных\n").str();
    
    latch.arrive_and_wait(); // Уменьшаем счетчик и ждем остальных
    std::cout << (std::stringstream() << "Поток " << id << " вышел из латча\n").str();
}

int main()
{
    std::thread threads[N_THREADS];
    for (int i = 0; i < N_THREADS; i++)
        threads[i] = std::thread(worker, i);

    for (auto &t : threads)
        t.join();

    return 0;
}