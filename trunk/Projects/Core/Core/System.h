
#ifndef OBJECTIVESCRIPT_SYSTEM_H
#define OBJECTIVESCRIPT_SYSTEM_H


// Library includes

// Project includes
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Object.h>
#include <Core/Utils/Position.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace System {


void Assert(const Runtime::Object& condition, const Utils::Position& position = Utils::Position());
void Print(const std::string& text, const Utils::Position& position = Utils::Position());
void PrintLn(const std::string& text, const Utils::Position& position = Utils::Position());


}
}


#endif
