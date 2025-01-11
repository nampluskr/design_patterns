#include <iostream>
#include <vector>
using namespace std;


// Iterator 인터페이스
struct Iterator {
    virtual ~Iterator() = default;
    virtual bool hasNext() = 0;
    virtual int next() = 0;
};

// ConcreteIterator 클래스
struct ConcreteIterator : Iterator {
    ConcreteIterator(const vector<int>& collection) { _collection = collection; }

    bool hasNext() override { return _position < _collection.size(); }
    int next() override {
        if (this->hasNext()) return _collection[_position++];
        return -1; // 또는 예외 처리
    }
private:
    vector<int> _collection;
    int _position = 0;
};

// Aggregate 인터페이스
struct Aggregate {
    virtual ~Aggregate() {}
    virtual Iterator* createIterator() = 0;
};

// ConcreteAggregate 클래스
struct ConcreteAggregate : Aggregate {
    void addItem(int item) { _collection.push_back(item); }
    Iterator* createIterator() override { return new ConcreteIterator(_collection); }
private:
    vector<int> _collection;
};


int main()
{
    ConcreteAggregate aggregate;
    aggregate.addItem(1);
    aggregate.addItem(2);
    aggregate.addItem(3);

    Iterator* iterator = aggregate.createIterator();
    while (iterator->hasNext()) {
        cout << iterator->next() << " ";
    }
    cout << endl;
    delete iterator;

    return 0;
}