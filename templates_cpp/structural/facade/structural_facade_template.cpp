#include <iostream>
#include <string>
using namespace std;


// 서브시스템 1
struct SubsystemA {
    SubsystemA(const string& name) : _name(name) {}
    string operation1() { return "SubsystemA (" + _name + ") Operation 1"; }
    string operation2() { return "SubsystemA (" + _name + ") Operation 2"; }
private:
    string _name;
};

// 서브시스템 2
struct SubsystemB {
    string operation1() { return "SubsystemB Operation 1"; }
};

// 서브시스템 3
struct SubsystemC {
    string operation1() { return "SubsystemC Operation 1"; }
    string operation2() { return "SubsystemC Operation 2"; }
};

// Facade
struct Facade {
    Facade(const string& name) {
        _subsystem1 = new SubsystemA(name);
        _subsystem2 = new SubsystemB();
        _subsystem3 = new SubsystemC();
    }
    ~Facade() {
        delete _subsystem1;
        delete _subsystem2;
        delete _subsystem3;
    }
    string operationA() {
        string result = "Facade Operation A:\n";
        result += _subsystem1->operation1() + "\n";
        result += _subsystem2->operation1() + "\n";
        return result;
    }
    string operationB() {
        string result = "Facade Operation B:\n";
        result += _subsystem1->operation2() + "\n";
        result += _subsystem3->operation1() + "\n";
        result += _subsystem3->operation2() + "\n";
        return result;
    }
private:
    SubsystemA* _subsystem1;
    SubsystemB* _subsystem2;
    SubsystemC* _subsystem3;
};

int main()
{
    Facade facade("MySubsystem");

    cout << facade.operationA() << endl;
    cout << facade.operationB() << endl;

    return 0;
}