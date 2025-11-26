#include <future>
#include <iostream>
#include <thread>

int calculate_sum(int a, int b) {
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate work
    return a + b;
}

int main() {
    // Будущее, сконструированное по умолчанию, недействительно
    std::future<int> f1;
    std::cout << "f1.valid(): " << f1.valid() << std::endl; // Output: 0 (false)

    //Future, полученный от std::async, является допустимым
    std::future<int> f2 = std::async(calculate_sum, 5, 7);
    std::cout << "f2.valid() before get(): " << f2.valid() << std::endl; // Output: 1 (true)

    //  После вызова get() будущее больше недействительно.
    int result = f2.get();
    std::cout << "Result: " << result << std::endl;
    std::cout << "f2.valid() after get(): " << f2.valid() << std::endl; // Output: 0 (false)

    return 0;
}