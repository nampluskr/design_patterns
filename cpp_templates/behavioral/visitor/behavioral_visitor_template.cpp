#include <iostream>
#include <vector>
using namespace std;


// 전방 선언 (Forward Declaration)
struct ElementA;
struct ElementB;

// Visitor 인터페이스
struct Visitor {
    virtual ~Visitor() = default;
    virtual void visit(ElementA* element) = 0;
    virtual void visit(ElementB* element) = 0;
};

// Element 인터페이스
struct Element {
    virtual ~Element() = default;
    virtual void accept(Visitor* visitor) = 0;
};

// 구체적인 Element A
struct ElementA : public Element {
    ElementA(int data) { _dataA = data; }
    int getDataA() const { return _dataA; }
    void accept(Visitor* visitor) override { visitor->visit(this); }
private:
    int _dataA;
};

// 구체적인 Element B
struct ElementB : public Element {
    ElementB(const string& data) { _dataB = data; }
    string getDataB() { return _dataB; }
    void accept(Visitor* visitor) override { visitor->visit(this); }
private:
    string _dataB;
};

// 구체적인 Visitor 1
struct Visitor1 : public Visitor {
    void visit(ElementA* element) override { cout << "Visitor1 visiting ElementA: " << element->getDataA() << endl; }
    void visit(ElementB* element) override { cout << "Visitor1 visiting ElementB: " << element->getDataB() << endl; }
};

// 구체적인 Visitor 2
struct Visitor2 : public Visitor {
    void visit(ElementA* element) override { cout << "Visitor2 visiting ElementA: " << element->getDataA() * 2 << endl; }
    void visit(ElementB* element) override { cout << "Visitor2 visiting ElementB: " << element->getDataB() + " (visited)" << endl; }
};


int main()
{
    vector<Element*> elements;
    elements.push_back(new ElementA(10));
    elements.push_back(new ElementB("Hello"));

    Visitor1 visitor1;
    Visitor2 visitor2;

    for (Element* element : elements) {
        element->accept(&visitor1);
        element->accept(&visitor2);
    }

    for (Element* element : elements) {
        delete element;
    }

    return 0;
}
