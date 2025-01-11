#include <iostream>
using namespace std;


// 추상 클래스 (Abstract Class)
struct AbstractClass {
    virtual ~AbstractClass() = default;

    // 템플릿 메서드 (Template Method) : 알고리즘의 뼈대를 정의합니다.
    void templateMethod() {
        primitiveOperation1();
        primitiveOperation2();
        if (hook()) {   // Hook 메서드 (선택적 확장 지점)
            concreteOperation();
        }
        primitiveOperation3();
    }
protected:
    // 추상 메서드 (Primitive Operations) : 하위 클래스에서 구현해야 하는 메서드입니다.
    virtual void primitiveOperation1() = 0;
    virtual void primitiveOperation2() = 0;
    virtual void primitiveOperation3() = 0;

    // Hook 메서드 (선택적 확장 지점) : 하위 클래스에서 필요에 따라 오버라이드할 수 있습니다.
    virtual bool hook() { return false; }   // 기본적으로 아무 동작도 하지 않음

private:
    void concreteOperation() { cout << "AbstractClass::concreteOperation\n"; }
};

// 구체 클래스 A (Concrete Class A)
struct ConcreteClassA : AbstractClass {
protected:
    void primitiveOperation1() override { cout << "ConcreteClassA::primitiveOperation1\n"; }
    void primitiveOperation2() override { cout << "ConcreteClassA::primitiveOperation2\n"; }
    void primitiveOperation3() override { cout << "ConcreteClassA::primitiveOperation3\n"; }
};

// 구체 클래스 B (Concrete Class B)
struct ConcreteClassB : AbstractClass {
protected:
    void primitiveOperation1() override { cout << "ConcreteClassB::primitiveOperation1\n"; }
    void primitiveOperation2() override { cout << "ConcreteClassB::primitiveOperation2\n"; }
    void primitiveOperation3() override { cout << "ConcreteClassB::primitiveOperation3\n"; }
    bool hook() override { return true; } // Hook 메서드 오버라이드
};

int main()
{
    AbstractClass* classA = new ConcreteClassA();
    classA->templateMethod();
    delete classA;

    cout << endl;

    AbstractClass* classB = new ConcreteClassB();
    classB->templateMethod();
    delete classB;

    return 0;
}
