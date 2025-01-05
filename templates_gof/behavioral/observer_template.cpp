#include <iostream>
#include <set>
using namespace std;

struct Subject;

// Observer 인터페이스
struct Observer {
    virtual ~Observer() {}
    virtual void update() = 0;
    virtual void setSubject(Subject* subject) = 0;
};

// Subject 인터페이스
struct Subject {
    virtual ~Subject() {}
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notify() = 0;
    virtual int getState() = 0;
    virtual void setState(int state) = 0;
};

// ConcreteSubject 클래스
struct ConcreteSubject : Subject {
    int getState() override{ return _state; }
    void setState(int state) override { _state = state; notify(); }
    void attach(Observer* observer) override { _observers.insert(observer); }
    void detach(Observer* observer) override { _observers.erase(observer); }
    void notify() override { for (Observer* observer : _observers) observer->update(); }
private:
    set<Observer*> _observers;
    int _state;
};

// ObserverA 클래스
struct ObserverA : Observer {
    ObserverA() { _subject = nullptr; }
    ObserverA(Subject* subject) { _subject = subject; _subject->attach(this); }
    ~ObserverA() { if (_subject) _subject->detach(this); }

    void setSubject(Subject* subject) override { _subject = subject; }
    void update() override {
        if (_subject)
            cout << "Observer A: Subject's state is now " << _subject->getState() << endl;
    }
private:
    Subject* _subject;
};

// ObserverB 클래스
struct ObserverB : Observer {
    ObserverB() { _subject = nullptr; }
    ObserverB(Subject* subject) { _subject = subject; _subject->attach(this); }
    ~ObserverB() { if (_subject) _subject->detach(this); }

    void setSubject(Subject* subject) override { _subject = subject; }
    void update() override {
        if (_subject)
            cout << "Observer B: Received new state: " << _subject->getState() * 2 << endl;
    }
private:
    Subject* _subject;
};

int main()
{
    if (1) {
        Subject* subject = new ConcreteSubject;
        Observer* observerA = new ObserverA;
        Observer* observerB = new ObserverB;

        observerA->setSubject(subject);
        observerB->setSubject(subject);

        subject->attach(observerA);
        subject->attach(observerB);

        subject->setState(5);
        cout << endl;
        subject->setState(10);
        cout << endl;

        subject->detach(observerA);
        subject->setState(15);

        delete observerA;
        delete observerB;
        delete subject;
    }
    if (1) {
        cout << endl << endl;
        ConcreteSubject subject;

        ObserverA observerA(&subject); // 생성 시 Subject 지정 및 attach 완료
        ObserverB observerB(&subject); // 생성 시 Subject 지정 및 attach 완료

        subject.setState(5);
        cout << endl;
        subject.setState(10);
        cout << endl;

        subject.detach(&observerA);
        subject.setState(15);
    }

    return 0;
}