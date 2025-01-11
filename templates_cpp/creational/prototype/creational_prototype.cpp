#include <iostream>
#include <string>
using namespace std;


// 프로토타입 인터페이스 (Prototype Interface)
struct Prototype {
    virtual ~Prototype() = default;
    virtual Prototype* clone() = 0;
    virtual void print() = 0;
};

// 구체적인 프로토타입 A (Concrete Prototype A)
struct PrototypeA : Prototype {
    PrototypeA(const string& dataA) { _dataA = dataA; }
    PrototypeA(const PrototypeA& other) {   // 복사 생성자
        _dataA = other._dataA;
        cout << "PrototypeA copy constructor" << endl;
    }
    Prototype* clone() override {
        cout << "Cloning PrototypeA" << endl;
        return new PrototypeA(*this);       // 복사 생성자 이용
    }
    void print() override { cout << "PrototypeA Data: " << _dataA << endl; }
private:
    string _dataA;
};

// 구체적인 프로토타입 B (Concrete Prototype B)
struct PrototypeB : Prototype {
    PrototypeB(int dataB) { _dataB = dataB; }
    PrototypeB(const PrototypeB& other) {   // 복사 생성자
        _dataB = other._dataB;
        _protectedDataB = other._protectedDataB;
        cout << "PrototypeB copy constructor" << endl;
    }
    Prototype* clone() override {
        cout << "Cloning PrototypeB" << endl;
        return new PrototypeB(*this);       // 복사 생성자 이용
    }
    void print() override {
        cout << "PrototypeB Data: " << _dataB << ", Protected Data: " << _protectedDataB << endl;
    }
private:
    int _dataB;
protected:
    int _protectedDataB = 0;
};

// PrototypeB를 상속받는 자식 클래스 예시
struct DerivedPrototypeB : PrototypeB {
    DerivedPrototypeB(int dataB) : PrototypeB(dataB) {
        _protectedDataB = dataB * 2; // protected 멤버 접근
    }
    void printDerived() {
        cout << "Derived Data: " << _protectedDataB << endl;
    }
};

int main()
{
    // PrototypeA 사용
    PrototypeA* prototypeA = new PrototypeA("Initial Data A");
    prototypeA->print();
    Prototype* cloneA1 = prototypeA->clone();
    cloneA1->print();
    delete prototypeA;
    delete cloneA1;

    cout << endl;

    // PrototypeB 사용
    PrototypeB* prototypeB = new PrototypeB(123);
    prototypeB->print();
    Prototype* cloneB1 = prototypeB->clone();
    cloneB1->print();
    delete prototypeB;
    delete cloneB1;

    cout << endl;

    // DerivedPrototypeB 사용
    DerivedPrototypeB* derivedB = new DerivedPrototypeB(10);
    derivedB->print();
    derivedB->printDerived();
    delete derivedB;

    return 0;
}
