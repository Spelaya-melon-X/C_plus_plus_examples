#include <iostream>
#include <mutex>
#include <thread>

// Глобальная переменная и мьютекс
int shared_data = 0;
std::mutex mtx;
std::timed_mutex tmtx;

// Функция потока
void thread_function_timed() 
{
    if (tmtx.try_lock_for(std::chrono::seconds(10))) 
    { 
        // Блокировка на 10 секунд в течении которых мьютекс стал доступен
        // Критическая секция
        tmtx.unlock(); 
    } 
    else 
    {
        // Мьютекс не был захвачен в течение 1 секунды
    }
}

// Функция потока
void thread_function() 
{
    // Блокировка мьютекса
    mtx.lock();
    
    // Критическая секция
    shared_data++;
    std::cout << "Поток: shared_data = " << shared_data << '\n'; // Тут не будет состояния гонки в вычислении операторов<< для std::cout
    
    // Разблокировка мьютекса
    mtx.unlock();
}

int main() 
{
    std::thread threads[2];

    // Создание потоков
    for (int i = 0; i < 2; i++) 
        threads[i] = std::thread(thread_function);

    // Ожидание завершения потоков
    for (int i = 0; i < 2; i++) 
        threads[i].join();


    for (int i = 0; i < 2; i++) 
        threads[i] = std::thread(thread_function_timed);

    // Ожидание завершения потоков
    for (int i = 0; i < 2; i++) 
        threads[i].join();

    return 0;
}