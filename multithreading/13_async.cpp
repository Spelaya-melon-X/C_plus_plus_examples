#include <future>
#include <iostream>
#include <thread>
#include <stdexcept>

int calculate_square(int x) {
    return x * x;
}

int simple() {
    // Запуск calculate_square асинхронно
    std::future<int> future_result = std::async(calculate_square, 5);

    // Здесь можно выполнять другой код, пока calculate_square работает в фоновом режиме

    // Получение результата. future_result.get() заблокирует выполнение,
    // пока результат не будет готов
    int result = future_result.get();
    std::cout << "Результат: " << result << std::endl; // Выведет "Результат: 25"
    return 0;
}


int lambda_() {
    std::future<int> future_result = std::async(std::launch::async, []() {
        std::cout << "Работаю в отдельном потоке..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return 10 * 20;
    });

    std::cout << "Ожидание результата..." << std::endl;
    int result = future_result.get();
    std::cout << "Результат: " << result << std::endl; // Выведет "Результат: 200"
    return 0;
}



int divide(int a, int b) {
    if (b == 0) {
        throw std::runtime_error("Деление на ноль!");
    }
    return a / b;
}

int excetpion_() {
    std::future<int> future_result = std::async(divide, 10, 0);

    try {
        // .get() вызовет исключение, если оно было брошено в асинхронной задаче
        int result = future_result.get();
        std::cout << "Результат: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Произошла ошибка: " << e.what() << std::endl;
    }

    return 0;
}


int main() {
    simple();
    lambda_();
    excetpion_();
    return 0;
}
