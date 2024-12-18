#pragma once
#include "fly_behavoir.h"
#include "quack_behavoir.h"
#include <iostream>
using namespace std;

// Context
// Abstract Class
struct Duck {
    FlyBehavoir* flyBehavior;
    QuackBehavoir* quackBehavior;

    virtual ~Duck() = default;
    virtual void display() = 0;

    void performFly() { flyBehavior->fly(); }
    void performQuack() { quackBehavior->quack(); }
    void swim() { cout << "All ducks float, even decoys!" << endl; }

    void setFlyBehavoir(FlyBehavoir* fb) { flyBehavior = fb; }
    void setQuackBehavoir(QuackBehavoir* qb) { quackBehavior = qb; }
};

struct MallardDuck : Duck {
    MallardDuck() {
        flyBehavior = new FlyWithWings();
        quackBehavior = new Quack();
    }
    void display() override {
        cout << "I'm real Mallard duck." << endl;
    }
};

struct RedheadDuck : Duck {
    RedheadDuck() {
        flyBehavior = new FlyWithWings();
        quackBehavior = new Quack();
    }
    void display() override {
        cout << "I'm real Red head duck." << endl;
    }
};

struct RubberDuck : Duck {
    RubberDuck() {
        flyBehavior = new FlyNoWay();
        quackBehavior = new Squeak();
    }
    void display() override {
        cout << "I'm a rubber duck." << endl;
    }
};

struct ModelDuck : Duck {
    ModelDuck() {
        flyBehavior = new FlyNoWay();
        quackBehavior = new Quack();
    }
    void display() override {
        cout << "I'm a model duck." << endl;
    }
};
