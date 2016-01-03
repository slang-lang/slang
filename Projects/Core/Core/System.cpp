
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


void Assert(const Object& condition, const std::string& file, int line)
{
(void)file;

	if ( isFalse(condition) ) {
		throw Utils::Exceptions::AssertionFailed(condition.ToString(), Utils::Position(line, 0));
	}
}

void print(const std::string& text, const std::string& file, int line)
{
	::Utils::PrinterDriver::getInstance()->print(text, file, line);
}

void println(const std::string& text, const std::string& file, int line)
{
	::Utils::PrinterDriver::getInstance()->println(text, file, line);
}


}
}
