#include <iostream>
#include <string>
#include <memory>

class MemoryPool
{};

class Data
{ };


MemoryPool g_pool;


class BusinessLogic
{
    Data* m_data;    // Dieser Zeiger sollte sein / ist gültig,
                     // solange Objekt 'BusinessLogic' lebt
};

class BusinessLogicSmart
{
    std::shared_ptr<Data> m_data;  // Referenz-Zähler // Smarter GC
};




class Person
{
private:
    MemoryPool& m_pool;  

public:
    Person () : m_pool(g_pool) {}

    Person (MemoryPool& pool) : m_age(20), m_pool(pool) {}

    std::string firstName;
    std::string lastName;

    int m_age;

public:
    // getter
    int getAge() const { /*m_age++;*/ return m_age; }

    const std::string& getFirstName() const { return firstName; }
};

static void func1()
{
    // Value-based Version

    Person p;              // Das ist EIN OBJEKT // Value // Wert

    Person p2 = p;         // HIER WIRD DAS KOMPLETTE OBJEKT KOPIERT
}

static void func2()
{
    //  Reference-Based  // 1 Ausprägung: Mit Zeiger
    //  Diese ist SEHR ÄHNLICH zu Java

    Person* p = nullptr;          // Das ist EIN Zeiger / Pointer
    p = new Person;               // Daten: Heap
    p->m_age = 30;

 //   Person* p = new Person;

    Person* p2 = nullptr;
    p2 = p;                       // Hier wird ein Zeiger kopiert.

    // NO Garbage Collector (GC)
    delete p;
}

Person pGlobal;

static void func3()
{
    // Referenzen
    Person p;
    p.m_age = 20;

    Person p2 = p;

    Person& p3 = p;    // p3 ist eine Referenz 
                       // Hinter den Kulissen: Da steht die Adresse von p drin
    p3.m_age = 30;
}

static void func4()
{
    Person* p = nullptr;          // Das ist EIN Zeiger / Pointer
    p = new Person;               // Daten: Heap
    p->m_age = 30;

    Person& pRef = *p;            // DON'T DO THIS
    pRef.m_age = 40;

    delete p;
}

static void func5()
{
    const Person p1;
    int age = p1.getAge();

    Person p2;
    std::string first = p1.getFirstName();
}



// NOT Recommende
//static void tueWasMitPerson(Person* p)
//{
//    p->m_age = 40;
//}

static void tueWasMitPerson(const Person& p)  // YES: Keine Kopie
{
    // p.m_age = 40;   // write

    int age = p.m_age;
}

void test_references()
{
    func4();
}