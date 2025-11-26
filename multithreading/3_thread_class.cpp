#include <iostream>
#include <thread>

class MyClass {
public:
  void instanceMethod1() {
    std::cout << "Поток 1 с методом объекта без доп. аргументов\n";
  }

  void instanceMethod2(int i, double d) {
    std::cout << "Поток 2 с методом объекта с доп. аргументами: " << i << ' '
              << d << '\n';
  }

  static void staticMethod1() {
    std::cout << "Поток 3 со статическим методом без аргументов\n";
  }

  static void staticMethod2(int i, double d) {
    std::cout << "Поток 4 со статическим методом с аргументами: " << i << ' '
              << d << '\n';
  }
};

int main() {
  MyClass myObject; // Объект нашего класса

  // Создание потоков
  std::thread thread1(&MyClass::instanceMethod1, &myObject); // передаем объект класса 
  thread1.join();
  std::thread thread2(&MyClass::instanceMethod2, &myObject, 1, 2.34);
  thread2.join();


  std::thread thread3(&MyClass::staticMethod1); // не передаем объект класса 
  thread3.join();
  std::thread thread4(&MyClass::staticMethod2, 1, 2.34);
  thread4.join();

  return 0;
}