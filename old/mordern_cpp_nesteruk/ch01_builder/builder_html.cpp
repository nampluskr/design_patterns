#if 0
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

class HtmlBuilder;

// Product
class HtmlElement {
public:
    string name;
    string text;
    vector<HtmlElement> elements;
    const size_t indent_size = 2;
    friend HtmlBuilder;

    HtmlElement() {}
    HtmlElement(const string& name, const string& text) {
        this->name = name;
        this->text = text;
    }
    string str(int indent = 0) const {
        ostringstream oss;
        string s(indent_size*indent, ' ');
        oss << s << "<" << name << ">" << endl;
        if (text.size() > 0)
        oss << string(indent_size*(indent + 1), ' ') << text << endl;

        for (const auto& e : elements)
        oss << e.str(indent + 1);

        oss << s << "</" << name << ">" << endl;
        return oss.str();
    }
    static HtmlBuilder build(const string& root_name);
};

// Product Builder
class HtmlBuilder {
public:
    HtmlElement root;
    HtmlBuilder(const string& root_name) {
        root.name = root_name;
    }
    void add_child1(const string& child_name, const string& child_text) {
        HtmlElement e{ child_name, child_text };
        root.elements.push_back(e);
    }
    HtmlBuilder& add_child2(const string& child_name, const string& child_text) {
        HtmlElement e{ child_name, child_text };
        root.elements.push_back(e);
        return *this;
    }
    HtmlBuilder* add_child3(const string& child_name, const string& child_text) {
        HtmlElement e{ child_name, child_text };
        root.elements.push_back(e);
        return this;
    }
    operator HtmlElement() const { return root; }   // since C++11
    HtmlElement get() const { return root; }
    string str() { return root.str(); }
};

HtmlBuilder HtmlElement::build(const string& root_name) {
    return HtmlBuilder(root_name);
}

int main()
{
    if (0) {    // Object Constructor
        string words[] = { "hello", "world" };
        HtmlElement list{ "ul", "" };
        for (const auto& w: words)
            list.elements.push_back({ "li", w });
        cout << list.str() << "\n";
    }
    if (0) {    // Product Builder
        HtmlBuilder builder1{ "ul" };
        builder1.add_child1("li", "hello");
        builder1.add_child1("li", "world");
        cout << builder1.str() << "\n";
    }
    if (0) {    // Fluent Builder (reference &)
        HtmlBuilder builder2{ "ul" };
        builder2.add_child2("li", "hello").add_child2("li", "world");
        cout << builder2.str() << "\n";
    }
    if (1) {    // Fluent Builder (reference &)
        HtmlBuilder* builder3 = new HtmlBuilder{ "ul" };
        builder3->add_child3("li", "hello")->add_child3("li", "world");
        cout << builder3->str() << "\n";
        delete builder3;
    }
    if (1) {    // Move Constructor
        HtmlElement element = HtmlElement::build("ul")
            .add_child2("li", "hello").add_child2("li", "world");
        cout << element.str() << "\n";
    }
    if (1) {
        HtmlBuilder builder4{ "ul" };
        HtmlElement e = builder4
            .add_child2("li", "hello")
            .add_child2("li", "world")
            .get();
        cout << e.str() << "\n";
    }

    return 0;
}
#endif