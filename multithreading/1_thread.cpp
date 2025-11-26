#include <thread>
#include <iostream>
 
void threadFunction1()
{
    std::cout << "Поток 1 с обычной функцией без аргументов\n";
}

void threadFunction2(int i, double d)
{
    std::cout << "Поток 2 с обычной функцией с аргументами: " << i << ' ' << d << '\n';
}

int main()
{
    std::thread myThread1(threadFunction1);
    myThread1.join();

    std::thread myThread2(threadFunction2, 1, 2.34);
    myThread2.join();

    return 0;
}