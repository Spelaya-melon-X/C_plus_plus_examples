#include <iostream>
#include <thread>
#include <future>

void producer_function(std::promise<int>&& p) { 
    // Simulate some work
    std::this_thread::sleep_for(std::chrono::seconds(1));
    int result = 42;
    p.set_value(result); // Fulfill the promise
}

int main() {
    std::promise<int> p;
    std::future<int> f = p.get_future(); // Получите будущее, связанное с обещанием

    std::thread t(producer_function, std::move(p)); // Pass the promise to the thread

    // In the main thread, wait for and get the result from the future
    std::cout << "Waiting for result..." << std::endl;
    int value = f.get(); // Блокирует до тех пор, пока обещание не будет выполнено , а когда будет выполнено , то значение будет возвращено
    std::cout << "Received value: " << value << std::endl;

    t.join(); // Wait for the thread to finish
    return 0;
}