#include <iostream>
#include <sstream>
#include <mutex>
#include <thread>

#define N_THREADS 10

std::mutex mtx; // Глобальный мьютекс

void perform_task(int id) 
{
    std::unique_lock<std::mutex> ul(mtx, std::defer_lock); // Создаем объект lock, но не захватываем мьютекс сразу

    // Некоторые операции, которые не требуют защиты мьютексом
    std::cout << (std::stringstream() << "Поток " << id << " работает без блокировки мьютекса\n").str();

    ul.lock(); // Явно захватываем мьютекс
    std::cout << (std::stringstream() << "Поток " << id << " захватил мьютекс\n").str();
    
    // Выполнение критической секции, требующей защиты мьютексом
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Имитация длительной операции

    std::cout << (std::stringstream() << "Поток " << id << " освобождает мьютекс\n").str();
    ul.unlock(); // Явное освобождение мьютекса

    // Продолжение работы после критической секции без мьютекса
    std::cout << (std::stringstream() << "Поток " << id << " заканичивает работу\n").str();
}

int main() 
{
    std::thread threads[N_THREADS];

    // Создание потоков
    for (int i = 0; i < N_THREADS; i++) 
        threads[i] = std::thread(perform_task, i);

    // Ожидание завершения потоков
    for (int i = 0; i < N_THREADS; i++) 
        threads[i].join();

    return 0;
}