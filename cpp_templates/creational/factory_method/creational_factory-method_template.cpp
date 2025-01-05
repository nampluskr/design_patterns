#include <iostream>
using namespace std;

// 추상 제품 (Abstract Product)
// 팩토리 메서드 패턴에서 생성될 객체의 인터페이스를 정의합니다.
struct Product {
    virtual ~Product() = default;   // 가상 소멸자
    virtual void operation() = 0;         // 추상 메서드
};

// 구체적인 제품 A (Concrete Product A)
struct ProductA : Product {
    void operation() override { cout << "Using Product A\n"; }
};

// 구체적인 제품 B (Concrete Product B)
struct ProductB : Product {
    void operation() override { cout << "Using Product B\n"; }
};


// 추상 생성자 (Abstract Creator)
// 객체를 생성하는 팩토리 메서드를 정의합니다.
struct Creator {
    virtual ~Creator() = default;           // 가상 소멸자
    virtual Product* factoryMethod() = 0;   // 팩토리 메서드

    //Creator가 Product를 사용하는 방법의 예시
    void someOperation() {
        Product* product = this->factoryMethod();
        product->operation();
        delete product;
    }
};

// 구체적인 생성자 A (Concrete Creator A)
struct CreatorA : Creator {
    Product* factoryMethod() override {
        cout << "CreatorA creates ProductA\n";
        return new ProductA();
    }
};

// 구체적인 생성자 B (Concrete Creator B)
struct CreatorB : Creator {
    Product* factoryMethod() override {
        cout << "CreatorB creates ProductB\n";
        return new ProductB();
    }
};


int main()
{
    if (1) {
        cout << "\nUsage-1" << endl;
        Creator* creatorA = new CreatorA();
        Product* productA = creatorA->factoryMethod();
        productA->operation();
        delete productA;
        delete creatorA;

        cout << endl;
        Creator* creatorB = new CreatorB();
        Product* productB = creatorB->factoryMethod();
        productB->operation();
        delete productB;
        delete creatorB;
    }
    if (1) {
        cout << "\nUsage-2" << endl;
        Creator* creatorA = new CreatorA();
        creatorA->someOperation();
        delete creatorA;

        cout << endl;
        Creator* creatorB = new CreatorB();
        creatorB->someOperation();
        delete creatorB;
    }

    return 0;
}