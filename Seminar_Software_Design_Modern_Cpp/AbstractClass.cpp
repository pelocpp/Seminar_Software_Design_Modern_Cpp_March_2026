
#include "Interfaces.h"

#include <string>


//AbstractClassVsInterface::AbstractClass::AbstractClass(const std::string& message)
//    : m_message{ message }
//{
//}

// versus

namespace AbstractClassVsInterface {

    AbstractClass::AbstractClass(const std::string& message)
        : m_message{ message }
    {
    }
}