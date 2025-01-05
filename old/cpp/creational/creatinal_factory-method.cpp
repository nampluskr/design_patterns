// https://medium.com/cp-massive-programming/factory-method-cheat-sheet-f1d2691e9c72
#include <iostream>
#include <string>
using namespace std;


// Product Interface
struct Food {
    virtual ~Food() {};
    virtual string produce() = 0;
    virtual string eat() = 0;
};

// Concrete Products
struct Pizza : Food {
    string produce() override { return "Let's make Pizza."; }
    string eat() override { return "Let's eat Pizza."; }
};

struct Wrap: Food {
    string produce() override { return "Let's make Wrap."; }
    string eat() override { return "Let's eat Wrap."; }
};

// Abstract Creator
struct Creator {
    virtual ~Creator() {};
    virtual Food* factoryMethod() = 0;

    string produceAndEat() {
        Food* food = factoryMethod();
        string _produce = food->produce();
        string _eat = food->eat();
        return _produce + " and " + _eat;
    }
};

// Concrete Creators
struct PizzaCreator : Creator {
    Food* factoryMethod() override { return new Pizza(); }
};

struct WrapCreator : Creator {
    Food* factoryMethod() override { return new Wrap(); }
};

// Client
string clientCode(Creator* creator) {
    return creator->produceAndEat();
}


int main()
{
    string activity;
    
    activity = clientCode(new PizzaCreator());
    cout << activity << endl;

    activity = clientCode(new WrapCreator());
    cout << activity << endl;

    return 0;
}
