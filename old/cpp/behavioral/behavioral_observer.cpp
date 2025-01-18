#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

struct Observer;

// Subject 인터페이스
struct Subject {
    virtual ~Subject() = default;
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notify() = 0;
    virtual string getState() = 0;
    virtual void setState(const string& state) = 0;
};

// Observer 인터페이스
struct Observer {
    virtual ~Observer() = default;
    virtual void update(Subject* subject) = 0; // Subject*를 인자로 받음
};

// Concrete Observer
struct ConcreteObserver : Observer {
    ConcreteObserver(const string& id) : id(id), state("") {}

    void update(Subject* subject) override {
        if (subject) { // subject가 nullptr이 아닌지 확인
            this->state = subject->getState();
            cout << "Observer-" << id << " received state: " << subject->getState() << endl;
        }
        else {
            cout << "Observer-" << id << " received update from a deleted subject." << endl;
        }
    }
private:
    string id;
    string state;
};



// Concrete Subject
struct ConcreteSubject : Subject {
    void attach(Observer* observer) override { observers.insert(observer); }
    void detach(Observer* observer) override { observers.erase(observer); }
    void notify() override {
        for (Observer* observer : observers) {
            observer->update(this); // this 포인터를 전달
        }
    }
    string getState() override { return state; }
    void setState(const string& state) override {
        if (this->state != state) {
            this->state = state;
            notify();
        }
    }
private:
    set<Observer*> observers;
    string state;
};

int main() {
    if (0) {
        // Subject 생성
        ConcreteSubject subject;

        // Observer 생성 (new 사용)
        Observer* observer1 = new ConcreteObserver("1");
        Observer* observer2 = new ConcreteObserver("2");
        Observer* observer3 = new ConcreteObserver("3");

        // Observer 등록
        subject.attach(observer1);
        subject.attach(observer2);
        subject.attach(observer3);

        // 상태 변경 및 알림d
        cout << endl;
        subject.setState("Initial State");

        cout << endl;
        subject.setState("New State");

        // observer2 해제 후 상태 변경 (delete 필요!)
        subject.detach(observer2);
        delete observer2;

        cout << endl;
        subject.setState("Another State");

        // Subject 해제 전에 Observer들을 모두 해제하는 것이 안전합니다.
        delete observer1;
        delete observer3;
    }
    if (1) {
        // Subject 생성
        ConcreteSubject subject;

        // Observer 생성 (new 사용)
        ConcreteObserver observer1("1");
        ConcreteObserver observer2("2");
        ConcreteObserver observer3("3");

        // Observer 등록
        subject.attach(&observer1);
        subject.attach(&observer2);
        subject.attach(&observer3);

        subject.setState("Initial State");

        cout << endl;
        subject.setState("New State");

        subject.detach(&observer2);
        cout << endl;
        subject.setState("Another State");
    }

    return 0;
}
