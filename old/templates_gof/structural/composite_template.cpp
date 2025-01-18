// Composite Pattern Template
// https://refactoring.guru/design-patterns/composite/cpp/example
#include <iostream>
#include <list>
#include <string>
using namespace std;


struct Component {
    virtual ~Component() = default;
    virtual string operation() = 0;

    virtual void add(Component* component) {}
    virtual void remove(Component* component) {}
    virtual bool isComposite() { return false; }

    //Component* getParent() { return _parent; }
    //void setParent(Component* parent) { _parent = parent; }

protected:
    // Component* _parent;
};


struct Leaf : Component {
    string operation() override { return "Leaf"; }
};


struct Composite : Component {
    void add(Component* component) override {
        _children.push_back(component);
        //component->setParent(this);
    }
    void remove(Component* component) override {
        _children.remove(component);
        //component->setParent(nullptr);
    }
    bool isComposite() override { return true; }
    string operation() override {
        string result = "";
        for (Component* child : _children) {
            if (child == _children.back())
                result += child->operation();
            else
                result += child->operation() + "+";
        }
        return "Branch(" + result + ")";
    }
protected:
    list<Component*> _children;
};


void ClientCode(Component* component) {
    cout << "RESULT: " << component->operation() << endl;
    cout << endl;
}


void ClientCode2(Component* component1, Component* component2) {
    if (component1->isComposite())
        component1->add(component2);
    cout << "RESULT: " << component1->operation() << endl;
    cout << endl;
}



int main()
{
    Component* simple = new Leaf;

    cout << "Client: I've got a simple component:\n";
    ClientCode(simple);

    Component* tree = new Composite;
    Component* branch1 = new Composite;
    Component* leaf1 = new Leaf;
    Component* leaf2 = new Leaf;
    Component* leaf3 = new Leaf;

    branch1->add(leaf1);
    branch1->add(leaf2);
    ClientCode(branch1);

    Component* branch2 = new Composite;

    branch2->add(leaf3);
    tree->add(branch1);
    tree->add(branch2);

    cout << "Client: Now I've got a composite tree:\n";
    ClientCode(tree);

    cout << "Client: I don't need to check the components classes even when managing the tree:\n";
    ClientCode2(tree, simple);

    delete simple;
    delete tree;
    delete branch1;
    delete branch2;
    delete leaf1;
    delete leaf2;
    delete leaf3;

    return 0;
}
