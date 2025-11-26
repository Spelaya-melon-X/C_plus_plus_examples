#include <iostream>
#include <sstream>
#include <barrier>
#include <thread>

#define N_THREADS 5

void sync_function(){
    std::cout << "Потоки пришли на барьер\n";
}

std::barrier sync_point1(N_THREADS); // Синхронизируем потоки
std::barrier sync_point2(N_THREADS, sync_function); // Синхронизируем потоки c функцией

void worker(int id){
    std::cout << (std::stringstream() << "Поток " << id << " стартовал\n").str();
    std::this_thread::sleep_for(std::chrono::milliseconds(400 * id)); // Имитация работы продолжительностью в соответствии с идентификатором потока

    std::cout << (std::stringstream() << "Поток " << id << " достиг 1 барьера\n").str();
    sync_point1.arrive_and_wait();

    std::cout << (std::stringstream() << "Поток " << id << " прошел 1 барьер\n").str();
    std::this_thread::sleep_for(std::chrono::milliseconds(400 * (id+1))); // Имитация работы продолжительностью в соответствии с идентификатором потока

    std::cout << (std::stringstream() << "Поток " << id << " достиг 2 барьера\n").str();
    
    sync_point2.arrive_and_wait();
    std::cout << (std::stringstream() << "Поток " << id << " прошел 2 барьер\n").str();
}

int main(){
    std::thread threads[N_THREADS];
    for (int i = 0; i < N_THREADS; i++) 
        threads[i] = std::thread(worker, i);

    for (auto &thread : threads)
        thread.join();

    return 0;
}