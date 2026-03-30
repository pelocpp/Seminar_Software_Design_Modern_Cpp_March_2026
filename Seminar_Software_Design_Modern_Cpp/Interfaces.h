#pragma once

#include <string>
#include <iostream>

namespace AbstractClassVsInterface {

    // interface declaration 
    class Interface
    {
    public:
        virtual ~Interface() {};

        virtual void method_first() = 0;             // only 'abstract' methods
        virtual void method_second() = 0;            // only 'abstract' methods
    };

    // abstract class declaration 
    class AbstractClass
    {
    public:
        virtual ~AbstractClass() {}

        AbstractClass(const std::string& message);

        //AbstractClass(const std::string& message)
        //    : m_message{ message }
        //{
        //}

        virtual void method_third() = 0;             // 'abstract' method

        virtual void method_fourth()                 // (virtual) method with implementation
        {
            std::cout << m_message << std::endl;
        }

        void method_fifth() const                    // (final) method
        {
        }

    protected:
        std::string m_message;                       // some data
    };
}