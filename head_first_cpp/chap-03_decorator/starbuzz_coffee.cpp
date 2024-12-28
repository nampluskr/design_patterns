#include <iostream>
#include <string>
using namespace std;


// Abstract Beverage
struct Beverage {
    virtual ~Beverage() = default;
    virtual double cost() = 0;
    virtual string getDescription() { return description; }
protected:
    string description = "Unknown Beverage";
};

// Concrete Beverages
struct Esopresso: Beverage {
    Esopresso() { description = "Esopresso"; }
    double cost() override { return 1.99; }
};

struct HouseBlend: Beverage {
    HouseBlend() { description = "House Blend Coffee"; }
    double cost() override { return 0.89; }
};

// Abstract Decorator
struct CondimentDecorator: Beverage {
    virtual ~CondimentDecorator() = default;
    virtual string getDescription() = 0;
protected:
    Beverage* beverage;
};

// Concrete Decoators
struct Mocha : CondimentDecorator {
    Mocha(Beverage* beverage) { this->beverage = beverage; }
    ~Mocha() { delete beverage; }
    string getDescription() override { return beverage->getDescription() + ", Mocha"; }
    double cost() override { return beverage->cost() + 0.20; }
};

struct Soy : CondimentDecorator {
    Soy(Beverage* beverage) { this->beverage = beverage; }
    ~Soy() { delete beverage; }
    string getDescription() override { return beverage->getDescription() + ", Soy"; }
    double cost() override { return beverage->cost() + 0.15; }
};

struct Whip : CondimentDecorator {
    Whip(Beverage* beverage) { this->beverage = beverage; }
    ~Whip() { delete beverage; }
    string getDescription() override { return beverage->getDescription() + ", whip"; }
    double cost() override { return beverage->cost() + 0.10; }
};

int main()
{
    Beverage* beverage1 = new Esopresso();
    cout << beverage1->getDescription() << " $" << beverage1->cost() << endl;

    Beverage* beverage2 = new HouseBlend();
    cout << beverage2->getDescription() << " $" << beverage2->cost() << endl;
    beverage2 = new Mocha(beverage2);
    cout << beverage2->getDescription() << " $" << beverage2->cost() << endl;
    beverage2 = new Soy(beverage2);
    cout << beverage2->getDescription() << " $" << beverage2->cost() << endl;
    beverage2 = new Whip(beverage2);
    cout << beverage2->getDescription() << " $" << beverage2->cost() << endl;

    delete beverage1, beverage2;
    return 0;
}