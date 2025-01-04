// State Pattern Template
// https://refactoring.guru/design-patterns/state/cpp/example
#include <iostream>
#include <string>
using namespace std;

struct Context;

// State Interface
struct State {
    virtual ~State() = default;

    void setContext(Context* context) { _context = context; }

    virtual string getName() = 0;
    virtual void handle1() = 0;
    virtual void handle2() = 0;
protected:
    Context* _context;
};

// Context
struct Context {
    Context() { _state = nullptr; }
    Context(State* state) { _state = nullptr; setState(state); }
    ~Context() { delete _state; }

    void setState(State* state) {
        if (_state != nullptr) delete _state;
        _state = state;
        cout << "Context: Transition to " << _state->getName() << ".\n";
        _state->setContext(this);
    }
    void request1() { _state->handle1(); }
    void request2() { _state->handle2(); }
private:
    State* _state;
};

// Concrete States
struct StateA : State {
    string getName() override { return "State A"; }
    void handle1() override;
    void handle2() override { cout << "StateA handles request2.\n"; }
};

struct StateB : State {
    string getName() override { return "State B"; }
    void handle1() override { 
        cout << "State B handles request2.(State B -> State A)\n";
        _context->setState(new StateA);
    }
    void handle2() override { cout << "State B handles request2.\n"; }
};

void StateA::handle1() {
    cout << "State A handles request2.(State A -> State B)\n";
    _context->setState(new StateB);
}


// Client
int main()
{
    Context* context = new Context(new StateA);
    cout << endl;

    context->request1();    // State A -> State B
    cout << endl;

    context->request2();    // State B
    cout << endl;

    context->request1();    // State B -> State A
    cout << endl;

    context->request2();    // State A

    delete context;

    return 0;
}
