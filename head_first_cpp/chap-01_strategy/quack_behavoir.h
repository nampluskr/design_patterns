#pragma once
#include <iostream>
using namespace std;


// Interface
struct QuackBehavoir {
    virtual ~QuackBehavoir() = default;
    virtual void quack() const = 0;
};

struct Quack : QuackBehavoir {
    void quack() const override {
        cout << "Quack." << endl;
    }
};

struct MuteQuack : QuackBehavoir {
    void quack() const override {
        cout << "<< Silence >>" << endl;
    }
};

struct Squeak : QuackBehavoir {
    void quack() const override {
        cout << "Squeak." << endl;
    }
};
