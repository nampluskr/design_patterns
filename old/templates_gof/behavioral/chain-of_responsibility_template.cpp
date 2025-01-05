// Chain of Responsibility Template
#include <iostream>

using namespace std;

// Abstract Handler 인터페이스
struct Handler {
    virtual ~Handler() = default;
    void setNext(Handler* next) { _next = next; }
    void handle(int request) {
        if (canHandle(request)) process(request);
        else if (_next) _next->handle(request);
        else cout << "Request " << request << " reached the end of the chain." << endl;
    }
protected:
    Handler* _next;
    virtual bool canHandle(int request) = 0;
    virtual void process(int request) = 0;
};

// Concrete Handlers
struct HandlerA : Handler {
    bool canHandle(int request) override {
        return request >= 0 && request < 10;
    }
    void process(int request) override {
        cout << "HandlerA handled request: " << request << endl;
    }
};

struct HandlerB : Handler {
    bool canHandle(int request) override {
        return request >= 10 && request < 20;
    }
    void process(int request) override {
        cout << "HandlerB handled request: " << request << endl;
    }
};

struct HandlerC : Handler {
    bool canHandle(int request) override {
        return request >= 20 && request < 30;
    }
    void process(int request) override {
        cout << "HandlerC handled request: " << request << endl;
    }
};


int main()
{
    // 핸들러 체인 생성 (new/delete를 직접 관리해야 함)
    Handler* handlerA = new HandlerA();
    Handler* handlerB = new HandlerB();
    Handler* handlerC = new HandlerC();

    handlerA->setNext(handlerB);
    handlerB->setNext(handlerC);

    // 요청 처리
    handlerA->handle(5);   // HandlerA가 처리
    handlerA->handle(15);  // HandlerB가 처리
    handlerA->handle(25);  // HandlerC가 처리
    handlerA->handle(35);  // 체인의 끝에 도달

    // 중요: 동적 할당된 메모리 해제! (메모리 누수 방지)
    delete handlerA;
    delete handlerB;
    delete handlerC;

    return 0;
}