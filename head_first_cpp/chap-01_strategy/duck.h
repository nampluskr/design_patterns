#pragma once
#include "fly_behavoir.h"
#include "quack_behavoir.h"
#include <iostream>
using namespace std;

// Context
// Abstract Class
struct Duck {
    FlyBehavoir* flyBehavoir;
    QuackBehavoir* quackBehavoir;

    virtual ~Duck() = default;
    void performFly() const {
        flyBehavoir->fly();
    }
    void performQuack() const {
        quackBehavoir->quack();
    }
    void swim() const {
        cout << "All ducks float, even decoys!" << endl;
    }
    virtual void display() const = 0;

    void setFlyBehavoir(FlyBehavoir* fb) {
        this->flyBehavoir = fb;
    }
    void setQuackBehavoir(QuackBehavoir* qb) {
        this->quackBehavoir = qb;
    }
};

struct MallardDuck : Duck {
    MallardDuck() {
        flyBehavoir = new FlyWithWings();
        quackBehavoir = new Quack();
    }
    void display() const override {
        cout << "I'm real Mallard duck." << endl;
    }
};

struct RedheadDuck : Duck {
    RedheadDuck() {
        flyBehavoir = new FlyWithWings();
        quackBehavoir = new Quack();
    }
    void display() const override {
        cout << "I'm real Red head duck." << endl;
    }
};

struct RubberDuck : Duck {
    RubberDuck() {
        flyBehavoir = new FlyNoWay();
        quackBehavoir = new Squeak();
    }
    void display() const override {
        cout << "I'm a rubber duck." << endl;
    }
};

struct ModelDuck : Duck {
    ModelDuck() {
        flyBehavoir = new FlyNoWay();
        quackBehavoir = new Quack();
    }
    void display() const override {
        cout << "I'm a model duck." << endl;
    }
};
