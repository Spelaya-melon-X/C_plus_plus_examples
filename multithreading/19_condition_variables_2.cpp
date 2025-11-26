#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <unistd.h>

// Глобальные переменные
std::mutex mtx;
std::condition_variable cv;
bool ready = false; // Условие, на котором основано ожидание

// Функция потока, ожидающего события
void waiting_thread() 
{
    std::unique_lock<std::mutex> lck(mtx);
    while (!ready)  {
        std::cout << "Ожидающий поток: ждем сигнала...\n";
        cv.wait(lck);
    }
    std::cout << "Ожидающий поток: получен сигнал.\n";
}

// Функция потока, посылающего сигнал
void signaling_thread() 
{
    sleep(1); // Имитация работы
    std::unique_lock<std::mutex> lck(mtx);
    ready = true;
    std::cout << "Сигнализирующий поток: выдаем сигнал.\n";
    cv.notify_all();
}

int main() 
{
    std::thread w_thread(waiting_thread);
    std::thread s_thread(signaling_thread);

    w_thread.join();
    s_thread.join();

    return 0;
}