#include <iostream>
#include <string>
using namespace std;

// 전방 선언
struct Context;

// State 추상 클래스
struct State {
    virtual ~State() = default;
    virtual void handle(Context* context) = 0;
protected:
    Context* _context;
};

// 구체적인 State A
struct StateA : State {
    StateA(Context* context) { _context = context; }
    void handle(Context* context) override;
};

// 구체적인 State B
struct StateB : State {
    StateB(Context* context) { _context = context; }
    void handle(Context* context) override;
};


// 추상 Context
struct Context {
    virtual ~Context() = default;
    void setState(State* state) { _state = state; };
    virtual void request() = 0;
protected:
    State* _state;
};

// 구체적인 Context
struct ConcreteContext : Context {
    ConcreteContext() { _state = new StateA(this); }    // 초기 상태
    ~ConcreteContext() { delete _state; }
    void request() override { _state->handle(this); }
};


void StateA::handle(Context* context) {
    cout << "Handling in StateA. Switching to StateB." << endl;
    context->setState(new StateB(context));
    delete this;
}
void StateB::handle(Context* context) {
    cout << "Handling in StateB. Switching to StateA." << endl;
    context->setState(new StateA(context));
    delete this;
}


int main()
{
    ConcreteContext context;

    context.request(); // A -> B
    context.request(); // B -> A
    context.request(); // A -> B

    return 0;
}
