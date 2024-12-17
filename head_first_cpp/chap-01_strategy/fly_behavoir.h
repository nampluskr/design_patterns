#pragma once
#include <iostream>
using namespace std;


// Interface
struct FlyBehavoir {
    virtual ~FlyBehavoir() = default;
    virtual void fly() const = 0;
};

struct FlyWithWings : FlyBehavoir {
    void fly() const override {
        cout << "I'm flying!!" << endl;
    }
};

struct FlyNoWay : FlyBehavoir {
    void fly() const override {
        cout << "I can't fly." << endl;
    }
};

struct FlyRocketPowered : FlyBehavoir {
    void fly() const override {
        cout << "I'm flying with a roket!" << endl;
    }
};
