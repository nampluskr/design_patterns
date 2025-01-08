#include <iostream>
#include <vector>
#include <algorithm> // std::remove 사용을 위해 추가
using namespace std;

// 전방 선언
struct Subject;

// Observer (관찰자) 인터페이스
struct Observer {
    virtual ~Observer() = default;
    virtual void update(Subject* subject) = 0;
};

// Subject (관찰 대상)
struct Subject {
    ~Subject() {
        for (Observer* observer : _observers) {
            delete observer;
        }
    }
    void attach(Observer* observer) { _observers.push_back(observer); }
    void detach(Observer* observer) {
        // observer를 찾아서 제거
        auto it = find(_observers.begin(), _observers.end(), observer);
        if (it != _observers.end()) {
            _observers.erase(it);
        }
    }
    int getState() const { return _state; }
    void setState(int state) { _state = state; notify(); }

private:
    vector<Observer*> _observers;
    int _state;

protected:
    void notify() {
        for (Observer* observer : _observers)
            observer->update(this);
    }
};

// 구체적인 Observer A
struct ObserverA : Observer {
    void update(Subject* subject) override {
        cout << "ObserverA: Subject's state is now " << subject->getState() << endl;
    }
};

// 구체적인 Observer B
struct ObserverB : Observer {
    void update(Subject* subject) override {
        cout << "ObserverB: Subject's state is now " << subject->getState() * 2 << endl;
    }
};


int main()
{
    Subject* subject = new Subject();
    Observer* observerA = new ObserverA();
    Observer* observerB = new ObserverB();

    subject->attach(observerA);
    subject->attach(observerB);

    subject->setState(5);
    cout << endl;

    subject->setState(10);
    cout << endl;

    subject->detach(observerA);

    subject->setState(15);
    cout << endl;

    delete subject; // Subject 삭제 시 Observer들도 함께 삭제

    return 0;
}
