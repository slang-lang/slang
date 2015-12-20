
// Header
#include "System.h"

// Library includes
#include <iostream>

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace System {


void print(const StringObject& value)
{
    std::string text = value.getValue();

    std::cout << text << std::endl;
}


}
}
