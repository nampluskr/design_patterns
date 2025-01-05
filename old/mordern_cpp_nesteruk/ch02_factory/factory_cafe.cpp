#if 1
#include <iostream>
#include <string>
#include <map>
using namespace std;


// Abstract Product
class HotDrink {
public:
    virtual ~HotDrink() {};
    virtual void prepare(int volume) = 0;
};

// Concrete Products
struct Tea: public HotDrink {
public:
    void prepare(int volume) override {
        cout << "Take tea bag, boil water, pour " << volume << "ml, add lemon.\n";
    }
};

struct Coffee: public HotDrink {
public:
    void prepare(int volume) override {
        cout << "Grind some beans, boil water, pour " << volume << "ml, add cream, enjoy!\n";
    }
};

// Factory Interface
class HotDrinkFactory {
public:
    virtual ~HotDrinkFactory() {};
    virtual HotDrink* make() const = 0;
};

// Concrete Factories
class TeaFactory: public HotDrinkFactory {
public:
    HotDrink* make() const override { return new Tea(); }
};

class CoffeeFactory: public HotDrinkFactory {
public:
    HotDrink* make() const override { return new Coffee(); }
};

// Client
class DrinkFactory {
private:
    map<string, HotDrinkFactory*> hot_factories;
public:
    DrinkFactory() {
        hot_factories["tea"] = new TeaFactory();
        hot_factories["coffee"] = new CoffeeFactory();
    }
    ~DrinkFactory() {
        delete hot_factories["tea"];
        delete hot_factories["coffee"];
    }
    HotDrink* make_drink(const string& name) {
        HotDrink* drink = hot_factories[name]->make();
        drink->prepare(200);
        return drink;
    }
};


int main()
{
    DrinkFactory factory;
    HotDrink* coffee = factory.make_drink("coffee");
    HotDrink* tea = factory.make_drink("tea");

    coffee->prepare(500);
    tea->prepare(300);

    delete coffee;
    delete tea;

    return 0;
}
#endif