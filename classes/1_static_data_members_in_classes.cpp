#include <iostream>

class MyClass {
public:
    static int sharedValue; // Declared static data member
    int instanceValue;

    MyClass(int val) : instanceValue(val) {}
};

int MyClass::sharedValue = 10; // Defined outside the class

int main() {
    MyClass obj1(5);
    MyClass obj2(7);

    std::cout << "obj1.sharedValue: " << obj1.sharedValue << std::endl; // Access via object
    std::cout << "MyClass::sharedValue: " << MyClass::sharedValue << std::endl; // Access via class name

    obj1.sharedValue = 20; // Modifying sharedValue through obj1

    std::cout << "obj2.sharedValue: " << obj2.sharedValue << std::endl; // obj2 sees the change
    std::cout << "obj1.sharedValue: " << obj1.sharedValue << std::endl; // obj1 sees the change
    return 0;
}