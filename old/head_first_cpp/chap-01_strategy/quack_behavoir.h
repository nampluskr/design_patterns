#pragma once
#include <iostream>
using namespace std;


// Interface
struct QuackBehavoir {
    virtual ~QuackBehavoir() = default;
    virtual void quack() = 0;
};

struct Quack : QuackBehavoir {
    void quack() override { cout << "Quack." << endl; }
};

struct MuteQuack : QuackBehavoir {
    void quack() override { cout << "<< Silence >>" << endl; }
};

struct Squeak : QuackBehavoir {
    void quack() override { cout << "Squeak." << endl; }
};
