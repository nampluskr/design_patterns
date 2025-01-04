#include <iostream>
using namespace std;


// Target 인터페이스 (클라이언트가 기대하는 인터페이스)
struct Target {
    virtual ~Target() = default;
    virtual void request() { cout << "Target's request.\n"; };
};

// Adaptee 클래스 (기존 클래스, 호환되지 않는 인터페이스)
struct Adaptee {
    void specificRequest() {
        cout << "Adaptee's specific request.\n";
    }
};

// Adapter 클래스 (Target 인터페이스를 구현하고 Adaptee를 사용)
struct Adapter : Target {
    Adapter(Adaptee* adaptee) { _adaptee = adaptee;}
    ~Adapter() { delete _adaptee; }

    void request() override {
        cout << "Adapter translates request to specific request.\n";
        _adaptee->specificRequest();
    }
private:
    Adaptee* _adaptee; // Adaptee 객체를 멤버로 가짐
};

int main()
{
    Target* target = new Target;
    target->request();
    delete target;

    cout << endl;
    Target* adapter = new Adapter(new Adaptee); // 어댑터를 통해 Adaptee 사용
    adapter->request();

    delete target; // 동적 할당 해제

    return 0;
}