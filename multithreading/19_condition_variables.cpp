#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void worker_thread() {
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "Поток-работник: жду, пока не станет готово..." << std::endl;

    // Ждет, пока условие "ready" не станет истинным.
    // При этом происходит разблокировка мьютекса, а после получения уведомления
    // мьютекс снова захватывается (блокируется).
    cv.wait(lock, [] { return ready; });

    std::cout << "Поток-работник: условие выполнено. Выполняю работу." << std::endl;
}

void main_thread() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
        std::cout << "Главный поток: установил 'ready' в true." << std::endl;
    }
    // Уведомляет один ожидающий поток о том, что условие могло измениться.
    cv.notify_one();
}

int main() {
    std::thread worker(worker_thread);
    std::thread main(main_thread);

    worker.join();
    main.join();

    return 1;
}
