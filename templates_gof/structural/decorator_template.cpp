// Decorator Pattern Template
// https://refactoring.guru/design-patterns/decorator/cpp/example

#include <iostream>
#include <string>
using namespace std;


// Interface
struct Component {
    virtual ~Component() = default;
    virtual string operation() = 0;
};


struct ConcreteComponent : Component {
    string operation() override { return "ConcreteComponent"; }
};


struct Decorator : Component {
    Decorator(Component* component) : _component(component) {}
    virtual ~Decorator() = default;
    string operation() override { return _component->operation(); }
protected:
    Component* _component;
};


struct DecoratorA : Decorator {
    DecoratorA(Component* component) : Decorator(component) {}
    string operation() override { return "DecoratorA(" + Decorator::operation() + ")"; }
};


struct DecoratorB : Decorator {
    DecoratorB(Component* component) : Decorator(component) {}
    string operation() override { return "DecoratorB(" + Decorator::operation() + ")"; }
};


void clientCode(Component* component) {
  cout << "RESULT: " << component->operation();
}


int main()
{
  Component* simple = new ConcreteComponent;
  cout << "Client: I've got a simple component:\n";
  clientCode(simple);
  cout << "\n\n";

  Component* decorator1 = new DecoratorA(simple);
  Component* decorator2 = new DecoratorB(decorator1);
  cout << "Client: Now I've got a decorated component:\n";
  clientCode(decorator2);
  cout << "\n";

  delete simple;
  delete decorator1;
  delete decorator2;

  return 0;
}