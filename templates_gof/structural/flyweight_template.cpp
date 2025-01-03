#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;


// Flyweight 인터페이스
struct Flyweight {
    virtual ~Flyweight() = default;
    virtual void operation(const string& extrinsicState) = 0;
};

// SharedFlyweight 클래스 (공유 객체)
struct SharedFlyweight : Flyweight {
    SharedFlyweight(const string& intrinsicState) { _intrinsicState = intrinsicState; }

    void operation(const string& extrinsicState) override {
        cout << "SharedFlyweight: Intrinsic = " << _intrinsicState
            << ", Extrinsic = " << extrinsicState << endl;
    }
private:
    string _intrinsicState;
};

// UnsharedFlywieght 클래스 (공유되지 않는 객체)
struct UnsharedFlywieght : Flyweight {
    UnsharedFlywieght(const string& allState) : allState(allState) {}

    void operation(const string& extrinsicState) override {
        cout << "UnsharedFlywieght: All State = " << allState
            << ", Extrinsic = " << extrinsicState << endl;
    }
private:
    string allState;
};

// FlyweightFactory 클래스 (Flyweight 객체 생성 및 관리)
struct FlyweightFactory {
    // Factory 소멸자에서 모든 Flyweight 객체 해제 (매우 중요!)
    ~FlyweightFactory() {
        cout << "FlyweightFactory 소멸\n";
        for (const auto& it : flyweights) {
            delete it.second;
        }
        flyweights.clear();
    }
    Flyweight* getFlyweight(const string& key) {
        if (flyweights.find(key) == flyweights.end()) {
            cout << "Creating new Flyweight: " << key << endl;
            flyweights[key] = new SharedFlyweight(key);
        }
        else {
            cout << "Reusing existing Flyweight: " << key << endl;
        }
        return flyweights[key];
    }
private:
    unordered_map<string, Flyweight*> flyweights;
};

// Client
int main() {
    FlyweightFactory factory;

    Flyweight* flyweight1 = factory.getFlyweight("A");
    flyweight1->operation("Context 1");

    Flyweight* flyweight2 = factory.getFlyweight("B");
    flyweight2->operation("Context 2");

    Flyweight* flyweight3 = factory.getFlyweight("A"); // 기존 객체 재사용
    flyweight3->operation("Context 3");

    // UnsharedFlyweight 사용 예시 (메모리 관리에 주의!)
    Flyweight* unsharedFlyweight = new UnsharedFlywieght("Unshared Data");
    unsharedFlyweight->operation("Context 4");

    delete unsharedFlyweight;
    unsharedFlyweight = nullptr;

    return 0;
}
