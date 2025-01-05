#include <iostream>
using namespace std;


// Subject 인터페이스 (실제 객체와 프록시가 공유하는 인터페이스)
struct Subject {
    virtual ~Subject() = default;
    virtual void request() = 0;
};

// RealSubject 클래스 (실제 객체)
struct RealSubject : Subject {
    RealSubject() { cout << "RealSubject 생성\n"; }   // 객체 생성 시점 확인
    ~RealSubject(){ cout << "RealSubject 소멸\n"; }
    void request() override { cout << "RealSubject의 request() 호출\n"; }
};

// VirtualProxy 클래스 (가상 프록시)
struct VirtualProxy : Subject {
    ~VirtualProxy(){ if(_realSubject != nullptr) delete _realSubject; }
    void request() override {
        if (_realSubject == nullptr) // 필요할 때 객체 생성 (지연 초기화)
            _realSubject = new RealSubject();
        _realSubject->request();
    }
private:
    RealSubject* _realSubject = nullptr; // 실제 객체 포인터
};

// ProtectedProxy 클래스 (보호 프록시)
struct ProtectedProxy : Subject {
    ProtectedProxy(Subject* _subject, bool canAccess) : _subject(_subject), canAccess(canAccess) {}
    ~ProtectedProxy(){ delete _subject; }

    void request() override {
        if (canAccess) {
            cout << "접근 권한 있음. 요청 전달\n";
            _subject->request();
        } else {
            cout << "접근 권한 없음.\n";
        }
    }
private:
    Subject* _subject;
    bool canAccess;
};


int main()
{
    // 가상 프록시 사용 예시
    cout << "가상 프록시 사용:\n";
    Subject* virtualProxy = new VirtualProxy();
    virtualProxy->request(); // 이 시점에 RealSubject 객체 생성
    virtualProxy->request(); // 이미 생성된 객체 사용
    delete virtualProxy;
    cout << endl;

    // 보호 프록시 사용 예시
    cout << "보호 프록시 사용:\n";
    Subject* realSubjectInstance = new RealSubject();
    Subject* protectionProxy1 = new ProtectedProxy(realSubjectInstance, true); // 접근 권한 있음
    Subject* protectionProxy2 = new ProtectedProxy(new RealSubject(), false);  // 접근 권한 없음
    cout << endl;

    protectionProxy1->request();
    protectionProxy2->request();
    delete protectionProxy1;
    delete protectionProxy2;
    cout << endl;

    return 0;
}