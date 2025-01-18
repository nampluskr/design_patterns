#if 1
// Chapter 2. Builder
// 2.5 Composite Builder

#include <iostream>
#include <string>
using namespace std;

class PersonAddressBuilder;
class PersonJobBuilder;


class Person {
    string street_address, post_code, city;
    string company_name, position;
    int annual_income = 0;

public:
    // Person() { cout << ">> Person created\n"; }
    //  ~Person() { cout << ">> Person destroyed\n"; }

    friend ostream& operator<<(ostream& os, const Person& person) {
        os << "street_address: " << person.street_address << endl
            << "post_code: " << person.post_code << endl
            << "city: " << person.city << endl
            << "company_name: " << person.company_name << endl
            << "position: " << person.position << endl
            << "annual_income: " << person.annual_income;
        return os;
    }
    friend class PersonAddressBuilder;
    friend class PersonJobBuilder;
};


class PersonBuilderBase {
protected:
    Person& person;
    PersonBuilderBase(Person& person) : person(person) {}
public:
    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;
    Person get() const { return person; }
};


class PersonBuilder : public PersonBuilderBase {
private:
    Person person;
public:
    PersonBuilder() : PersonBuilderBase(person) {}
};


class PersonAddressBuilder : public PersonBuilderBase {
private:
    using Self = PersonAddressBuilder;
public:
    PersonAddressBuilder(Person& person)
        : PersonBuilderBase(person) {}

    Self& at(const string& street_adress) {
        person.street_address = street_adress;
        return *this;
    }
    Self& with_postcode(const string& post_code) {
        person.post_code = post_code;
        return *this;
    }
    Self& in(const string& city) {
        person.city = city;
        return *this;
    }
};


class PersonJobBuilder : public PersonBuilderBase {
private:
    using Self = PersonJobBuilder;
public:
    PersonJobBuilder(Person& person)
        : PersonBuilderBase(person) {}

    Self& at(const string& company_name) {
        person.company_name = company_name;
        return *this;
    }
    Self& as_a(const string& position) {
        person.position = position;
        return *this;
    }
    Self& earning(int annual_income) {
        person.annual_income = annual_income;
        return *this;
    }
};


PersonAddressBuilder PersonBuilderBase::lives() const {
    return PersonAddressBuilder(person);
}

PersonJobBuilder PersonBuilderBase::works() const {
    return PersonJobBuilder(person);
}


int main()
{
    if (1) {
        PersonBuilder builder;
        Person person = builder
            .lives().at("123 London Road")
                    .with_postcode("SW1 1GB")
                    .in("London")
            .works().at("PragmaSoft")
                    .as_a("Consultant")
                    .earning(10e6)
            .get();
        cout << person << endl;
    }

    return 0;
}
#endif