// https://medium.com/cp-massive-programming/builder-cheat-sheet-ec0417836e82
#include <iostream>
#include <string>
using namespace std;

// Product
struct House {
    int walls, doors, windows, floors;
    bool garden, pool, basement;
};

// Builder
struct Builder {
    virtual ~Builder() {};
    virtual Builder* buildWalls(int) = 0;
    virtual Builder* buildDoors(int) = 0;
    virtual Builder* buildWindows(int) = 0;
    virtual Builder* buildFloors(int) = 0;
    virtual Builder* buildGarden() = 0;
    virtual Builder* buildPool() = 0;
    virtual Builder* buildBasement() = 0;
    virtual House getResult() = 0;
};

struct HouseBuilder : Builder {
    Builder* buildWalls(int count) override { house.walls = count; return this; }
    Builder* buildDoors(int count) override { house.doors = count; return this; }
    Builder* buildWindows(int count) override { house.windows = count; return this; }
    Builder* buildFloors(int count) override { house.floors = count; return this; }
    Builder* buildGarden() override { house.garden = true; return this; }
    Builder* buildPool() override { house.pool = true; return this; }
    Builder* buildBasement() override { house.basement = true; return this; }
    House getResult() override { return house; }
private:
    House house;    // composition ???
};

// Director
struct Director {
    void setBuilder(Builder* builder) { this->builder; }
    void constructVilla() {
        builder->buildWalls(42);
        builder->buildBasement();
        builder->buildDoors(15);
        builder->buildFloors(7);
        builder->buildGarden();
        builder->buildPool();
        builder->buildWindows(75);
    }
    void constructFamliyHouse() {
        builder->buildWalls(17);
        builder->buildBasement();
        builder->buildWindows(32);
        builder->buildDoors(7);
        builder->buildFloors(2);
        builder->buildGarden();
    }
private:
    Builder* builder;   // aggregation ???
};

int main()
{
    if (1) { // with Director
        Builder* builder = new HouseBuilder();
        Director director;
        director.setBuilder(builder);

        director.constructFamliyHouse();
        House familyHouse = builder->getResult();

        director.constructVilla();
        House villa = builder->getResult();

        delete builder;
    }
    if (1) {    // without Director
    
    }
    return 0;
}
