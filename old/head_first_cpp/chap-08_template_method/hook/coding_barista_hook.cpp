#include <iostream>
#include <string>
using namespace std;

// Abstract class
struct CaffeineBeverageWithHook {
    // template method
    void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();
        if (customWantsCondiments()) { addCondiments(); }
    }
    virtual ~CaffeineBeverageWithHook() = default;
    void boilWater() { cout << "Boiling water\n"; }
    virtual void brew() = 0;
    void pourInCup() { cout << "Pouring into cup\n"; }
    virtual void addCondiments() = 0;
    virtual bool customWantsCondiments() { return true; }
};

struct CoffeeWithHook : CaffeineBeverageWithHook {
    void brew() override { cout << "Dripping Coffee through filter\n"; }
    void addCondiments() override { cout << "Adding Sugar and Milk\n"; }
    // hook
    bool customWantsCondiments() override {
        string answer = getUserInput();
        if (answer == "y") return true;
        else return false;
    }
private:
    string getUserInput() {
        string answer = "";
        cout << "Would you like milk and sugar with your coffee (y/n)? ";
        cin >> answer;
        if (answer == "") return "no";
        return answer;
    }
};

struct TeaWithHook : CaffeineBeverageWithHook {
    void brew() override { cout << "Steeping the tea\n"; }
    void addCondiments() override { cout << "Adding Lemon\n"; }
};


int main()
{
    TeaWithHook* myTea = new TeaWithHook();
    CoffeeWithHook* myCoffee = new CoffeeWithHook();

    cout << "\nMaking tea...\n";
    myTea->prepareRecipe();

    cout << "\nMaking coffee...\n";
    myCoffee->prepareRecipe();

    delete myTea, myCoffee;
    return 0;
}