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
    virtual void buildPartA() = 0;
    virtual void buildPartB() = 0;
    virtual void buildPartC() = 0;
    virtual Product* getResult() = 0;
};

// 구체적인 빌더 (Concrete Builder)
// 추상 빌더 인터페이스를 구현하여 실제 제품을 생성
struct ConcreteBuilder : public Builder {
    ConcreteBuilder() { _product = new Product(); }
    ~ConcreteBuilder(){
        cout << "~ConcreteBuilder()" << endl;
        delete _product;
    }
    void buildPartA() override {
        _product->partA = "Part A";
        cout << "Building part A" << endl;
    }
    void buildPartB() override {
        _product->partB = "Part B";
        cout << "Building part B" << endl;
    }
    void buildPartC() override {
        _product->partC = "Part C";
        cout << "Building part C" << endl;
    }
    Product* getResult() override {
        Product* result = _product;
        _product = new Product();    // 새로운 Product 객체 생성
        return result;
    }
private:
    Product* _product;
};

// 디렉터 (Director)
// 빌더를 사용하여 객체 생성 과정을 관리
struct Director {
    ~Director(){
        cout << "~Director()" << endl;
        delete _builder;
    }
    void setBuilder(Builder* builder) { _builder = builder; }

    void buildMinimalProduct() {
        _builder->buildPartA();
    }
    void buildFullProduct() {
        _builder->buildPartA();
        _builder->buildPartB();
        _builder->buildPartC();
    }
private:
    Builder* _builder;
};

int main()
{
    // Director 사용
    Director* director = new Director();
    Builder* builder = new ConcreteBuilder();
    director->setBuilder(builder);

    cout << "Building minimal product:" << endl;
    director->buildMinimalProduct();
    Product* product1 = builder->getResult();
    product1->show();
    delete product1;

    cout << "\nBuilding full product:" << endl;
    director->buildFullProduct();
    Product* product2 = builder->getResult();
    product2->show();
    delete product2;
    delete director;

    return 0;
}