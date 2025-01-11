#include <iostream>
#include <memory>
#include <mutex>

class Singleton {
private:
    Singleton(int data) : _data(data) {
        std::cout << "Singleton constructor called" << std::endl;
    }

    ~Singleton() {
        std::cout << "Singleton destructor called" << std::endl;
    }

    Singleton(const Singleton& other) = delete;
    Singleton& operator=(const Singleton& other) = delete;
    Singleton(Singleton&& other) = delete;
    Singleton& operator=(Singleton&& other) = delete;

public:
    static Singleton& getInstance() {
        static Singleton instance(42); // 정적 지역 변수 초기화 (스레드 안전)
        return instance;
    }

    void printData() const { std::cout << "Singleton Data: " << _data << std::endl; }
    void setData(int data) { _data = data; }

private:
    int _data;
};

int main()
{
    Singleton& singleton = Singleton::getInstance();
    singleton.printData();
    singleton.setData(100);
    singleton.printData();

    std::cout << std::endl;

    Singleton& singleton2 = Singleton::getInstance();
    singleton2.printData();

    return 0;
}