
// Header
#include "System.h"

// Library includes
#include <iostream>

// Project includes
#include <Tools/Printer.h>
#include <Utils/Exceptions.h>
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {
namespace System {


void Assert(const Object& condition, const Utils::Position& position)
{
	if ( isFalse(condition) ) {
		throw Utils::Exceptions::AssertionFailed(condition.ToString(), position);
	}
}

void Print(const std::string& text, const Utils::Position& position)
{
	::Utils::PrinterDriver::getInstance()->print(text, position.file, position.line);
}

void PrintLn(const std::string& text, const Utils::Position& position)
{
	::Utils::PrinterDriver::getInstance()->println(text, position.file, position.line);
}


}
}
