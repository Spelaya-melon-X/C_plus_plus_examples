#include <iostream>
#include <thread>
#include <mutex>

#define N_THREADS 5

std::mutex mtx1;
std::mutex mtx2;

void threadFunction(int id) 
{
    for (int i = 0; i < 5; i++) 
    {
        {
            std::scoped_lock lock(mtx1, mtx2);  // Одновременное захватывание нескольких мьютексов
            std::cout << "Поток " << id << ": итерация " << i << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() 
{
    std::thread threads[N_THREADS];

    for (int i = 0; i < N_THREADS; i++) 
        threads[i] = std::thread(threadFunction, i);
    
    for (auto& thread : threads) 
        thread.join();

    return 0;
}