#include <iostream>
using namespace std;

// Interface Duck
struct Duck {
    virtual ~Duck() = default;
    virtual void quack() = 0;
    virtual void fly() = 0;
};

struct MallardDuck : Duck {
    void quack() override { cout << "Quack\n"; }
    void fly() override { cout << "I'm flying\n"; }
};

// Interface Turkey
struct Turkey {
    virtual ~Turkey() = default;
    virtual void gobble() = 0;
    virtual void fly() = 0;
};

struct WildTurkey : Turkey {
    void gobble() override { cout << "Gobble gobble\n"; }
    void fly() override { cout << "I'm flying a short distance\n"; }
};

// Adapter
struct TurkeyAdapter : Duck {
    TurkeyAdapter(Turkey* turkey) { this->turkey = turkey; }
    void quack() override { turkey->gobble(); };
    void fly() override { for (int i = 0; i < 5; i++) turkey->fly(); }
private:
    Turkey* turkey;
};

void testDuck(Duck* duck) {
    duck->quack();
    duck->fly();
}

// DuckTestDrive
int main()
{
    Duck* duck = new MallardDuck();
    Turkey* turkey = new WildTurkey();
    Duck* turkeyAdapter = new TurkeyAdapter(turkey);

    cout << "The Turkey says...\n";
    turkey->gobble();
    turkey->fly();

    cout << "\nThe Duck says...\n";
    testDuck(duck);

    cout << "\nThe TurkeyAdapter says...\n";
    testDuck(turkeyAdapter);

    delete duck, turkey, turkeyAdapter;
    return 0;
}