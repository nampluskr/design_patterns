// template for Strategy Pattern (Behavioral)
#include <iostream>
#include <string>
using namespace std;


// Strategy Inteface
struct Strategy {
    virtual ~Strategy() = default;
    virtual void execute(const string& data) = 0;
};

// Concrete Strategies
struct StrategyA : Strategy {
    void execute(const string& data) override {
        cout << "Execute Strategy-A for " << data << endl;
    }
};

struct StrategyB : Strategy {
    void execute(const string& data) override {
        cout << "Execute Strategy-B for " << data << endl;
    }
};

// Context
struct Context {
    Context() { _strategy = nullptr; }
    Context(Strategy* strategy) { _strategy = strategy; }
    ~Context() { 
        cout << "Context Deconstrutor\n";
        delete _strategy;
    }

    void setStrategy(Strategy* strategy) { _strategy = strategy; }
    void executeStrategy(const string& data) { _strategy->execute(data); }
private:
    Strategy* _strategy;
};

// Client Code
int main()
{
    string data = "DATA";
    Context context;

    if (1) {
        Strategy* strategyA = new StrategyA();
        context.setStrategy(strategyA);
        context.executeStrategy(data);

        Strategy* strategyB = new StrategyB();
        context.setStrategy(strategyB);
        context.executeStrategy(data);

        delete strategyA;   // aggregation
        delete strategyB;   // aggregation
    }

    if (1) {
        StrategyA strategyA;
        context.setStrategy(&strategyA);
        context.executeStrategy(data);

        StrategyB strategyB;
        context.setStrategy(&strategyB);
        context.executeStrategy(data);
    }

    return 0;
}