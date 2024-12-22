#if 1
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Abstract Pizza class
struct Pizza {
    virtual ~Pizza() = default;
    void prepare() {
        cout << endl;
        cout << "Preparing " + name << endl;
        cout << "Tossing dough..." << endl;
        cout << "Adding sauce..." << endl;
        cout << "Adding toppings: " << endl;
        for (const string& topping : toppings)
            cout << "    " + topping << endl;
    }
    void bake() { cout << "Bake for 25 minutes at 350" << endl; }
    void cut() { cout << "Cutting the pizza into diagonal slices" << endl; }
    void box() { cout << "Place pizza in official PizzaStore box" << endl; }
    string getName() { return name; }
protected:
    string name, dough, sauce;
    vector<string> toppings;
};

// Concrete Pizza classes
struct CheesePizza : Pizza {
    CheesePizza() { name = "Cheese Pizza"; }
};

struct GreekPizza : Pizza {
    GreekPizza() { name = "Greek Pizza"; }
};

struct PepperoniPizza : Pizza {
    PepperoniPizza() { name = "Pepperoni Pizza"; }
};

// Factory Funtion
Pizza* orderPizza(const string& type) {
    Pizza* pizza;

    if (type == "cheese") { pizza = new CheesePizza(); }
    else if (type == "greek") { pizza = new GreekPizza(); }
    else if (type == "pepperoni") { pizza = new PepperoniPizza(); }
    else { pizza = nullptr; }

    pizza->prepare();
    pizza->bake();
    pizza->cut();
    pizza->box();
    return pizza;
}

// Factory Class
struct SimplePizzaFactory {
    Pizza* createPizza(const string& type) {
        Pizza* pizza = nullptr;

        if (type == "cheese") { pizza = new CheesePizza(); }
        else if (type == "greek") { pizza = new GreekPizza(); }
        else if (type == "pepperoni") { pizza = new PepperoniPizza(); }
        return pizza;
    }
};

struct PizzaStore {
    PizzaStore(SimplePizzaFactory* factory) { this->factory = factory; }
    ~PizzaStore() { delete factory; }
    Pizza* orderPizza(const string& type) {
        Pizza* pizza = factory->createPizza(type);
        if (pizza) {
            pizza->prepare();
            pizza->bake();
            pizza->cut();
            pizza->box();
        }
        return pizza;
    }
protected:
    SimplePizzaFactory* factory;
};


int main()
{
    if (0) { // Factory Function
        Pizza* pizza;
        pizza = orderPizza("cheese");
        pizza = orderPizza("greek");
        pizza = orderPizza("pepperoni");

        delete pizza;
    }
    if (1) { // Factory Class (pointer)
        Pizza* pizza;
        auto* pizzaStore = new PizzaStore(new SimplePizzaFactory());
        pizza = pizzaStore->orderPizza("cheese");
        pizza = pizzaStore->orderPizza("greek");
        pizza = pizzaStore->orderPizza("pepperoni");

        delete pizza;
        delete pizzaStore;
    }
    if (1) { // Factory Class (reference)
        Pizza* pizza;
        PizzaStore& pizzaStore = PizzaStore(&SimplePizzaFactory());
        pizza = pizzaStore.orderPizza("cheese");
        pizza = pizzaStore.orderPizza("greek");
        pizza = pizzaStore.orderPizza("pepperoni");

        delete pizza;
    }
    return 0;
}
#endif