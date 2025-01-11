#include <iostream>
using namespace std;


struct Singleton {
    static Singleton* _instance;

    Singleton(int data) { 
        _data = data;
        cout << "Singleton constructor called" << endl;
    }
    //~Singleton() { cout << "Singleton destructor called" << endl; }

    Singleton(const Singleton& other) = delete;             // 복사 생성자 삭제
    Singleton& operator=(const Singleton& other) = delete;  // 복사 대입 연산자 삭제
    Singleton(Singleton&& other) = delete;                  // 이동 생성자 삭제
    Singleton& operator=(Singleton&& other) = delete;       // 이동 대입 연산자 삭제

    static Singleton& getInstance() {
        if (!_instance)
            _instance = new Singleton(42); // 스레드 안전하지 않음!
        return *_instance;
    }
    void printData() { cout << "Singleton Data: " << _data << endl; }
    void setData(int data) { _data = data; }

private:
    int _data;
};


// 정적 멤버 초기화
Singleton* Singleton::_instance = nullptr;


int main() {
    Singleton& singleton = Singleton::getInstance();
    singleton.printData();
    singleton.setData(100);
    singleton.printData();

    cout << endl;

    Singleton& singleton2 = Singleton::getInstance();
    singleton2.printData();

    delete Singleton::_instance;    // 명시적인 메모리 해제! 매우 중요!
    Singleton::_instance = nullptr; // dangling pointer 방지

    return 0;
}
