#include <iostream>
#include <atomic>
#include <thread>

#define N_THREADS 5

std::atomic_flag lock = ATOMIC_FLAG_INIT;

void simpleSpinLock(int id)
{
    while (lock.test_and_set(std::memory_order_acquire))  {
        // Блокировка занята, ждем
    }
    std::cout << "поток " << id << " захватил блокировку\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Симуляция работы
    lock.clear(std::memory_order_release);
}

int main() 
{
    std::thread threads[N_THREADS];
    for (int i = 0; i < N_THREADS; i++) 
        threads[i] = std::thread(simpleSpinLock, i);
    for (auto& thread : threads) 
        thread.join();
    
    return 0;
}