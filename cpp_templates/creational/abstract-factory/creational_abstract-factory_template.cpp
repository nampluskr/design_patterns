#include <iostream>
using namespace std;


// 추상 제품 A (Abstract Product A)
struct ProductA {
    virtual ~ProductA() = default;
    virtual void operationA() = 0;
};

// 구체적인 제품 A1 (Concrete Product A1)
struct ProductA1 : ProductA {
    void operationA() override { cout << "ProductA1 operationA\n"; }
};

// 구체적인 제품 A2 (Concrete Product A2)
struct ProductA2 : ProductA {
    void operationA() override { cout << "ProductA2 operationA\n"; }
};

// 추상 제품 B (Abstract Product B)
struct ProductB {
    virtual ~ProductB() = default;
    virtual void operationB() = 0;
    virtual void interact(ProductA* productA) = 0; // 제품 A와의 상호작용
};

// 구체적인 제품 B1 (Concrete Product B1)
struct ProductB1 : ProductB {
    void operationB() override { cout << "ProductB1 operationB\n"; }
    void interact(ProductA* productA) override { 
        cout << "ProductB1 interacts with ";
        productA->operationA();
    }
};

// 구체적인 제품 B2 (Concrete Product B2)
struct ProductB2 : ProductB {
    void operationB() override { cout << "ProductB2 operationB\n"; }
    void interact(ProductA* productA) override {
        cout << "ProductB2 interacts with ";
        productA->operationA();
    }
};


// 추상 팩토리 (Abstract Factory)
struct Factory {
    virtual ~Factory() = default;
    virtual ProductA* createProductA() = 0;
    virtual ProductB* createProductB() = 0;
};

// 구체적인 팩토리 1 (Concrete Factory 1)
struct Factory1 : Factory {
    ProductA* createProductA() override {
        cout << "Factory1 creates ProductA1\n";
        return new ProductA1();
    }
    ProductB* createProductB() override {
        cout << "Factory1 creates ProductB1\n";
        return new ProductB1();
    }
};

// 구체적인 팩토리 2 (Concrete Factory 2)
struct Factory2 : Factory {
    ProductA* createProductA() override {
        cout << "Factory2 creates ProductA2\n";
        return new ProductA2();
    }
    ProductB* createProductB() override {
        cout << "Factory2 creates ProductB2\n";
        return new ProductB2();
    }
};


int main()
{
    // 팩토리 1 사용
    cout << endl;
    Factory* factory1 = new Factory1();
    ProductA* productA1 = factory1->createProductA();
    ProductB* productB1 = factory1->createProductB();

    productA1->operationA();
    productB1->operationB();
    productB1->interact(productA1);

    delete productA1;
    delete productB1;
    delete factory1;

    // 팩토리 2 사용
    cout << endl;
    Factory* factory2 = new Factory2();
    ProductA* productA2 = factory2->createProductA();
    ProductB* productB2 = factory2->createProductB();

    productA2->operationA();
    productB2->operationB();
    productB2->interact(productA2);

    delete productA2;
    delete productB2;
    delete factory2;

    return 0;
}
