#include <iostream>
#include <thread>
#include <chrono>

void foo() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void bar() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main() {
    std::thread t1(foo);
    std::thread t2(bar);

    std::cout << "Initial thread IDs:" << std::endl;
    std::cout << "t1: " << t1.get_id() << std::endl;
    std::cout << "t2: " << t2.get_id() << std::endl;

    // Swap using the non-member function std::swap
    std::swap(t1, t2);
    std::cout << "\nAfter std::swap(t1, t2):" << std::endl;
    std::cout << "t1: " << t1.get_id() << std::endl;
    std::cout << "t2: " << t2.get_id() << std::endl;

    // Swap using the member function t1.swap(t2)
    t1.swap(t2);
    std::cout << "\nAfter t1.swap(t2):" << std::endl;
    std::cout << "t1: " << t1.get_id() << std::endl;
    std::cout << "t2: " << t2.get_id() << std::endl;

    // Join the threads (the actual thread execution continues independently)
    t1.join();
    t2.join();

    return 0;
}
