#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Component 인터페이스
struct Component {
    virtual ~Component() = default;
    virtual void add(Component* component) {}
    virtual void remove(Component* component) {}
    virtual string getName() { return ""; }
    virtual void operation() = 0;
};

// Leaf (잎)
struct Leaf : Component {
    Leaf(const string& name) { _name = name; }
    string getName() override { return _name; }
    void operation() override { cout << "Leaf " << _name << " operation." << endl; }
private:
    string _name;
};

// Composite (복합체)
struct Composite : Component {
    Composite(const string& name) { _name = name; }
    ~Composite() {
        // 매우 중요: 모든 자식들을 삭제해야 함
        for (Component* child : _children) { delete child; }
        _children.clear(); // 벡터 비우기 (필수는 아니지만 권장)
    }
    void add(Component* component) override { 
        _children.push_back(component);
    }
    void remove(Component* component) override {
        auto it = find(_children.begin(), _children.end(), component);
        if (it != _children.end()) { _children.erase(it); }
    }
    string getName() override { return _name; }
    void operation() override {
        cout << "Composite " << _name << " operation." << endl;
        for (Component* child : _children) { child->operation(); }
    }
private:
    vector<Component*> _children;
    string _name;
};


int main()
{
    // 복합체 생성
    Composite* root = new Composite("Root");
    Composite* branch1 = new Composite("Branch 1");
    Composite* branch2 = new Composite("Branch 2");

    // 잎 생성
    Leaf* leaf1 = new Leaf("Leaf 1");
    Leaf* leaf2 = new Leaf("Leaf 2");
    Leaf* leaf3 = new Leaf("Leaf 3");

    // 복합체에 잎 추가
    branch1->add(leaf1);
    branch1->add(leaf2);
    branch2->add(leaf3);

    // 복합체에 다른 복합체 추가
    root->add(branch1);
    root->add(branch2);

    // 전체 구조에 대한 연산 수행
    root->operation();

    // 매우 중요: root를 삭제하면 모든 자식들도 함께 삭제됨
    delete root;

    return 0;
}