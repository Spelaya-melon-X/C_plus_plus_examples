#include <iostream>
#include <future>
#include <thread>

int threadFunction() {
    // Имитация работы
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 42; // Ответ на главный вопрос жизни, вселенной и всего такого
}

int main() {
    // Создание std::promise
    std::promise<int> threadPromise;

    // Получение std::future из std::promise
    std::future<int> threadFuture = threadPromise.get_future();

    // Запуск потока, передача std::promise в поток
    std::thread myThread([&threadPromise]() {
        threadPromise.set_value(threadFunction()); // Установка значения, которое будет получено через std::future
    });

    // Здесь можно проводить вычисления, пока запущенный поток работает

    // Получение результата работы потока (main засыпает)
    int result = threadFuture.get();
    std::cout << "Результат работы потока: " << result << std::endl;

    // Дождемся завершения потока 
    myThread.join();
    return 0;
}