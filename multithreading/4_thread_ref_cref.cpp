#include <thread>
#include <iostream>

class MyClass
{
public:
    //  this - адрес объекта  
    void instanceMethod1(int& i, double& d) {
        std::cout << "Поток с методом объекта (" << this << ") с доп. аргументами: " << i << " (" << &i << ") и " << d << "(" << &d << ")\n";
    }

    void instanceMethod2(int i, double d) {
        std::cout << "Поток с методом объекта (" << this << ") с доп. аргументами: " << i << " (" << &i << ") и " << d << "(" << &d << ")\n";
    }
};

int main()
{
    MyClass myObject; // Объект нашего класса
    int i = 1;  double d = 2.34;

    // Вывод адресов
    std::cout << "myObject (" << &myObject << ") i (" << &i << ") d (" << &d << ")\n\n \n";
    // Создание потоков
    std::thread thread1(&MyClass::instanceMethod1, &myObject, std::ref(i), std::ref(d)); // адрес myObject и ссылки на i, d
    thread1.join();
    /*
    - &object - норм 
    - std::ref(object) - норм
    - std::cref(object) - норм
    - object - не норм ( создается копия )
    */


    std::thread thread2(&MyClass::instanceMethod1, std::ref(myObject), std::ref(i), std::ref(d)); // ссылка myObject и ссылки на i, d
    thread2.join();

    std::thread thread3(&MyClass::instanceMethod2, myObject, i, d); // копия myObject и копии i, d
    thread3.join();
    
    return 0;
}