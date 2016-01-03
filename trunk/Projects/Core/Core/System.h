
#ifndef OBJECTIVESCRIPT_SYSTEM_H
#define OBJECTIVESCRIPT_SYSTEM_H


// Library includes

// Project includes
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace System {


void Assert(const Object& condition, const std::string& file = "", int line = 0);
void print(const std::string& text, const std::string& file = "", int line = 0);
void println(const std::string& text, const std::string& file = "", int line = 0);


}
}


#endif //OBJECTIVESCRIPT_SYSTEM_H
