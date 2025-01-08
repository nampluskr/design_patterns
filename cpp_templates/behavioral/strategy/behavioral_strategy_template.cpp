#include <iostream>
#include <string>
using namespace std;


// 전략 인터페이스 (Strategy Interface)
struct Strategy {
    virtual ~Strategy() = default;
    virtual void execute(const string& data) = 0;
};

// 구체적인 전략 A (Concrete Strategy A)
struct StrategyA : Strategy {
    void execute(const string& data) override { 
        cout << "Executing Concrete Strategy A for " << data << endl;
    }
};

// 구체적인 전략 B (Concrete Strategy B)
struct StrategyB : Strategy {
    void execute(const string& data) override {
        cout << "Executing Concrete Strategy B for " << data << endl;
    }
};


// 문맥 (Context)
struct Context {
    Context(Strategy* strategy) : _strategy(strategy) {}
    ~Context() { delete _strategy; }

    void setStrategy(Strategy* strategy) {
        delete _strategy; // 기존 전략 삭제 (메모리 누수 방지!)
        _strategy = strategy;
    }
    void executeStrategy(const string& data) { _strategy->execute(data); }
private:
    Strategy* _strategy;
};


int main()
{
    string data = "data";
    // 전략 A 사용
    Context context(new StrategyA());
    context.executeStrategy(data);

    // 전략 변경 (전략 B로 변경)
    context.setStrategy(new StrategyB());
    context.executeStrategy(data);

    // 전략 A 다시 사용
    context.setStrategy(new StrategyA());
    context.executeStrategy(data);

    return 0;
}
