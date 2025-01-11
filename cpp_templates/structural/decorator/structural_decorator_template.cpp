#include <iostream>
#include <string>

using namespace std;

// Component 인터페이스
struct Component {
    virtual ~Component() = default;
    virtual string operation() = 0;
};

// Concrete Component (구체적인 컴포넌트)
struct ConcreteComponent : Component {
    string operation() override { return "ConcreteComponent"; }
};

// Decorator 인터페이스
struct Decorator : Component {
    Decorator(Component* component) : _component(component) {}
    ~Decorator() { delete _component; }

    string operation() override {
        if (_component) { return _component->operation(); }
        return ""; // component가 nullptr인 경우 빈 문자열 반환 (안전 처리)
    }
protected:
    Component* _component;
};

// Concrete DecoratorA
struct DecoratorA : Decorator {
    DecoratorA(Component* component) : Decorator(component) {}
    string operation() override {
        return "DecoratorA(" + Decorator::operation() + ")";
    }
};

// Concrete DecoratorB
struct DecoratorB : Decorator {
    DecoratorB(Component* component) : Decorator(component) {}
    string operation() override {
        return "DecoratorB[" + Decorator::operation() + "]";
    }
};

int main()
{
    // 기본 컴포넌트 생성
    Component* component = new ConcreteComponent();
    cout << component->operation() << endl;

    // DecoratorA로 장식
    Component* decoratorA = new DecoratorA(component);
    cout << decoratorA->operation() << endl;

    // DecoratorB로 추가 장식 (DecoratorA 위에 덧씌움)
    Component* decoratorB = new DecoratorB(decoratorA);
    cout << decoratorB->operation() << endl;

    cout << endl;

    // 다른 순서로 장식
    Component* component2 = new ConcreteComponent();
    cout << component2->operation() << endl;

    Component* decoratorB2 = new DecoratorB(component2);
    cout << decoratorB2->operation() << endl;

    Component* decoratorA2 = new DecoratorA(decoratorB2);
    cout << decoratorA2->operation() << endl;

    delete decoratorA2;
    delete decoratorB2;
    delete component2;

    delete decoratorB;
    delete decoratorA;
    delete component;

    return 0;
}