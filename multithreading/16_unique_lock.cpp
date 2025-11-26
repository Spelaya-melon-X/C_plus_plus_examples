#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::mutex mtx; // Global mutex to protect shared_data
int shared_data = 0; // Shared data variable

void increment_data_with_unique_lock() {
    // Создайте объект unique_lock, отложив получение блокировки.
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock);

    //Выполнять некоторые операции, не требующие блокировки
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    //Явно получить блокировку
    lock.lock();

    // Критическая секция: безопасное изменение shared_data
    shared_data += 1;
    std::cout << "Thread " << std::this_thread::get_id() << " incremented shared_data to: " << shared_data << std::endl;

    // Снимите блокировку вручную, прежде чем unique_lock выйдет из области действия.
    // Это позволяет другим потокам получить блокировку раньше, если это необходимо.
    lock.unlock();

    //Выполнить дополнительные операции после снятия блокировки
    std::this_thread::sleep_for(std::chrono::milliseconds(20));

    // Блокировка будет автоматически повторно установлена ​​деструктором unique_lock 
    // если она не была явно разблокирована или может быть повторно заблокирована вручную. 
    // В этом примере мы явно разблокировали блокировку и теперь находимся вне критической секции.
}

int main() {
    std::vector<std::thread> threads;

    // Create multiple threads to increment shared_data
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(increment_data_with_unique_lock);
    }

    // Wait for all threads to finish
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Final value of shared_data: " << shared_data << std::endl;

    return 0;
}