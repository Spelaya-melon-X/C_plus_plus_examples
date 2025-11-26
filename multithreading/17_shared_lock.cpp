#include <iostream>
#include <sstream>
#include <mutex>
#include <shared_mutex>
#include <thread>

#define N_THREADS 5
using namespace std;

class ThreadSafeCounter 
{
    public:
        // Увеличивает значение счетчика
        int increment() {
            std::unique_lock lock(mtx);
            return ++value;
        }

        // Получает текущее значение счетчика
        int get() const {
            std::shared_lock lock(mtx);
            return value;
        }

    private:
        mutable std::shared_mutex mtx;
        int value = 0;
};

void reader(ThreadSafeCounter& counter, int id){
    int value;
    for (int i = 0; i < 5; i++) 
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        value = counter.get();
        std::cout << (std::stringstream() << "Текущее значение в потоке " << id << ": " << value << '\n').str();
    }
}

void writer(ThreadSafeCounter& counter) 
{
    int value;
    for (int i = 0; i < 5; i++) 
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        value = counter.increment();
        std::cout << (std::stringstream() << "Икремент изменил значение на: " << value  << '\n').str();
    }
}

int main() 
{
    ThreadSafeCounter counter;
    std::thread threads[N_THREADS];

    // Запускаем несколько потоков-чтецов
    for (int i = 0; i < N_THREADS; i++) 
        threads[i] = std::thread(reader, std::ref(counter), i);

    // Запускаем поток-записыватель
    std::thread threadW(writer, std::ref(counter));

    // Ждем завершения всех потоков
    for (auto& t : threads) 
        t.join();

    threadW.join();

    return 0;
}