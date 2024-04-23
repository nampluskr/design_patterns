#if 0
#include <string>
using namespace std;

class PersonAddressBuilder;
class PersonJobBuilder;

class Person {
private:
    // lives
    string street, zipcode, city;
    // works
    string company, position;
    int income;
};


class PersonBuilderBase {
protected:
    Person& person;
    PersonBuilderBase(Person& person): person(person) {}
public:
    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;
};


class PersonBuilder: public PersonBuilderBase {
private:
    Person p;
public:
    PersonBuilder(): PersonBuilderBase(p) {}
};

class PersonAddressBuilder: public PersonBuilderBase {
private:
    using Self = PersonAddressBuilder;
public:
    PersonAddressBuilder(Person& person): PersonBuilderBase(person) {}
    Self& at(string street) { person.street = street; return *this; }
    Self& with_zipcode(string zipcode) { person.zipcode = zipcode; }
    Self& in(string city) { person.city = city; }
};



int main()
{
    return 0;
}
#endif