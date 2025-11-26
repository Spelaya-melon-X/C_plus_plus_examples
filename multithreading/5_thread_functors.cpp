#include <thread>
#include <iostream>

class MyClass {
public:
    void operator()(){
        std::cout << "Поток с функтором (" << this << ") - без аргументов\n";
    }

    void operator()(int i, double d) {
        std::cout << "Поток  с функтором (" << this << ") с аргументами: " << i << ' ' << d << '\n';
    }
};

int main()
{
    MyClass myObject; // Объект-функтор
    // Адрес объекта-функтора
    std::cout << "myObject (" << &myObject << ")\n";
    
    // Создание потоков
    std::thread thread1(std::ref(myObject)); // ссылка на объект-функтор
    thread1.join();
    std::thread thread2(myObject); // копия объекта-функтора
    thread2.join();
    std::thread thread3(std::ref(myObject), 1, 2.3); // ссылка на объект-функтор с аргументами
    thread3.join();
    
    return 0;
}