#include "state.h"
#include <iostream>
using namespace std;

// Implementation of Concrete States
string StateA::getName() { return "State A"; }
void StateA::handle(Context* context) {
    cout << "Handling in State A. Changing to State B.\n";
    context->setState(new StateB());
}

string StateB::getName() { return "State B"; }
void StateB::handle(Context* context) {
    cout << "Handling in State B. Changing to State A.\n";
    context->setState(new StateA());
}


// Implementation of Context
Context::Context() : _state(new StateA()) {}
Context::~Context() {
    cout << "Context Deconstrutor\n";
    delete _state;
}
void Context::setState(State* state) {
    delete _state;
    _state = state;
}
void Context::request() {
    cout << "Current State: " << _state->getName() << "\n";
    _state->handle(this);
}

int main() {
    Context context;

    context.request(); // State A -> State B
    context.request(); // State B -> State A
    context.request(); // State A -> State B
    context.request(); // State B -> State A

    return 0;
}