#include <iostream>
#include <string>
using namespace std;


// 제품 (Product)
// 빌더 패턴으로 생성될 복합 객체
struct Product {
    string partA, partB, partC;

    ~Product(){ cout << "~Product()" << endl; }
    void show() { cout << "Product parts: " << partA << ", " << partB << ", " << partC << endl; }
};

// 추상 빌더 (Abstract Builder)
// 제품의 각 부분을 생성하는 메서드를 정의
struct Builder {
    virtual ~Builder() = default;
    virtual Builder* buildPartA(const string& value) = 0;
    virtual Builder* buildPartB(const string& value) = 0;
    virtual Builder* buildPartC(const string& value) = 0;
    virtual Product* getResult() = 0;
};

// 구체적인 빌더 (Concrete Builder)
// 추상 빌더 인터페이스를 구현하여 실제 제품을 생성
// 메서드 체이닝(method chaining)을 통해 제품의 사양을 연속적으로 정의
struct ConcreteBuilder : Builder {
    Product* product;

    ConcreteBuilder() { product = new Product(); }
    ~ConcreteBuilder(){
        cout << "~ConcreteBuilder()" << endl;
        delete product;
    }
    Builder* buildPartA(const string& value) override {
        product->partA = value;
        cout << "Building part A: " << value << endl;
        return this; // 핵심: this 반환
    }
    Builder* buildPartB(const string& value) override {
        product->partB = value;
        cout << "Building part B: " << value << endl;
        return this; // 핵심: this 반환
    }
    Builder* buildPartC(const string& value) override {
        product->partC = value;
        cout << "Building part C: " << value << endl;
        return this; // 핵심: this 반환
    }
    Product* getResult() override {
        Product* result = product;
        product = new Product(); // 새로운 Product 객체 생성 (빌더 재사용을 위해)
        return result;
    }
};

int main()
{
    // Director 미사용: 메서드 체이닝을 사용하여 제품 생성
    Builder* builder = new ConcreteBuilder();
    
    Product* product1 = builder->buildPartA("Part A1")
                               ->buildPartB("Part B1")
                               ->buildPartC("Part C1")
                               ->getResult();
    product1->show();
    delete product1;

    cout << endl;
    Product* product2 = builder->buildPartA("Part A2")
                               ->buildPartB("Part B2")
                               ->getResult(); // Part C는 생략
    product2->show();
    delete product2;
    delete builder;

    return 0;
}