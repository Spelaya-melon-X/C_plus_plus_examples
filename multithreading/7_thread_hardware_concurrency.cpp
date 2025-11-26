#include <iostream>
#include <thread> // Required for std::thread::hardware_concurrency()

int main() {
    // Get the number of concurrent threads supported by the hardware
    unsigned int num_concurrent_threads = std::thread::hardware_concurrency();

    if (num_concurrent_threads > 0) {
        std::cout << "The hardware supports approximately " 
                  << num_concurrent_threads 
                  << " concurrent threads." << std::endl;
    } else {
        std::cout << "Unable to determine the number of concurrent threads supported by the hardware." << std::endl;
        std::cout << "This might mean the information is not well-defined or computable on this system." << std::endl;
    }

    return 0;
}