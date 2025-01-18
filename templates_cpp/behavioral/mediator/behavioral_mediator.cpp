#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Colleague;

// Mediator 인터페이스
struct Mediator {
    virtual ~Mediator() = default;
    virtual void sendMessage(const string& message, Colleague* colleague) = 0;
};

// Colleague 클래스 (추상 클래스)
struct Colleague {
    Colleague(Mediator* mediator) { _mediator = mediator; }
    virtual ~Colleague() = default;

    virtual void receiveMessage(const string& message) = 0;
    virtual void sendMessage(const string& message) = 0;
protected:
    Mediator* _mediator;
};

// ColleagueA 클래스
struct ColleagueA : Colleague {
    ColleagueA(Mediator* mediator) : Colleague(mediator) {}

    void receiveMessage(const string& message) override {
        cout << "ColleagueA received: " << message << endl;
    }
    void sendMessage(const string& message) override{
        _mediator->sendMessage(message, this);
    }
};

// ColleagueB 클래스
struct ColleagueB : Colleague {
    ColleagueB(Mediator* mediator) : Colleague(mediator) {}

    void receiveMessage(const string& message) override {
        cout << "ColleagueB received: " << message << endl;
    }
    void sendMessage(const string& message) override{
        _mediator->sendMessage(message, this);
    }
};

// ConcreteMediator 클래스
struct ConcreteMediator : Mediator {
    void setColleagueA(ColleagueA* colleagueA) { _colleagueA = colleagueA; }
    void setColleagueB(ColleagueB* colleagueB) { _colleagueB = colleagueB; }
    void sendMessage(const string& message, Colleague* colleague) override {
        if (colleague == _colleagueA)
            _colleagueB->receiveMessage(message);
        else if (colleague == _colleagueB)
            _colleagueA->receiveMessage(message);
    }
private:
    ColleagueA* _colleagueA;
    ColleagueB* _colleagueB;
};

int main()
{
    ConcreteMediator mediator;
    ColleagueA colleagueA(&mediator);
    ColleagueB colleagueB(&mediator);

    mediator.setColleagueA(&colleagueA);
    mediator.setColleagueB(&colleagueB);

    colleagueA.sendMessage("Message from ColleagueA");
    colleagueB.sendMessage("Message from ColleagueB");

    return 0;
}