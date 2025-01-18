#include <iostream>
#include <string>
using namespace std;

// Abstract class
struct CaffeineBeverage {
    // template method
    void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
    }
    virtual ~CaffeineBeverage() = default;
    void boilWater() { cout << "Boiling water\n"; }
    virtual void brew() = 0;
    void pourInCup() { cout << "Pouring into cup\n"; }
    virtual void addCondiments() = 0;
};

struct Coffee : CaffeineBeverage {
    void brew() override { cout << "Dripping Coffee through filter\n"; }
    void addCondiments() override { cout << "Adding Sugar and Milk\n"; }
};

struct Tea : CaffeineBeverage {
    void brew() override { cout << "Steeping the tea\n"; }
    void addCondiments() override { cout << "Adding Lemon\n"; }
};


int main()
{
    Tea* myTea = new Tea();
    myTea->prepareRecipe();

    Coffee* myCoffee = new Coffee();
    myCoffee->prepareRecipe();

    delete myTea, myCoffee;
    return 0;
}