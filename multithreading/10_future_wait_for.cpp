#include <iostream>
#include <future>
#include <chrono>
#include <thread> // For std::this_thread::sleep_for

// A function that simulates a long-running task
int calculate_sum(int a, int b) {
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate work
    return a + b;
}

int main() {
    // Launch the asynchronous task
    std::future<int> result_future = std::async(std::launch::async, calculate_sum, 10, 20);

    std::cout << "Waiting for the result with a timeout of 1 second..." << std::endl;

    // Ждите результат максимум 1 секунду.
    std::future_status status = result_future.wait_for(std::chrono::seconds(1));

    if (status == std::future_status::ready) {
        std::cout << "Result is ready! Sum: " << result_future.get() << std::endl;

    } else if (status == std::future_status::timeout) { // timeout -  время выполнения превышено
        std::cout << "Timeout occurred. Result not ready within 1 second." << std::endl;
        // Tеперь вы можете выбрать ожидание на неопределенный срок или сделать что-то другое.
        std::cout << "Waiting indefinitely for the result..." << std::endl;
        std::cout << "Sum: " << result_future.get() << std::endl; // Это заблокирует до готовности

    } else if (status == std::future_status::deferred) { // deferred - отложенный
        std::cout << "The task was deferred (std::launch::deferred) and not yet run." << std::endl;
        // Вызов get() выполнит задачу в текущем потоке.
        std::cout << "Sum: " << result_future.get() << std::endl;
    }

    return 0;
}