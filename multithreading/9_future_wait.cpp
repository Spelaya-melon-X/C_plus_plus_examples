#include <iostream>
#include <future>
#include <thread>
#include <chrono>

// A function that simulates a long-running task
int calculate_sum(int a, int b) {
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate work
    return a + b;
}

int main() {
    // Запустить асинхронную задачу с помощью std::async
    std::future<int> result_future = std::async(std::launch::async, calculate_sum, 5, 7);

    std::cout << "Main thread is doing other work while the calculation runs..." << std::endl;

    // Simulate some other work in the main thread
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Main thread is now waiting for the calculation to complete." << std::endl;

    // Блокируем основной поток, пока общее состояние result_future не будет готово.
    result_future.wait();

    std::cout << "Calculation is complete. Now retrieving the result." << std::endl;

    // Получите результат (это не приведет к дальнейшей блокировке, так как wait() уже обеспечил готовность)
    int sum = result_future.get();

    std::cout << "The sum is: " << sum << std::endl;

    return 0;
}