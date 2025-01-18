#pragma once
#include <iostream>
using namespace std;


// Interface
struct FlyBehavoir {
    virtual ~FlyBehavoir() = default;
    virtual void fly() = 0;
};

struct FlyWithWings : FlyBehavoir {
    void fly() override { cout << "I'm flying!!" << endl; }
};

struct FlyNoWay : FlyBehavoir { 
    void fly() override { cout << "I can't fly." << endl; }
};

struct FlyRocketPowered : FlyBehavoir {
    void fly() override { cout << "I'm flying with a roket!" << endl; }
};
