#include <iostream>
#include <string>
using namespace std;


// Implementation Interface
struct Implementation {
    virtual ~Implementation() {}
    virtual string operationImpl() = 0;
};

// Concrete Implementations
struct ImplementationA : Implementation {
    string operationImpl() override {
        return "ImplementationA: Here's the result on the platform A.\n";
    }
};
struct ImplementationB : Implementation {
    string operationImpl() override {
        return "ImplementationB: Here's the result on the platform B.\n";
    }
};

// Abstraction
struct Abstraction {
    Abstraction() { _impl = nullptr; }
    Abstraction(Implementation* implementation) { _impl = implementation; }
    virtual ~Abstraction() { delete _impl; };

    virtual string operation() {
        return "Abstraction: Base operation with:\n" + _impl->operationImpl();
    }
protected:
    Implementation* _impl;
};

// Extended Abstraction
struct RefinedAbstraction : Abstraction {
    RefinedAbstraction(Implementation* implementation) { _impl = implementation; }

    string operation() override {
        return "RefinedAbstraction: Extended operation with:\n" + _impl->operationImpl();
    }
};

void ClientCode(Abstraction* abstraction) {
    cout << abstraction->operation();
    cout << endl;
}

int main()
{
    Implementation* implementation = new ImplementationA;
    Abstraction* abstraction = new Abstraction(implementation);

    ClientCode(abstraction);
    delete implementation;
    delete abstraction;

    implementation = new ImplementationB;
    abstraction = new RefinedAbstraction(implementation);

    ClientCode(abstraction);
    delete implementation;
    delete abstraction;

    return 0;
}
