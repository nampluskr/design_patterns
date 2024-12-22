#if 0
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Abstract Pizza class
struct Pizza {
    virtual ~Pizza() = default;
    void prepare() {
        coud << endl;
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
struct NYStypeCheesePizza : Pizza {
    NYStypeCheesePizza() {
        name = "NY Style Sauce and Cheese Pizza";
        dough = "Thin Crust Dough";
        sauce = "Marinara Sauce";
        toppings.push_back("Grated Reggiano Cheese");
    }
};

struct ChicagoStyleCheesePizza : Pizza {
    ChicagoStyleCheesePizza() {
        name = "Chicago Style Deep Dish Cheese Pizza";
        dough = "Extra Thick Crust Dough";
        sauce = "Plum Tomato Sauce";
        toppings.push_back("Shredded Mozzarella Cheese");
    }
    void cut() { cout << "Cutting the pizza into square slices" << endl; }
};

// Abstract PizzaStore
struct PizzaStore {
    virtual ~PizzaStore() = default;
    virtual Pizza* createPizza(const string& type) = 0;
    Pizza* orderPizza(const string& type) {
        Pizza* pizza;
        pizza = createPizza(type);
        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();
        return pizza;
    }
};

// Concrete PizzaStore
struct NYPizzaStore : PizzaStore {
    Pizza* createPizza(const string& item) {
        if (item == "cheese") return new NYStypeCheesePizza();
        else return nullptr;
    }
};

struct ChicagoPizzaStore : PizzaStore {
    Pizza* createPizza(const string& item) {
        if (item == "cheese") return new ChicagoStyleCheesePizza();
        else return nullptr;
    }
};


// PizzaTestDrive
int main()
{
    PizzaStore* nyStore = new NYPizzaStore();
    PizzaStore* chicagoStore = new ChicagoPizzaStore();
    Pizza* pizza;

    pizza = nyStore->orderPizza("cheese");
    cout << "Ethan ordered a " + pizza->getName() + "\n" << endl;

    pizza = chicagoStore->orderPizza("cheese");
    cout << "Joel ordered a " + pizza->getName() + "\n" << endl;

    delete nyStore, pizza;
    return 0;
}
#endif