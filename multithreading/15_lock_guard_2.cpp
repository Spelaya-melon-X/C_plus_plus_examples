#include <iostream>
#include <thread>
#include <mutex>

#define N_THREADS 10

std::mutex mtx;

void print_id(int id) 
{
    // Небезопасная секция
    // ...
    // Блок кода после lock_guard автоматически защищен мьютексом
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Поток " << id << " работает в безопасной секции\n"; // Тут не будет состояния гонки в вычислении операторов<< для std::cout
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Задержка во времени
    // Мьютекс автоматически освободится при выходе из блока (в данном случае функции)
}

int main() 
{
    std::thread threads[N_THREADS];

    // Создание потоков
    for (int i = 0; i < N_THREADS; i++) 
        threads[i] = std::thread(print_id, i);

    // Ожидание завершения потоков
    for (int i = 0; i < N_THREADS; i++) 
        threads[i].join();

    return 0;
}