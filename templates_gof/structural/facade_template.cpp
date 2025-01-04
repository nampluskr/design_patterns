#include <iostream>
using namespace std;


// 서브시스템 1
struct SubsystemA {
    void operationA1() { cout << "SubsystemA: Operation A1\n"; }
    void operationA2() { cout << "SubsystemA: Operation A2\n"; }
};

// 서브시스템 2
struct SubsystemB {
    void operationB1() { cout << "SubsystemB: Operation B1\n"; }
    void operationB2() { cout << "SubsystemB: Operation B2\n"; }
};

// 서브시스템A3
struct SubsystemC{
    void operationC1() { cout << "SubsystemC: Operation C1\n"; }
    void operationC2() { cout << "SubsystemC: Operation C2\n"; }
};

// 퍼사드
struct Facade {
    SubsystemA subsystemA;
    SubsystemB subsystemB;
    SubsystemC subsystemC;

    void operation1() {
        cout << "Facade: Operation 1\n";
        subsystemA.operationA1();
        subsystemB.operationB1();
        subsystemC.operationC1();
    }
    void operation2() {
        cout << "Facade: Operation 2\n";
        subsystemA.operationA2();
        subsystemB.operationB2();
        subsystemC.operationC2();
    }
};

int main() {
    Facade facade;

    facade.operation1();
    cout << endl;

    facade.operation2();
    cout << endl;

    return 0;
}