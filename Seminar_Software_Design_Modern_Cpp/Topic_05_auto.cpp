#include <vector>
#include <list>
#include <iostream>
#include <algorithm>

class Person
{
private:
    std::string m_firstName;
    std::string m_lastName;
    int         m_age;

public:
    Person() : m_age() {}
    Person(int age) : m_age(age) {}
    Person(const std::string& first, const std::string& last)
        : m_firstName(first), m_lastName(last) , m_age(0)
    {}

public:
    // getter
    int getAge() const { return m_age; }
    const std::string& getFirstName() const { return m_firstName; }
};

void test_auto()
{
    Person p("Hans", "Mueller");

    auto& first = p.getFirstName();

    const auto& first2 = p.getFirstName();


}