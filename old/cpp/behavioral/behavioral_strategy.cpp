// https://medium.com/cp-massive-programming/abstract-factory-cheat-sheet-e97ed1b2ab61
#include <iostream>
#include <string>
using namespace std;

// Interface
struct Strategy {
    virtual ~Strategy() = default;
    virtual void sort() = 0;
};

struct MergeSort : Strategy {
    void sort() override { cout << "Sorting using Merge Sort\n"; }
};

struct QuickSort : Strategy {
    void sort() override { cout << "Sorting using Quick Sort\n"; }
};


// Context
struct Sorting {
    Sorting() { this->_strategy = nullptr; }
    Sorting(Strategy* strategy) { this->_strategy = strategy; } // aggregation
    ~Sorting() { delete _strategy; }

    void setSortStrategy(Strategy* strategy) { this->_strategy = strategy; }
    void sort() { _strategy->sort(); }
private:
    Strategy* _strategy;
};


// Client Code
int main()
{
    Sorting sorter;
    sorter.setSortStrategy(new MergeSort());
    sorter.sort();

    sorter.setSortStrategy(new QuickSort());
    sorter.sort();

    return 0;
}
