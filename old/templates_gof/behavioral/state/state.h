#pragma once
#include <string>
using namespace std;

class Context;

// State Interface
class State {
public:
    virtual ~State() = default;
    virtual void handle(Context* context) = 0;
    virtual string getName() = 0;
};

// Concrete States
class StateA : public State {
public:
    string getName() override;
    void handle(Context* context) override;
};

class StateB : public State {
public:
    string getName() override;
    void handle(Context* context) override;
};

// Context
class Context {
private:
    State* _state;

public:
    Context();
    ~Context();
    void setState(State* state);
    void request();
};