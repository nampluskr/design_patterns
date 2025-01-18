#if 1
// https://www.geeksforgeeks.org/factory-method-for-designing-pattern/
// pointer version

#include <iostream>
using namespace std;

// Product interface
class Vehicle {
public:
    virtual ~Vehicle() {};
    virtual void printVehicle() const = 0;
};

// Concrete Products
class TwoWheeler : public Vehicle {
public:
    void printVehicle() const override { cout << "I am two wheeler\n"; }
};

class FourWheeler : public Vehicle {
public:
    void printVehicle() const override { cout << "I am four wheeler\n"; }
};

// Creator Interface
class VehicleFactory {
public:
    virtual ~VehicleFactory() {};
    virtual Vehicle* createVehicle() const = 0;
};

// Concrete Creators
class TwoWheelerFactory : public VehicleFactory {
public:
    Vehicle* createVehicle() const override { return new TwoWheeler(); }
};

class FourWheelerFactory : public VehicleFactory {
public:
    Vehicle* createVehicle() const override { return new FourWheeler(); }
};

// Client
class Client {
private:
    VehicleFactory* _factory;
public:
    Client(VehicleFactory* factory = nullptr) { setFactory(factory); }
    void setFactory(VehicleFactory* factory) { _factory = factory;}
    Vehicle* getVehicle() { return _factory->createVehicle(); }
};


int main()
{
    if (0) {
        VehicleFactory* factory;
        Vehicle* vehicle;

        factory = new TwoWheelerFactory();
        vehicle = factory->createVehicle();
        vehicle->printVehicle();

        factory = new FourWheelerFactory();
        vehicle = factory->createVehicle();
        vehicle->printVehicle();

        delete factory;
        delete vehicle;
    }
    if (1) {
        Vehicle* vehicle;
        Client client;

        TwoWheelerFactory twoWheelerFactory;
        client.setFactory(&twoWheelerFactory);
        vehicle = client.getVehicle();
        vehicle->printVehicle();

        FourWheelerFactory fourWheelerFactory;
        client.setFactory(&fourWheelerFactory);
        vehicle = client.getVehicle();
        vehicle->printVehicle();

        delete vehicle;
    }

    if (0) {
        VehicleFactory* twoWheelerFactory = new TwoWheelerFactory();
        Vehicle* twoWheeler = twoWheelerFactory->createVehicle();
        twoWheeler->printVehicle();

        delete twoWheelerFactory;
        delete twoWheeler;

        VehicleFactory* fourWheelerFactory = new FourWheelerFactory();
        Vehicle* fourWheeler = fourWheelerFactory->createVehicle();
        fourWheeler->printVehicle();

        delete fourWheelerFactory;
        delete fourWheeler;
    }

    if (0) {
        TwoWheelerFactory twoWheelerFactory;
        Client client(&twoWheelerFactory);
        Vehicle* vehicle1 = client.getVehicle();
        vehicle1->printVehicle();

        delete vehicle1;

        FourWheelerFactory fourWheelerFactory;
        client.setFactory(&fourWheelerFactory);
        Vehicle* vehicle2 = client.getVehicle();
        vehicle2->printVehicle();

        delete vehicle2;
    };

    return 0;
}
#endif