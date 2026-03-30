// ===========================================================================
// ConceptualExample.cpp // Abstract Classes vs Interfaces in C++
// ===========================================================================

#include "Interfaces.h"

#include <array>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace AbstractClassVsInterface {

    // abstract class inheriting from an interface 
    class AnotherAbstractClass : public /*virtual*/ Interface
    {
    public:
        AnotherAbstractClass(double value) : m_value{ value } {}

        void method_first() override
        {
            // std::cout << m_value << std::endl;
            std::cout << "Another AbstractClass" << std::endl;
        }

    protected:
        double m_value;
    };

    // concrete class inheriting from an abstract class 
    class ConcreteClass : public AnotherAbstractClass
    {
    public:
        ConcreteClass() : ConcreteClass{ 1.0 } {}

        ConcreteClass(double value)
            : AnotherAbstractClass{ value }, m_anotherValue{} {
        }

        ConcreteClass(double value1, double value2)
            : AnotherAbstractClass{ value1 }, m_anotherValue{ value2 } {
        }

        void method_second() override
        {
            std::cout << m_value << ", " << m_anotherValue << std::endl;
        }

    private:
        double m_anotherValue;
    };

    // concrete class inheriting directly from an interface 
    class AnotherConcreteClass : public Interface
    {
    public:
        AnotherConcreteClass() : m_oneMoreValue{ 1.0 } {}

        AnotherConcreteClass(double value) : m_oneMoreValue{ value } {}

        void method_first() override
        {
            std::cout << "Another ConcreteClass" << std::endl;
        }

        void method_second() override
        {
            method_first();
        }

        void my_method()
        {
        }

    private:
        double m_oneMoreValue;
    };

    // =======================================================================

    static Interface* getInterface()
    {
        AnotherConcreteClass* impl = new AnotherConcreteClass();
        // or
        // Interface* impl = new AnotherConcreteClass();

        //impl->

        return impl;
    }

    // =======================================================================

    static void test_client_of_interface()
    {
        Interface* ip = getInterface();

      //  ip->

        ip->method_first();

        delete ip;
    }
}

// ===========================================================================

void test_poly()
{
    using namespace AbstractClassVsInterface;

    std::shared_ptr<ConcreteClass> ptr1{ new ConcreteClass ()};
    std::shared_ptr<ConcreteClass> ptr2 = std::make_shared<ConcreteClass>();
    std::shared_ptr<ConcreteClass> ptr3 = std::make_shared<ConcreteClass>();

    std::shared_ptr<AnotherConcreteClass> ptr10{ new AnotherConcreteClass() };
    std::shared_ptr<AnotherConcreteClass> ptr11 = std::make_shared<AnotherConcreteClass>();
    std::shared_ptr<AnotherConcreteClass> ptr12 = std::make_shared<AnotherConcreteClass>();

    ConcreteClass obj1;
    ConcreteClass obj2;
    ConcreteClass obj3;

    AnotherConcreteClass obj10;
    AnotherConcreteClass obj11;
    AnotherConcreteClass obj12;

    // Ist-ein Beziehung // is-a Relationship:
    // Ein AnotherConcreteClass-Objekt realisiert das 'Interface'

    // C-style Array
    //std::shared_ptr<Interface> pointers[6]{
    //    ptr1,ptr2, ptr3, ptr10, ptr11, ptr12
    //};

    // Modern C++ Array
    std::array < std::shared_ptr<Interface>, 6 >   pointers {
        ptr1,ptr2, ptr3, ptr10, ptr11, ptr12
    };

    // Polymorphmus: Range-based for-Loop // for_each
    for (std::shared_ptr<Interface> elem : pointers) {
        elem->method_first();
    }

}




void test_conceptual_example()
{
    using namespace AbstractClassVsInterface;

    // Interface obj1;                      // Error
    // AbstractClass obj2;                  // Error
    // AnotherAbstractClass obj3;           // Error
    ConcreteClass obj4{ 1.5, 2.5 };
    obj4.method_first();
    obj4.method_second();
    AnotherConcreteClass obj5{ 3.5 };
    obj5.method_first();
    obj5.method_second();

    // ---------------------------------------------

    // using references
    Interface& obj01{ obj4 };
    obj01.method_first();
    obj01.method_second();
    // AbstractClass& obj02{ obj4 };        // Error - no relationship with interface 'Interface'
    AnotherAbstractClass& obj03{ obj4 };
    obj03.method_first();
    obj03.method_second();
    ConcreteClass obj04{ obj4 };
    obj04.method_first();
    obj04.method_second();
    AnotherConcreteClass obj05{ obj5 };
    obj05.method_first();
    obj05.method_second();

    // ---------------------------------------------

    // using pointers
    Interface* obj001{ &obj4 };
    obj001->method_first();
    obj001->method_second();
    // AbstractClass* obj002{ &obj4 };     // Error
    AnotherAbstractClass* obj003{ &obj4 };
    obj003->method_first();
    obj003->method_second();
    ConcreteClass* obj004{ &obj4 };
    obj004->method_first();
    obj004->method_second();
    AnotherConcreteClass* obj005{ &obj5 };
    obj005->method_first();
    obj005->method_second();

    // ---------------------------------------------
}

// ===========================================================================
// End-of-File
// ===========================================================================
